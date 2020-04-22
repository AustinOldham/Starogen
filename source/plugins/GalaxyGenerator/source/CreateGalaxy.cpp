//Copyright (C) 2019  Austin Oldham
//
//This file is part of Starogen.
//
//Starogen is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//Starogen is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Starogen.  If not, see <https://www.gnu.org/licenses/>.

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
using json = nlohmann::json;


// TODO: Replace "type_x" with more specific types such as "red_dwarf", "red_giant", etc.
// TODO: Replace hardcoded values with values read in from a file in order to make adding new stars easier

// IDEA: Instead of just choosing a number and replacing the pixel, add to it so the less dense areas will naturally have different colors
// IDEA: Each star has an 8 (or higher) bit number pair that determines its local coordinates and may have a min/max value (e.g. 256 numbers for 8 bit but min is 10 and max is 245) to ensure sufficient space between stars. If 8 bit, the coordinates are determined by the main map coordinate plus the local coordinate divided by 255.
// TODO: Clouds will be generated using density map where the number of stars in a square around each star (or every pixel) is used for the calculation (odd number width of search only so offset = searchWidth / 2 and the locations at galaxy[y - offset + i][x - offset + j] are checked)

CreateGalaxy::CreateGalaxy() {
	initializeContainers();
}

void CreateGalaxy::generate(string nameInput, string seedInput, int pixelsInput, double cloudsFrequencyInput, int armsInput, double radialDistanceMultInput, double clusterStddevInput, double densityInput, double aInput, double bInput, int extraStarsInput, int densityGridInput, double cloudsMultInput, double densityMult) {
	seed = getSeed(seedInput);

	name = getName(nameInput);

	pixels = pixelsInput;

	arms = getArms(armsInput);

	radialDistanceMult = getRadialDistanceMult(radialDistanceMultInput);

	clusterStddev = getClusterStddev(clusterStddevInput);  // pixels/100.0? pixels/40.0?(worse)

	density = getDensity(densityInput);

	a = getA(aInput);
	b = getB(bInput);

	extraStars = getExtraStars(extraStarsInput);

	densityGrid = getDensityGrid(densityGridInput);

	cloudsMult = getCloudsMult(cloudsMultInput);

	std::hash<string> seedHasher;
	int seedInt = seedHasher(seed);
	starClusterGen.setSeed(seed);
	cloudNoise.SetSeed(seedInt);
	cloudNoise.SetNoiseType(FastNoise::SimplexFractal);  // SimplexFractal for clouds
	cloudNoise.SetFrequency(cloudsFrequencyInput);  // 0.05 for clouds

	myGalaxy.clear();
	myGalaxy.resize(pixels, vector<int>(pixels, 0));
	densityMap.clear();
	densityMap.resize(pixels, vector<double>(pixels, 0));
	clouds.clear();
	clouds.resize(pixels, vector<double>(pixels, 0));

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
	//int arms = 4;  // 4
	vector<double> rotation = getAngles(arms, 0);

	double maxRadialDistance = radialDistance(0, 0, halfway, halfway);

	double counter = 0.0;

	vector<bool> finished(arms, false);

	vector<vector<bool>> markedMap(pixels, vector<bool>(pixels, false));  // Prevents extremely large number of clusters in the core

	//double a = 0.1;

	//double b = 0.3;

	while (!isFinished(finished)) {  // Runs until all items are marked as true
		// double t = counter / 20.0;
		double t = counter / density;
		double mult = getMult(t, a, b); //0.1, 0.3
		for (int j = 0; j < arms; j++) {
			if (finished[j]) {
				continue;
			}
			theta = rotation[j];
			int x = static_cast<int>((logSpiralX(t, theta, mult)) + halfway);
			int y = static_cast<int>((logSpiralY(t, theta, mult)) + halfway);

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
			if (extraStars) {
				starCluster(x, y, localDensity, 10.0 * clusterStddev, distanceProportion); //5.0 * 10.0  Adds background clutter
			}
			starCluster(x, y, localDensity, clusterStddev, distanceProportion);  //stddev = 5.0
		}
		counter++;
	}


	createDensityMap();
	createClouds();
	// cout << "myGalaxy[y][x]: " << myGalaxy[2][1] << endl;
}

int CreateGalaxy::at(int x, int y) {
	return myGalaxy[y][x];
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

int CreateGalaxy::getPixels() {
	return pixels;
}

// NOTE: Add padding to the myGalaxy vector so the star clusters don't get cut off on the edges

void CreateGalaxy::createDensityMap() {
	int subtracted = densityGrid / 2;
	double gridSquared = static_cast<double>(densityGrid * densityGrid);
	for (int y = 0; y < pixels; y++) {
		for (int x = 0; x < pixels; x++) {
			for (int i = 0; i < densityGrid; i++) {  // NxN area where N is an odd number is the number being subtracted is N / 2
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
			densityMap[y][x] = densityMap[y][x] / gridSquared;
			if (densityMap[y][x] > 1.0) {
				densityMap[y][x] = 1.0;
			}
		}
	}
}

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

void CreateGalaxy::starCluster(int x, int y, int num, double stddev, double distanceProportion) {  // stddev = 5.0
	for (int i = 0; i < num; i++) {
		double modX = starClusterGen.nextNormal(0.0, stddev);
		double modY = starClusterGen.nextNormal(0.0, stddev);
		if (x + modX < 0 || y + modY < 0 || x + modX >= pixels || y + modY >= pixels) {
			continue;
		}

		myGalaxy[y + modY][x + modX] = plotStar(distanceProportion);
	}
}

int CreateGalaxy::plotStar(double distanceProportion) {
	// TODO: Choose stars randomly (maybe add bias by storing the first star generated at x and y then rerolling if that star does not match)
	// Choose using this https://stackoverflow.com/a/9330667/11356785

	double probability = starClusterGen.next(0.0, 1.0);
	double probabilitySum = 0.0;

	// cout << probability << endl;

	for (int i = 0; i < starList.size(); i++) {
		probabilitySum += starList[i].adjustedChance;
		if (probability <= probabilitySum) {
			return i;
		}
	}

	// cout << "THIS CODE SHOULD NEVER BE REACHED" << endl;
	return 0;

	// An option will be added in the future to guarantee certain types of celestial bodies are generated by adding them after the galaxy has generated.
}



vector<double> CreateGalaxy::getAngles(int num, double additional) {
	vector<double> myAngles(num, 0);
	double divisor = static_cast<double>(num);
	for (int i = 0; i < num; i++) {
		myAngles[i] = ((2 * PI) * (i / divisor)) + additional;
		// cout << myAngles[i] << endl;
	}
	return myAngles;
}

string CreateGalaxy::getName(string nameInput) {
	if (nameInput.empty()) {
		return string("placeholdername");
	} else {
		return nameInput;
	}
}

string CreateGalaxy::getSeed(string seedInput) {
	if (seedInput.empty()) {
		return string("placeholderseed");
	} else {
		return seedInput;
	}
}

int CreateGalaxy::getArms(int armsInput) {
	if (armsInput <= 0) {
		return 4;  // Placeholder
	} else {
		return armsInput;
	}
}

double CreateGalaxy::getClusterStddev(double clusterStddevInput) {
	if (clusterStddevInput <= 0.0) {
		if (pixels <= 100) {
			return pixels / 40.0;
		} else {
			return pixels / 100.0;
		}
	} else {
		return clusterStddevInput;
	}
}

double CreateGalaxy::getRadialDistanceMult(double radialDistanceMultInput) {
	if (radialDistanceMultInput <= 0.0) {
		return 10.0;  // Not a placeholder
	} else {
		return radialDistanceMultInput;
	}
}

double CreateGalaxy::getDensity(double densityInput) {
	if (densityInput <= 0.0) {
		return (pixels / 25);
	} else {
		return densityInput;
	}
}

double CreateGalaxy::getA(double aInput) {
	return aInput;  // TODO: Determine what values are invalid and randomly pick a value.
}

double CreateGalaxy::getB(double bInput) {
	return bInput;  // TODO: Determine what values are invalid and randomly pick a value.
}

bool CreateGalaxy::getExtraStars(int extraStarsInput) {
	if (extraStarsInput < 0) {
		if (pixels <= 100) {
			return false;
		} else {
			return true;
		}
	} else if (extraStarsInput == 0) {
		return false;
	} else {
		return true;
	}
}

int CreateGalaxy::getDensityGrid(int densityGridInput) {
	if (densityGridInput <= 0) {
		if (pixels <= 100) {
			return 5;
		} else {
			return 15;
		}
	} else {
		return densityGridInput;
	}
}

double CreateGalaxy::getCloudsMult(double cloudsMultInput) {
	if (cloudsMultInput <= 0.0) {
		return 5.0;
	} else {
		return cloudsMultInput;
	}
}

double CreateGalaxy::getMult(double t, double a, double b) {
	return a * exp(b * t);
}

// x = a * (e^(bt)) * cos(t);
double CreateGalaxy::logSpiralX(double t, double theta, double a, double b) {
	double mult = exp(b * t);
	return (a * mult * cos(t - theta));
}

// y = a * (e^(bt)) * sin(t);
double CreateGalaxy::logSpiralY(double t, double theta, double a, double b) {
	double mult = exp(b * t);
	return (a * mult * sin(t - theta));
}

double CreateGalaxy::logSpiralX(double t, double theta, double mult) {
	return (mult * cos(t - theta));
}

double CreateGalaxy::logSpiralY(double t, double theta, double mult) {
	return (mult * sin(t - theta));
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

vector<CreateGalaxy::StarType> CreateGalaxy::readStarFile(string fileName) {
	cout << "herersf" << endl;
	vector<CreateGalaxy::StarType> myStarList;
	std::ifstream input(fileName);
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

void CreateGalaxy::saveGalaxy() {
	// Godot autoload and cereal serialization
	// Simplify things by combining all generators into one file (e.g. universegenerator)
}

int CreateGalaxy::Galaxy::starAtPosition(int x, int y) {
	return 2;
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
