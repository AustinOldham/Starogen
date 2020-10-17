//Copyright (C) 2020  Austin Oldham
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

#include "CustomDiscreteDistribution.h"

using std::cout;
using std::string;
using std::vector;

CustomDiscreteDistribution::CustomDiscreteDistribution() {
	seed = std::to_string(std::time(0));
	CustomDiscreteDistribution::setSeed();
}

CustomDiscreteDistribution::CustomDiscreteDistribution(string seedInput) {
	seed = seedInput;
	CustomDiscreteDistribution::setSeed();
}

void CustomDiscreteDistribution::setSeed() {
	std::seed_seq mySeed(seed.begin(), seed.end());
	generator.seed(mySeed);
}

void CustomDiscreteDistribution::setSeed(string inputSeed) {
	seed = inputSeed;
	CustomDiscreteDistribution::setSeed();
}

void CustomDiscreteDistribution::setWeights(vector<int> weightsVector) {
	distribution = std::discrete_distribution<int>(weightsVector.begin(), weightsVector.end());
}

int CustomDiscreteDistribution::next() {
	return distribution(generator);
}
