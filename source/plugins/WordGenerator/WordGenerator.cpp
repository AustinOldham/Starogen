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
using std::vector;
using std::list;

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
	// TODO: Ensure this works on Linux and Mac.
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
		cout << "You probably forgot to copy the config directory over" << endl;
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

string WordGenerator::nextWordFromSeed(unsigned int seedInput) {
	return nextWordFromSeed(to_string(seedInput));
}

string WordGenerator::nextWordFromSeed(string seedInput) {
	return nextWordFromSeed(seedInput, -1, -1);
}

string WordGenerator::nextWordFromSeed(unsigned int seedInput, int minLength, int maxLength) {
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
			if (usesCensoredWordsList && containsCensoredWord(word + nextSyllable)) {
				return generateWord(rand, randSyllable, minLength, maxLength);
			} else {
				// In the future, make a simple dictionary of the basic vowels (aeiouy) and checks if each letter belongs in that dictionary. If one does, return the word, otherwise, recurse until a vowel is found.
				return (word + nextSyllable);
			}

		} else if ((word + nextSyllable).size() > localMaxLength) {
			// This can be optimized by sorting the syllables by length and only choosing one that fits.
			nextSyllable = getRandomSyllable(randSyllable, currentIsConsonant);
			continue;
		}
		word = word + nextSyllable;
		currentIsConsonant = !currentIsConsonant;
		nextSyllable = getRandomSyllable(randSyllable, currentIsConsonant);
	}
}

bool WordGenerator::containsCensoredWord(string wordInput) {
	for (auto const& censoredWord : censoredWordsList) {
		if (wordInput.find(censoredWord) != std::string::npos) {
			return true;  // Contains the censored word.
		}
	}
	return false;  // Does not contain a censored word.
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

string WordGenerator::getName(unsigned int keyInput) {
	return getName(to_string(keyInput));
}

string WordGenerator::getName(string keyInput) {
	return getName(keyInput, -1, -1);
}

string WordGenerator::getName(unsigned int keyInput, int minLength, int maxLength) {
	return getName(to_string(keyInput), minLength, maxLength);
}

string WordGenerator::getName(string keyInput, int minLength, int maxLength) {
	string name = retrieveName(keyInput);
	string suffix = "";
	int loops = 0;
	if (!name.empty()) {
		return name;
	} else {
		do {
			if (loops == 3) {
				break;
			}
			name = generateWord(randomGen, syllableSelector, minLength, maxLength);
			loops++;
		} while (isNameTaken(name));
		if (loops == 3) {
			do {
				suffix = getGreekLettersFromNumber(loops - 2, " ");  // Starts with Beta.
				loops++;
			} while (isNameTaken(name + " " + suffix));
			name = name + " " + suffix;
		}
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

list<int> WordGenerator::base10ToArbitraryBase(int input, int base) {
	list<int> output;
	if (input == 0) {
		output.push_front(0);
		return output;
	}
	while (input > 0) {
		output.push_front(input % base);
		input = input / base;
	}
	return output;
}

string WordGenerator::getGreekLettersFromNumber(int input, string delimiter) {
	string output = "";
	list<int> convertedNumber = base10ToArbitraryBase(input, greekAlphabet.size());
	for (auto it = convertedNumber.cbegin(); it != convertedNumber.cend(); it++) {
		output = output + greekAlphabet[*it];
		if (std::next(it) != convertedNumber.cend()) {
			output = output + delimiter;
		}
	}
	return output;
}

bool WordGenerator::setCensoredWordsPath(string pathInput) {
	censoredWordsPath = pathInput;
	censoredWordsList.clear();
	if (censoredWordsPathEmpty()) {
		usesCensoredWordsList = false;
		return true;
	} else {
		usesCensoredWordsList = true;
		return readCensoredWordsFiles();
	}
}

bool WordGenerator::censoredWordsPathEmpty() {
	std::filesystem::path dir(censoredWordsPath);
	dir.make_preferred();
	return(std::filesystem::is_empty(dir));  // Checks if any files are present in that directory.
}

bool WordGenerator::readCensoredWordsFiles() {
	cout << "Loading censored words lists" << endl;

	std::filesystem::path dir(censoredWordsPath);
	dir.make_preferred();

	for (const auto & file : std::filesystem::directory_iterator(dir)) {
		std::ifstream censoredWordsIn(file.path());
		cout << "Reading " << file.path() << endl;
		if (censoredWordsIn.is_open()) {
			string line;
			while (std::getline(censoredWordsIn, line)) {
				if (!line.empty()) {
					if (line.front() == '#') {
						continue;
					}
					if (line.back() == '\r') {  // Removes the carriage return character on Linux.
						line.pop_back();
					}
					cout << line << endl;
					censoredWordsList.push_back(line);
				}
			}
			censoredWordsIn.close();
		} else {
			return false;
		}
	}


	cout << "Done reading censored words" << endl;
	return true;
}

bool WordGenerator::clearNames() {
	usedNames.clear();
	return true;
}
