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

#ifndef PLANETGENERATOR_RANDCLASS_H
#define PLANETGENERATOR_RANDCLASS_H

#include <iostream>
#include <random>
#include <string>
#include <ctime>

class RandClass {
	private:
		std::mt19937 generator;
		std::string seed;
		int min;
		int max;
	public:
		RandClass();
		RandClass(std::string);
		RandClass(std::string seedInput, int minInput, int maxInput);
		RandClass(int, int);
		void setSeed();
		void setSeed(std::string);
		void printInfo();
		int next();
		int next(int, int);
		double next(double minInput, double maxInput);
		double nextNormal(double mean, double stddev);
		int nextAltNormal();
		int nextAltNormal(int minInput, int maxInput);
};

#endif  // PLANETGENERATOR_RANDCLASS_H
