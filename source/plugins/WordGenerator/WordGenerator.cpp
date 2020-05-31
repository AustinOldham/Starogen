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
using std::cout;
using std::endl;

WordGenerator::WordGenerator() : defaultMinLength(1), defaultMaxLength(20) {
	readSyllableFiles();
}

WordGenerator::WordGenerator(string seedInput) : defaultMinLength(1), defaultMaxLength(20), randomGen(seedInput), syllableSelector(seedInput) {
	readSyllableFiles();
}

bool WordGenerator::readSyllableFiles() {
	bool consonantFileSuccessful = readConsonantSyllableFile("config/consonant_syllables.txt");
	bool vowelFileSuccessful = readVowelSyllableFile("config/vowel_syllables.txt");
	if (consonantFileSuccessful && vowelFileSuccessful) {
		combinedSyllables = consonantSyllables;
		combinedSyllables.insert(combinedSyllables.end(), vowelSyllables.begin(), vowelSyllables.end());
	}
	return (consonantFileSuccessful && vowelFileSuccessful);
}

bool WordGenerator::readConsonantSyllableFile(string filePathInput) {
	std::ifstream consonantsIn(filePathInput);
	cout << "Reading consonants" << endl;
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
				cout << line << endl;
				consonantSyllables.push_back(line);
			}
		}
		consonantsIn.close();
	} else {
		return false;
	}
	cout << "Done reading consonants" << endl;
	return true;
}

bool WordGenerator::readVowelSyllableFile(string filePathInput) {
	std::ifstream vowelsIn(filePathInput);
	cout << "Reading vowels" << endl;
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
				cout << line << endl;
				vowelSyllables.push_back(line);
			}
		}
		vowelsIn.close();
	} else {
		return false;
	}
	cout << "Done reading vowels" << endl;
	return true;
}

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

string WordGenerator::nextWordFromSeed(int seedInput, int minLength, int maxLength) {
	return nextWordFromSeed(to_string(seedInput), minLength, maxLength);
}

string WordGenerator::nextWordFromSeed(string seedInput, int minLength, int maxLength) {
	RandClass tempRandomGen(seedInput);
	RandClass tempSyllableSelector(seedInput);
	return generateWord(tempRandomGen, tempSyllableSelector, minLength, maxLength);
}

string WordGenerator::generateWord(RandClass& rand, RandClass& randSyllable, int minLength, int maxLength) {
	if (minLength == -1) {
		minLength = defaultMinLength;
	}
	if (maxLength == -1) {
		maxLength = defaultMaxLength;
	}
	int localMaxLength = rand.next(minLength, maxLength);
	string word = "";
	string nextSyllable = getRandomCombinedSyllable(randSyllable);
	bool currentIsConsonant = isConsonant(nextSyllable);
	while (true) {
		// Add a loop that loops through this getConsecutiveConsonantNum() times.
		if ((word + nextSyllable).size() == localMaxLength) {
			// In the future, make a simple dictionary of the basic vowels (aeiouy) and checks if each letter belongs in that dictionary. If one does, return the word, otherwise, recurse until a vowel is found.
			return (word + nextSyllable);
		} else if ((word + nextSyllable).size() > localMaxLength) {
			nextSyllable = getRandomSyllable(randSyllable, currentIsConsonant);
			continue;
		}
		word = word + nextSyllable;
		currentIsConsonant = !currentIsConsonant;
		nextSyllable = getRandomSyllable(randSyllable, currentIsConsonant);
	}
}

string WordGenerator::getRandomSyllable(RandClass& randSyllable, bool isConsonantInput) {
	if (isConsonantInput) {
		return getRandomConsonantSyllable(randSyllable);
	} else {
		return getRandomVowelSyllable(randSyllable);
	}
}

string WordGenerator::getRandomVowelSyllable(RandClass& randSyllable) {
	int index = randSyllable.next(0, vowelSyllables.size() - 1);
	return vowelSyllables[index];
}

string WordGenerator::getRandomConsonantSyllable(RandClass& randSyllable) {
	int index = randSyllable.next(0, consonantSyllables.size() - 1);
	return consonantSyllables[index];
}

string WordGenerator::getRandomCombinedSyllable(RandClass& randSyllable) {
	int index = randSyllable.next(0, combinedSyllables.size() - 1);
	return combinedSyllables[index];
}

bool WordGenerator::isConsonant(string currSyllable) {
	if (std::find(consonantSyllables.begin(), consonantSyllables.end(), currSyllable) != consonantSyllables.end()) {
		return true;
	} else {
		return false;
	}
}

int WordGenerator::getConsecutiveConsonantNum(RandClass& rand) {
	int num = static_cast<int>(rand.nextNormal(0, 1));  // Maybe set the standard deviation to 0.5 and make the minimum 1 by adding 1 to the result.
	if (num < 0) {
		num = num * (-1);
	}
	if (num > maxConsecutiveConsonants) {
		num = maxConsecutiveConsonants;
	}
	return num;
}

bool WordGenerator::setSeed(string seedInput) {
	// If random syllable frequencies are used, they must be updated when the seed is changed.
	randomGen.setSeed(seedInput);
	syllableSelector.setSeed(seedInput);
	return true;
}

/*string WordGenerator::getName() {
	return getName(-1, -1);
}

string WordGenerator::getName(int minLength, int maxLength) {
	return generateWord(randomGen, syllableSelector, minLength, maxLength);
}*/

string WordGenerator::getName(int keyInput) {
	return getName(to_string(keyInput));
}

string WordGenerator::getName(string keyInput) {
	return getName(keyInput, -1, -1);
}

string WordGenerator::getName(int keyInput, int minLength, int maxLength) {
	return getName(to_string(keyInput), minLength, maxLength);
}

string WordGenerator::getName(string keyInput, int minLength, int maxLength) {
	string name = retrieveName(keyInput);
	if (!name.empty()) {
		return name;
	} else {
		do {
			name = generateWord(randomGen, syllableSelector, minLength, maxLength);
		} while (isNameTaken(name));
	}
	usedNames[keyInput] = name;
	return name;
}

string WordGenerator::retrieveName(string keyInput) {
	auto search = usedNames.find(keyInput);
	if (search != usedNames.end()) {
		return (search->second);
	} else {
		return "";
	}
}

bool WordGenerator::isNameTaken(string nameInput) {
	for (auto keyValuePair : usedNames) {
		if (nameInput.compare(keyValuePair.second) == 0) {
			return true;  // Name is taken.
		}
	}
	return false;
}
