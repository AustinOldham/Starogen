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

#ifndef WORDGENERATOR_H
#define WORDGENERATOR_H

#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "RandClass/RandClass.h"


// TODO: Add a random distribution based on the seed to allow for different looking languages.

class WordGenerator {
	private:
		RandClass randomGen;
		// RandClass tempRandomGen;
		RandClass syllableSelector;  // This may be unnecessary.
		// RandClass tempSyllableSelector;

		std::vector<std::string> consonantSyllables;
		std::vector<std::string> vowelSyllables;
		std::vector<std::string> combinedSyllables;

		std::vector<std::string> censoredWordsList;

		std::unordered_map<std::string, std::string> usedNames;

		const int maxConsecutiveConsonants = 5;
		int defaultMaxLength;  // This is a loose maximum since additional characters may need to be added in the case where there are many names already.
		int defaultMinLength;

		bool usesCensoredWordsList;

		std::string censoredWordsPath;

		bool readSyllableFiles();
		bool readConsonantSyllableFile(std::string filePathInput);
		bool readVowelSyllableFile(std::string filePathInput);
		std::string generateWord(RandClass& rand, RandClass& randSyllable, int minLength, int maxLength);  // The default minimum length is 1 character.

	public:
		WordGenerator();
		explicit WordGenerator(std::string seedInput);

		const std::vector<std::string> greekAlphabet = {
			"Alpha",
			"Beta",
			"Gamma",
			"Delta",
			"Epsilon",
			"Zeta",
			"Eta",
			"Theta",
			"Iota",
			"Kappa",
			"Lambda",
			"Mu",
			"Nu",
			"Xi",
			"Omicron",
			"Pi",
			"Rho",
			"Sigma",
			"Tau",
			"Upsilon",
			"Phi",
			"Chi",
			"Psi",
			"Omega"
		};

		std::string nextWord();
		std::string nextWord(int minLength, int maxLength);
		std::string nextWordFromSeed(std::string seedInput);  // This function uses a separate random number generator.
		std::string nextWordFromSeed(int seedInput);
		std::string nextWordFromSeed(std::string seedInput, int minLength, int maxLength);
		std::string nextWordFromSeed(int seedInput, int minLength, int maxLength);

		// std::string getName();
		// std::string getName(int minLength);
		std::string getName(std::string keyInput);
		std::string getName(int keyInput);
		std::string getName(std::string keyInput, int minLength, int maxLength);
		std::string getName(int keyInput, int minLength, int maxLength);

		std::string getNameFromSeed(std::string keyInput, std::string seedInput);
		std::string getNameFromSeed(int keyInput, std::string seedInput);
		std::string getNameFromSeed(std::string keyInput, std::string seedInput, int minLength, int maxLength);
		std::string getNameFromSeed(int keyInput, std::string seedInput, int minLength, int maxLength);

		std::string getSatelliteName(std::string primaryBodyName);  // Names the planet of a star by appending a Roman numeral.

		std::list<int> base10ToArbitraryBase(int input, int base);
		std::string getGreekLettersFromNumber(int number, std::string delimiter);

		  // This function uses a separate random number generator.

		std::string translateWord();  // This will share the same list of used words as getName() and will be used for dialogue.

		std::string getRandomCombinedSyllable(RandClass& randSyllable);
		std::string getRandomSyllable(RandClass& randSyllable, bool isVowelInput);
		std::string getRandomVowelSyllable(RandClass& randSyllable);
		std::string getRandomConsonantSyllable(RandClass& randSyllable);
		bool isConsonant(std::string currSyllable);

		bool setDefaultMaxLength(int maxLengthInput);
		bool setDefaultMinLength(int minLengthInput);

		bool setCensoredWordsPath(std::string pathInput);

		bool setSeed(std::string seedInput);

		int getConsecutiveConsonantNum(RandClass& rand);

		std::string retrieveName(std::string keyInput);
		bool isNameTaken(std::string nameInput);
};

#endif  // WORDGENERATOR_H
