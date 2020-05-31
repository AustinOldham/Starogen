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

#include "WordGenerator.h"

using std::string;
using std::to_string;

WordGenerator::WordGenerator() {}

WordGenerator::WordGenerator(string seedInput) : randomGen(seedInput), syllableSelector(seedInput) {}

string WordGenerator::nextWord() {
	return nextWord(-1, -1);
}

string WordGenerator::nextWord(int minLength, int maxLength) {
	return generateWord(randomGen, syllableSelector, minLength, maxLength);
}

string WordGenerator::nextWordFromSeed(int seedInput) {
	return nextWordFromSeed(to_string(seedInput));
}

string WordGenerator::nextWordFromSeed(string seedInput) {
	return nextWordFromSeed(seedInput, -1, -1);
}

string nextWordFromSeed(int seedInput, int minLength, int maxLength) {
	return nextWordFromSeed(to_string(seedInput), minLength, maxLength);
}

string nextWordFromSeed(string seedInput, int minLength, int maxLength) {
	RandomGen tempRandomGen(seedInput);
	RandomGen tempSyllableSelector(seedInput);
	return generateWord(tempRandomGen, minLength, maxLength);
}

string generateWord(rand, randSyllable, minLength, maxLength) {
	
}
