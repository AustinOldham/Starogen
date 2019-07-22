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

#ifndef CREATEPLANET_H_
#define CREATEPLANET_H_

#include <random>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include <cstdint>

#include "FastNoise/FastNoise.h"
#include "RadialGradient/RadialGradient.h"


class CreatePlanet {
	public:
		std::vector<std::vector<uint8_t>> planetVector;
		//static char colors[][3];
		static const std::vector<std::vector<int>> colors;

		CreatePlanet(int seedInput, int diameterInput);
		CreatePlanet(int seedInput, int diameterInput, int endInput, double frequencyInput);




	private:
		int seed;
		int diameter;
		int end;
		double frequency;
		FastNoise myNoise;

		void generate();
		void addLayer(uint8_t outerMaterial, uint8_t innerMaterial, double sharpMult = 0.5, double adjustedMin = 0.7);
		double adjustRange(double oldNum, double oldMin, double oldMax, double newMin, double newMax);
};

#endif  // CREATEPLANET_H_
