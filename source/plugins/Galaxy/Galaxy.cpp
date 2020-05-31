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

#include "Galaxy.h"

using std::string;
using std::pair;
using std::make_pair;

Galaxy::Galaxy() {
	WordGenerator tempWordGenerator;
	name = tempWordGenerator.nextWord(1, 10);
	capitalize(name);

	seed = tempWordGenerator.nextWord(1, 10);
	capitalize(seed);

	pixels = 500;
	arms = 4;
	radialDistanceMult = 10.0;
	// clusterStddev = 5.0;
	clusterStddev = 7.0;
	// density = 20.0;
	density = 10.0;
	spiralA = 0.1;
	spiralB = 0.3;
	// extraStars = 1;
	extraStars = 0;
	// densityGrid = 15;
	cloudsFrequency = 0.05;
	cloudsMult = 5.0;
	densityMult = 1.0;
}

string Galaxy::getName() {
	return name;
}

string Galaxy::getSeed() {
	return seed;
}

int Galaxy::getPixels() {
	return pixels;
}

double Galaxy::getCloudsFrequency() {
	return cloudsFrequency;
}

int Galaxy::getArms() {
	return arms;
}

double Galaxy::getRadialDistanceMult() {
	return radialDistanceMult;
}

double Galaxy::getClusterStddev() {
	return clusterStddev;
}

double Galaxy::getDensity() {
	return density;
}

double Galaxy::getSpiralA() {
	return spiralA;
}

double Galaxy::getSpiralB() {
	return spiralB;
}

int Galaxy::getExtraStars() {
	return extraStars;
}

double Galaxy::getCloudsMult() {
	return cloudsMult;
}

double Galaxy::getDensityMult() {
	return densityMult;
}

bool Galaxy::setName(string nameInput) {
	if (nameInput.empty()) {
		return false;
	} else {
		name = nameInput;
		return true;
	}
}

bool Galaxy::setSeed(string seedInput) {
	if (seedInput.empty()) {
		return false;
	} else {
		seed = seedInput;
		return true;
	}
}

bool Galaxy::setPixels(int pixelsInput) {
	if (pixelsInput > 0) {
		pixels = pixelsInput;
		return true;
	} else {
		return false;
	}
}

bool Galaxy::setCloudsFrequency(double cloudsFrequencyInput) {
	if (cloudsFrequencyInput > 0) {
		cloudsFrequency = cloudsFrequencyInput;
		return true;
	} else {
		return false;
	}
}

bool Galaxy::setArms(int armsInput) {
	if (armsInput > 0) {
		arms = armsInput;
		return true;
	} else {
		return false;
	}
}

bool Galaxy::setRadialDistanceMult(double radialDistanceMultInput) {
	if (radialDistanceMultInput > 0) {
		radialDistanceMult = radialDistanceMultInput;
		return true;
	} else {
		return false;
	}
}

bool Galaxy::setClusterStddev(double clusterStddevInput) {
	if (clusterStddevInput >= 0) {
		clusterStddev = clusterStddevInput;
		return true;
	} else {
		return false;
	}
}

bool Galaxy::setDensity(double densityInput) {
	if (densityInput > 0) {
		density = densityInput;
		return true;
	} else {
		return false;
	}
}

bool Galaxy::setSpiralA(double spiralAInput) {
	if (spiralAInput != 0) {
		spiralA = spiralAInput;
		return true;
	} else {
		return false;
	}
}

bool Galaxy::setSpiralB(double spiralBInput) {
	if (spiralBInput != 0) {
		spiralB = spiralBInput;
		return true;
	} else {
		return false;
	}
}

bool Galaxy::setExtraStars(int extraStarsInput) {
	if (extraStarsInput >= 0) {
		extraStars = extraStarsInput;
		return true;
	} else {
		return false;
	}
}

bool Galaxy::setCloudsMult(double cloudsMultInput) {
	if (cloudsMultInput > 0) {
		cloudsMult = cloudsMultInput;
		return true;
	} else {
		return false;
	}
}

bool Galaxy::setDensityMult(double densityMultInput) {
	if (densityMultInput > 0) {
		densityMult = densityMultInput;
		return true;
	} else {
		return false;
	}
}

string Galaxy::generateName(int keyInput) {  // Generates a capitalized name.
	return generateName(std::to_string(keyInput));
}

string Galaxy::generateName(string keyInput) {  // Generates a capitalized name.
	string tempName = myWordGenerator.getName(keyInput);
	capitalize(tempName);
	return tempName;
}

int Galaxy::at(int x, int y) {
	// return myGalaxy[y][x];
	// TODO: Make this return the star at this location and add a separate function to check for the existence of a star.
	/*int curr = -1;
	pair<int, int> location(x, y);
	try {
		curr = blankGalaxyMap.at(location);
	} catch (const std::out_of_range& e) {
		curr = 0;
	}
	return curr; */
	auto search = galaxyMap.find(make_pair(x, y));
	if (search != galaxyMap.end()) {
		return (search->second).getStarTypeID();
	} else {
		return 0;
	}
}

bool Galaxy::capitalize(string& wordInput) {
	if (!wordInput.empty()) {
		wordInput[0] = std::toupper(wordInput[0]);
	}
	return true;
}
