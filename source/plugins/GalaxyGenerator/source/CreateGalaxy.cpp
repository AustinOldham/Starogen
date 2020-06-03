// Copyright (C) 2020  Austin Oldham
//
// This file is part of Starogen.
//
// Starogen is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Starogen is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Starogen.  If not, see <https://www.gnu.org/licenses/>.

#include "CreateGalaxy.h"

using std::cout;
using std::string;
using std::cos;
using std::sin;
using std::atan;
using std::vector;
using std::exp;
using std::pow;
using std::sqrt;
using std::max;
using std::min;
using std::endl;
using std::find;
using std::unordered_map;
using std::pair;
using std::make_pair;
using json = nlohmann::json;


// IDEA: Each star has an 8 (or higher) bit number pair that determines its local coordinates and may have a min/max value (e.g. 256 numbers for 8 bit but min is 10 and max is 245) to ensure sufficient space between stars. If 8 bit, the coordinates are determined by the main map coordinate plus the local coordinate divided by 255.
// TODO: Clouds will be generated using density map where the number of stars in a square around each star (or every pixel) is used for the calculation (odd number width of search only so offset = searchWidth / 2 and the locations at galaxy[y - offset + i][x - offset + j] are checked)
// TODO: Consider replacing the density map by adding a step to the generator where star clusters are plotted in the same way as normal stars except each cluster is more dense and each time a "star" is plotted, the number stored is incremented. The values will then be normalized to be in the range [0, 1] in order to create an approximate density map.
CreateGalaxy::CreateGalaxy() {
	initializeContainers();
}

void CreateGalaxy::run() {
	// TODO: Have the generator store the modified variables then set them in myGalaxy when generation starts in case the user changes those variables after generation but does not click "generate" again.
	name = myGalaxy.getName();
	seed = myGalaxy.getSeed();
	pixels = myGalaxy.getPixels();
	arms = myGalaxy.getArms();
	radialDistanceMult = myGalaxy.getRadialDistanceMult();
	clusterStddev = myGalaxy.getClusterStddev();
	density = myGalaxy.getDensity();
	spiralA = myGalaxy.getSpiralA();
	spiralB = myGalaxy.getSpiralB();
	extraStars = myGalaxy.getExtraStars();
	cloudsFrequency = myGalaxy.getCloudsFrequency();
	cloudsMult = myGalaxy.getCloudsMult();
	densityMult = myGalaxy.getDensityMult();

	std::hash<string> seedHasher;
	unsigned int seedHash = seedHasher(seed);
	myGalaxy.setSeedHash(seedHash);
	starClusterGen.setSeed(seed);
	cloudNoise.SetSeed(seedHash);
	cloudNoise.SetNoiseType(FastNoise::SimplexFractal);  // SimplexFractal for clouds
	cloudNoise.SetFrequency(cloudsFrequency);  // 0.05 for clouds

	myGalaxy.blankGalaxyMap.clear();
	myGalaxy.galaxyMap.clear();
	myGalaxy.clearNames();
	//myGalaxy.resize(pixels, vector<int>(pixels, 0));
	//densityMap.clear();
	//densityMap.resize(pixels, vector<double>(pixels, 0));
	//clouds.clear();
	//clouds.resize(pixels, vector<double>(pixels, 0));

	cout << name << endl;
	cout << seed << endl;

	generate();

	cout << "finished" << endl;

	/*printGalaxy(myGalaxy, name);
	string densityName = name + "_densitymap";
	printDensityMap(densityMap, densityName);
	string cloudsName = name + "_clouds";
	printClouds(clouds, cloudsName);
	string theColors = "thecolors";
	printColorPalette(theColors);*/
}

void CreateGalaxy::generate() {
	double theta;
	double halfway = pixels / 2.0;
	vector<double> rotation = calculateAngles(arms, 0);

	double maxRadialDistance = radialDistance(0, 0, halfway, halfway);

	double counter = 0.0;

	vector<bool> finished(arms, false);

	vector<vector<bool>> markedMap(pixels, vector<bool>(pixels, false));  // Prevents extremely large number of clusters in the core

	//double a = 0.1;

	//double b = 0.3;

	while (!isFinished(finished)) {  // Runs until all items are marked as true
		double spiralDistance = counter / density;  // The distance along the spiral. Increasing the density shortens the distance between two clusters of stars, making the galaxy more dense.
		double mult = getMult(spiralDistance, spiralA, spiralB); //0.1, 0.3
		for (int j = 0; j < arms; j++) {
			if (finished[j]) {
				continue;
			}
			theta = rotation[j];  // Angle of the current arm in radians.
			int x = static_cast<int>((logSpiralX(spiralDistance, theta, mult)) + halfway);
			int y = static_cast<int>((logSpiralY(spiralDistance, theta, mult)) + halfway);

			if (x < 0 || y < 0 || x >= pixels || y >= pixels) {
				finished[j] = true;
				continue;
			} else {
				if (markedMap[y][x] == false) {
					markedMap[y][x] = true;
				} else {
					continue;
				}
			}
			// Add second less dense cluster to fill out the galaxy

			double currRadialDistance = radialDistance(x, y, halfway, halfway);

			// TODO: Add option to have star colors based off of distance from the center. Currently not implemented because variety is better for gameplay.
			// Create a map between star type and distance then choose the closest type that is greater than or equal to the number generated with "probability = starClusterGen.nextNormal(distanceProportion, 0.1)".
			double distanceProportion = (maxRadialDistance - currRadialDistance) / maxRadialDistance;
			int localDensity = static_cast<int>(distanceProportion * radialDistanceMult * densityMult);
			for (int k = 0; k < extraStars; k++) {
				starCluster(x, y, localDensity, 10.0 * clusterStddev, static_cast<int>(distanceProportion * 100.0)); //5.0 * 10.0  Adds background clutter
			}
			starCluster(x, y, localDensity, clusterStddev, static_cast<int>(distanceProportion * 100.0));  //stddev = 5.0
		}
		counter++;
	}

	populateEmptyStars();


	// createDensityMap();
	// createClouds();
	// cout << "myGalaxy[y][x]: " << myGalaxy[2][1] << endl;
}


void CreateGalaxy::createApproximateDensityMap() {}

void CreateGalaxy::createClouds() {
	for (int y = 0; y < pixels; y++) {
		for (int x = 0; x < pixels; x++) {
			clouds[y][x] = 0.5 * (cloudNoise.GetNoise(x, y) + 1);  // Puts it in the range of 0 to 1
			clouds[y][x] *= densityMap[y][x];
			clouds[y][x] *= cloudsMult;
			clouds[y][x] = max(0.0, clouds[y][x]);
			clouds[y][x] = min(1.0, clouds[y][x]);
		}
	}
}

void CreateGalaxy::starCluster(int x, int y, int num, double stddev, int distanceProportionInt) {  // stddev = 5.0
	for (int i = 0; i < num; i++) {
		int modX = static_cast<int>(starClusterGen.nextNormal(0.0, stddev));
		int modY = static_cast<int>(starClusterGen.nextNormal(0.0, stddev));
		if (x + modX < 0 || y + modY < 0 || x + modX >= pixels || y + modY >= pixels) {
			continue;
		}

		// myGalaxy[y + modY][x + modX] = plotStar(distanceProportion);
		pair<int, int> location(x + modX, y + modY);
		myGalaxy.blankGalaxyMap[location] = distanceProportionInt;
	}
}

Star CreateGalaxy::plotStar(int distanceProportionInt) {
	// TODO: Replace this implementation with std::discrete_distribution.

	double probability = starClusterGen.next(0.0, 1.0);
	double probabilitySum = 0.0;

	// cout << probability << endl;

	for (int i = 0; i < starList.size(); i++) {
		probabilitySum += starList[i].adjustedChance;
		if (probability <= probabilitySum) {
			Star newStar(i);
			unsigned int starSeed = myGalaxy.getNextUniqueID();
			string starName = myGalaxy.generateName(starSeed);
			newStar.setName(starName);
			newStar.setSeed(starSeed);
			return newStar;
		}
	}

	// cout << "THIS CODE SHOULD NEVER BE REACHED" << endl;
	throw std::runtime_error("There was an error with plotStar");

	// An option will be added in the future to guarantee certain types of celestial bodies are generated by adding them after the galaxy has generated.
}

void CreateGalaxy::populateEmptyStars() {
	cout << "Populating empty stars" << endl;
	int counter = 0;
	for (auto it : myGalaxy.blankGalaxyMap) {
		myGalaxy.galaxyMap[it.first] = plotStar(it.second);
	}
	cout << "Finished populating empty stars" << endl;
}


string CreateGalaxy::getName() {
	return myGalaxy.getName();
}

string CreateGalaxy::getSeed() {
	return myGalaxy.getSeed();
}

int CreateGalaxy::getPixels() {
	return myGalaxy.getPixels();
}

double CreateGalaxy::getCloudsFrequency() {
	return myGalaxy.getCloudsFrequency();
}

int CreateGalaxy::getArms() {
	return myGalaxy.getArms();
}

double CreateGalaxy::getRadialDistanceMult() {
	return myGalaxy.getRadialDistanceMult();
}

double CreateGalaxy::getClusterStddev() {
	return myGalaxy.getClusterStddev();
}

double CreateGalaxy::getDensity() {
	return myGalaxy.getDensity();
}

double CreateGalaxy::getSpiralA() {
	return myGalaxy.getSpiralA();
}

double CreateGalaxy::getSpiralB() {
	return myGalaxy.getSpiralB();
}

int CreateGalaxy::getExtraStars() {
	return myGalaxy.getExtraStars();
}

double CreateGalaxy::getCloudsMult() {
	return myGalaxy.getCloudsMult();
}

double CreateGalaxy::getDensityMult() {
	return myGalaxy.getDensityMult();
}

bool CreateGalaxy::setName(string nameInput) {
	return myGalaxy.setName(nameInput);
}

bool CreateGalaxy::setSeed(string seedInput) {
	return myGalaxy.setSeed(seedInput);
}

bool CreateGalaxy::setPixels(int pixelsInput) {
	return myGalaxy.setPixels(pixelsInput);
}

bool CreateGalaxy::setCloudsFrequency(double cloudsFrequencyInput) {
	return myGalaxy.setCloudsFrequency(cloudsFrequencyInput);
}

bool CreateGalaxy::setArms(int armsInput) {
	return myGalaxy.setArms(armsInput);
}

bool CreateGalaxy::setRadialDistanceMult(double radialDistanceMultInput) {
	return myGalaxy.setRadialDistanceMult(radialDistanceMult);
}

bool CreateGalaxy::setClusterStddev(double clusterStddevInput) {
	return myGalaxy.setClusterStddev(clusterStddevInput);
}

bool CreateGalaxy::setDensity(double densityInput) {
	return myGalaxy.setDensity(densityMult);
}

bool CreateGalaxy::setSpiralA(double spiralAInput) {
	return myGalaxy.setSpiralA(spiralAInput);
}

bool CreateGalaxy::setSpiralB(double spiralBInput) {
	return myGalaxy.setSpiralB(spiralBInput);
}

bool CreateGalaxy::setExtraStars(int extraStarsInput) {
	return myGalaxy.setExtraStars(extraStarsInput);
}

bool CreateGalaxy::setCloudsMult(double cloudsMultInput) {
	return myGalaxy.setCloudsMult(cloudsMultInput);
}

bool CreateGalaxy::setDensityMult(double densityMultInput) {
	return myGalaxy.setDensityMult(densityMultInput);
}

Star CreateGalaxy::at(int x, int y) {
	return myGalaxy.at(x, y);
}

float CreateGalaxy::getRed(int index) {
	return starList[index].red;
}

float CreateGalaxy::getGreen(int index) {
	return starList[index].green;
}

float CreateGalaxy::getBlue(int index) {
	return starList[index].blue;
}

float CreateGalaxy::getAlpha(int index) {
	return starList[index].alpha;
}


// TODO: Completely replace or remove this function since it cannot handle large inputs.
/*
void CreateGalaxy::createDensityMap() {
	int subtracted = densityGrid / 2;
	double gridSquared = static_cast<double>(densityGrid * densityGrid);
	for (int y = 0; y < pixels; y++) {
		for (int x = 0; x < pixels; x++) {
			for (int i = 0; i < densityGrid; i++) {  // NxN area where N is an odd number and the number being subtracted is N / 2
				for (int j = 0; j < densityGrid; j++) {
					int gridY = y - subtracted + i;
					int gridX = x - subtracted + j;
					if (gridY < 0 || gridX < 0) {
						break;
					}

					if (gridY >= myGalaxy.size() || gridX >= myGalaxy[y].size()) {
						break;
					}

					if (myGalaxy[gridY][gridX] > 0) {
						densityMap[y][x]++;
					}
				}
			}
			densityMap[y][x] = densityMap[y][x] / gridSquared;  // The maximum possible number of stars in each "chunk" (densityGrid * densityGrid area) is densityGrid ^ 2. This make the maximum value 1 and the minimum 0.
			if (densityMap[y][x] > 1.0) {
				densityMap[y][x] = 1.0;
			}
		}
	}
}
*/



// Returns num equal angles (in radians) that add up to 2 * PI.
vector<double> CreateGalaxy::calculateAngles(int num, double additional) {
	vector<double> myAngles(num, 0);
	double divisor = static_cast<double>(num);
	for (int i = 0; i < num; i++) {
		myAngles[i] = ((2 * PI) * (i / divisor)) + additional;
		// cout << myAngles[i] << endl;
	}
	return myAngles;
}

string CreateGalaxy::suggestName() {
	WordGenerator tempWordGenerator;
	string tempName = tempWordGenerator.nextWord(1, 10);
	myGalaxy.capitalize(tempName);
	return tempName;
}

string CreateGalaxy::suggestSeed() {
	WordGenerator tempWordGenerator;
	string tempSeed = tempWordGenerator.nextWord(1, 10);
	myGalaxy.capitalize(tempSeed);
	return tempSeed;
}

double CreateGalaxy::suggestClusterStddev() {
	if (myGalaxy.getPixels() <= 100) {
		return myGalaxy.getPixels() / 40.0;
	} else {
		return myGalaxy.getPixels() / 100.0;
	}
}

double CreateGalaxy::suggestRadialDistanceMult() {
	return 10.0;
}

double CreateGalaxy::suggestDensity() {
	return (myGalaxy.getPixels() / 25.0);
}

double CreateGalaxy::suggestSpiralA() {
	return 0.1;
}

double CreateGalaxy::suggestSpiralB() {
	return 0.3;
}

int CreateGalaxy::suggestExtraStars() {
	if (myGalaxy.getPixels() <= 100) {
		return 0;
	} else {
		return 1;
	}
}

double CreateGalaxy::suggestCloudsMult() {
	return 5.0;
}

// Since both logSpiralX and logSpiralY both require this value, this is precalculated to save time.
double CreateGalaxy::getMult(double spiralDistance, double spiralA, double spiralB) {
	return spiralA * exp(spiralB * spiralDistance);
}

// x = spiralA * (e ^ (spiralB * spiralDistance)) * cos(spiralDistance);
double CreateGalaxy::logSpiralX(double spiralDistance, double theta, double spiralA, double spiralB) {
	double mult = exp(spiralB * spiralDistance);
	return (spiralA * mult * cos(spiralDistance - theta));
}

// y = spiralA * (e ^ (spiralB * spiralDistance)) * sin(spiralDistance);
double CreateGalaxy::logSpiralY(double spiralDistance, double theta, double spiralA, double spiralB) {
	double mult = exp(spiralB * spiralDistance);
	return (spiralA * mult * sin(spiralDistance - theta));
}

double CreateGalaxy::logSpiralX(double spiralDistance, double theta, double mult) {
	return (mult * cos(spiralDistance - theta));
}

double CreateGalaxy::logSpiralY(double spiralDistance, double theta, double mult) {
	return (mult * sin(spiralDistance - theta));
}

bool CreateGalaxy::isFinished(vector<bool> finished) {
	for (int i = 0; i < finished.size(); i++) {
		if (finished[i] == false) {
			return false;
		}
	}
	return true;
}

double CreateGalaxy::radialDistance(int x, int y, double centerX, double centerY) {
	double distanceX = pow(abs(centerX - x), 2);
	double distanceY = pow(abs(centerY - y), 2);
	return sqrt(distanceX + distanceY);
}

void CreateGalaxy::initializeContainers() {
	starList = readStarFile("config/galaxy_stars.json");
	getProbabilities();
}

vector<CreateGalaxy::StarType> CreateGalaxy::readStarFile(string fileNameInput) {
	vector<CreateGalaxy::StarType> myStarList;
	std::ifstream input(fileNameInput);
	json j;
	input >> j;
	int i = 0;
	for (auto& element : j) {
		// cout << element["name"] << '\n';
		myStarList.push_back(CreateGalaxy::StarType());
		myStarList[i].name = element["name"];
		// cout << myStarList[i].name << endl;
		myStarList[i].type = element["type"];
		myStarList[i].chance = element["chance"];
		myStarList[i].red = element["red"];
		myStarList[i].green = element["green"];
		myStarList[i].blue = element["blue"];
		myStarList[i].alpha = element["alpha"];
		i++;
	}
	return myStarList;
}

void CreateGalaxy::getProbabilities() {
	double probabilitySum = 0.0;

	for (int i = 0; i < starList.size(); i++) {
		probabilitySum += starList[i].chance;
	}

	for (int i = 0; i < starList.size(); i++) {
		starList[i].adjustedChance = starList[i].chance / probabilitySum;  // Normalizes the probabilities so they are between 0.0 and 1.0.
		// cout << starList[i].adjustedChance << endl;
	}
}

bool CreateGalaxy::saveGalaxy(string pathInput) {
	// See Godot autoload
	cout << "Saving" << endl;

	// for (int i = 0; i < starList.size(); i++) {
	//	cout << starList[i].name << " " << starList[i].type << endl;
	// }

	//string testFile("C:\\serialization_test\\test.galaxy");
	//std::filesystem::path fileLocation(testFile);
	// std::ofstream ostr(testFile.c_str(), std::ios::binary);

	std::filesystem::path dir(pathInput);
	dir.make_preferred();
	string newName = myGalaxy.getName();
	std::replace(newName.begin(), newName.end(), ' ', '_');
	std::filesystem::path fileLocation = dir / newName;
	fileLocation.replace_extension(".galaxy");

	cout << fileLocation << endl;

	std::ofstream ostr(fileLocation.c_str(), std::ios::binary);
	boost::archive::binary_oarchive oa(ostr);
	// oa << starList;
	oa << myGalaxy;
	ostr.close();
	cout << "Saved" << endl;
	return true;
}

bool CreateGalaxy::loadGalaxy(string pathInput, string fileNameInput) {
	// TODO: Move this to the galaxy manager.
	cout << "Loading" << endl;

	// vector<StarType> loadedStarList;

	// Galaxy testGalaxy;

	//string testFile("C:\\serialization_test\\test.galaxy");
	//std::ifstream istr(testFile.c_str(), std::ios::binary);

	std::filesystem::path dir(pathInput);
	dir.make_preferred();
	std::replace(fileNameInput.begin(), fileNameInput.end(), ' ', '_');
	std::filesystem::path fileLocation = dir / fileNameInput;
	fileLocation.replace_extension(".galaxy");

	cout << fileLocation << endl;

	std::ifstream istr(fileLocation.c_str(), std::ios::binary);
	boost::archive::binary_iarchive ia(istr);
	// ia >> loadedStarList;
	ia >> myGalaxy;
	istr.close();

	cout << myGalaxy.getName() << endl;
	cout << myGalaxy.getPixels() << endl;

	// for (int i = 0; i < loadedStarList.size(); i++) {
	//	cout << loadedStarList[i].name << " " << loadedStarList[i].type << endl;
	// }

	cout << "Loaded" << endl;
	return true;
}

/*vector<vector<string>> CreateGalaxy::readFile(string fileName) {
	vector<vector<string>> myVector;
	std::ifstream myFile(fileName);
	if (myFile.is_open()) {
		string line;
		while (std::getline(myFile, line)) {
			if (line.empty()) {
				continue;
			}

			if (line.at(0) == '#') {
				continue;
			}
			myVector.push_back(splitString(line, '\t'));
		}
		myFile.close();
	}
	return myVector;
}

vector<string> CreateGalaxy::splitString(const string &s, char delimiter) {
	vector<string> result;
	std::stringstream ss(s);
	string item;

	while (getline(ss, item, delimiter)) {
		result.push_back(item);
	}

	return result;
}*/

string CreateGalaxy::getStarNameAt(int x, int y) {
	Star tempStar = at(x, y);
	if (tempStar.getStarTypeID() == -1) {
		return "";
	} else {
		return tempStar.getName();
	}
}

int CreateGalaxy::getStarTypeIDAt(int x, int y) {
	Star tempStar = at(x, y);
	return tempStar.getStarTypeID();
}

bool CreateGalaxy::setCensoredWordsPath(string pathInput) {
	return myGalaxy.setCensoredWordsPath(pathInput);
}
