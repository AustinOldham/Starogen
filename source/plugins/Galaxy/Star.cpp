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

#include "Star.h"

using std::string;
using std::vector;

Star::Star() {
	starTypeID = -1;
}

Star::Star(int id) {
	starTypeID = id;
}

int Star::getStarTypeID() {
	return starTypeID;
}

string Star::getName() {
	return name;
}

vector<Planet> Star::getPlanetList() {
	return planetList;
}

bool Star::setName(string nameInput) {
	name = nameInput;
	return true;
}

// bool Star::setSeed(int seedInput) {
// 	return setSeed(std::to_string(seedInput));
// }

bool Star::setSeed(unsigned int seedInput) {
	seed = seedInput;
	return true;
}


bool Star::setPlanetCount(uint16_t planetCountInput) {
	planetCount = planetCountInput;
	return true;
}

bool Star::setPlanetList(std::vector<Planet> planetListInput) {
	planetList = planetListInput;
	return true;
}