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

#include "RandClass.h"

using std::cout;
using std::string;

RandClass::RandClass() {
	seed = std::to_string(std::time(0));
	min = 0;
	max = 2147483647;  // Max int
	RandClass::setSeed();
}

RandClass::RandClass(string seedInput) {
	seed = seedInput;
	min = 0;
	max = 2147483647;  // Max int
	RandClass::setSeed();
}

RandClass::RandClass(string seedInput, int minInput, int maxInput) : seed(seedInput), min(minInput), max(maxInput) {
	RandClass::setSeed();
}

RandClass::RandClass(int minInput, int maxInput) {
	seed = std::to_string(std::time(0));
	min = minInput;
	max = maxInput;
	RandClass::setSeed();
}

void RandClass::setSeed() {
	std::seed_seq mySeed(seed.begin(), seed.end());
	generator.seed(mySeed);
}

void RandClass::setSeed(string inputSeed) {
	seed = inputSeed;
	RandClass::setSeed();
}

void RandClass::printInfo() {
	cout << "seed: " << seed << "\n";
	cout << "min: " << min << "\n";
	cout << "max: " << max << "\n";
}

int RandClass::next() {  // Generates a random number using the min and max initially provided
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

int RandClass::next(int minInput, int maxInput) {
	std::uniform_int_distribution<int> distribution(minInput, maxInput);
	return distribution(generator);
}

double RandClass::next(double minInput, double maxInput) {
	std::uniform_real_distribution<double> distribution(minInput, maxInput);
	return distribution(generator);
}

double RandClass::nextNormal(double mean, double stddev) {
	std::normal_distribution<double> distribution(mean, stddev);
	return distribution(generator);
}

int RandClass::nextAltNormal() {
	std::normal_distribution<double> distribution((min + max) / 2, (max - min) / 6);
	return static_cast<int>(distribution(generator));
}

int RandClass::nextAltNormal(int minInput, int maxInput) {
	std::normal_distribution<double> distribution((minInput + maxInput) / 2, (maxInput - minInput) / 6);
	return static_cast<int>(distribution(generator));
}

/*int RandClass::nextNormal(double mean, double stddev) {
	std::uniform_int_distribution<int> distribution(minInput, maxInput);
	return distribution(generator);
}*/
