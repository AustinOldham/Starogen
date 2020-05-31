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

bool WordGenerator::readSyllableFiles() {
	bool consonantFileSuccessful = readSyllableFiles("config/consonant_syllables.txt");
	bool vowelFileSuccessful = readSyllableFiles("config/vowel_syllables.txt");
	return (consonantFileSuccessful && vowelFileSuccessful);
}

bool WordGenerator::readConsonantSyllableFile(string filePathInput) {
	std::ifstream consonantsIn(filePathInput);
	if (consonantsIn.is_open()) {
		string line;
		while (std::getline(consonantsIn, line)) {
			if (!line.empty()) {
				if (line.front() == '#') {
					continue;
				}
				if (line.back() == '\r') {  // Removes the carriage return character on Linux.
					line.pop_back();
				}
				consonantSyllables.push_back(line);
			}
		}
		consonantsIn.close();
	} else {
		return false;
	}
}

bool WordGenerator::readVowelSyllableFile(string filePathInput) {
	std::ifstream vowelsIn(filePathInput);
	if (vowelsIn.is_open()) {
		string line;
		while (std::getline(vowelsIn, line)) {
			if (!line.empty()) {
				if (line.front() == '#') {
					continue;
				}
				if (line.back() == '\r') {  // Removes the carriage return character on Linux.
					line.pop_back();
				}
				vowelSyllables.push_back(line);
			}
		}
		vowelsIn.close();
	} else {
		return false;
	}	
}

string WordGenerator::nextWord() {
	return nextWord(1, -1);
}

string WordGenerator::nextWord(int minLength, int maxLength) {
	return generateWord(randomGen, syllableSelector, minLength, maxLength);
}

string WordGenerator::nextWordFromSeed(int seedInput) {
	return nextWordFromSeed(to_string(seedInput));
}

string WordGenerator::nextWordFromSeed(string seedInput) {
	return nextWordFromSeed(seedInput, 1, -1);
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
	// A length of -1 means the length requirement is ignored.
}
