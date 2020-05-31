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
#include <fstream>
#include <algorithm>

#include "RandClass/RandClass.h"


// TODO: Add a random distribution based on the seed to allow for different looking languages.

class WordGenerator {
	private:
		RandClass randomGen;
		// RandClass tempRandomGen;
		RandClass syllableSelector;  // This may be unnecessary.
		// RandClass tempSyllableSelector;

		vector<std::string> consonantSyllables;
		vector<std::string> vowelSyllables;
		vector<std::string> combinedSyllables;

		vector<std::string> censoredWordsList;

		const int maxConsecutiveConsonants = 5;
		int defaultMaxLength;
		int defaultMinLength;

		bool usesCensoredWordsList;

		std::string censoredWordsPath;

		bool readSyllableFiles();
		bool readConsonantSyllableFile(std::string filePathInput);
		bool readVowelSyllableFile(std::string filePathInput);
		std::string generateWord(RandClass rand, RandClass randSyllable, int minLength, int maxLength); // The default minimum length is 1 character.

	public:
		WordGenerator();
		explicit WordGenerator(std::string seedInput);

		std::string nextWord();
		std::string nextWord(int minLength, int maxLength);
		std::string nextWordFromSeed(std::string seedInput);  // This function uses a separate random number generator.
		std::string nextWordFromSeed(int seedInput);
		std::string nextWordFromSeed(std::string seedInput, int minLength, int maxLength);
		std::string nextWordFromSeed(int seedInput, int minLength, int maxLength);

		std::string getRandomCombinedSyllable(RandClass randSyllable);
		bool isConsonant(std::string currSyllable);

		bool setDefaultMaxLength(int maxLengthInput);
		bool setDefaultMinLength(int minLengthInput);

		bool setCensoredWordsPath(std::string pathInput);

		int getConsecutiveConsonantNum();
};

#endif  // WORDGENERATOR_H
