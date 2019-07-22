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

//Part of this code is based on the code provided on Stack Exchange (https://gamedev.stackexchange.com/a/128912) by zebleckDAMM (https://gamedev.stackexchange.com/users/90326/zebleckdamm)

#include "CreatePlanet.h"

using std::string;
using std::endl;
using std::vector;

const vector<vector<int>> CreatePlanet::colors = {
	{0, 0, 0, 0},
	{34, 177, 76, 255},
	{185, 122, 87, 255},
	{127, 127, 127, 255}
};

CreatePlanet::CreatePlanet(int seedInput, int diameterInput) {
	seed = seedInput;
	diameter = diameterInput;
	if (diameter <= 100) {
		frequency = 0.015;
		end = 500;
	} else {
		frequency = 0.015;
		end = 500;
	}
	myNoise.SetSeed(seed);
	myNoise.SetNoiseType(FastNoise::Simplex);
	myNoise.SetFrequency(frequency);
	planetVector.clear();
	planetVector.resize(diameter, vector<uint8_t>(diameter, 0));
	CreatePlanet::generate();
}

CreatePlanet::CreatePlanet(int seedInput, int diameterInput, int endInput, double frequencyInput) {
	seed = seedInput;
	diameter = diameterInput;
	frequency = frequencyInput;
	myNoise.SetSeed(seed);
	myNoise.SetNoiseType(FastNoise::Simplex);
	myNoise.SetFrequency(frequency);
}

void CreatePlanet::generate() {
	CreatePlanet::addLayer(0, 0);
}

void CreatePlanet::addLayer(uint8_t outerMaterial, uint8_t innerMaterial, double sharpMult, double adjustedMin) {
	RadialGradient<double> gradient;
	gradient.sharpRadialGradient(diameter, diameter, 0, 1, sharpMult);

	vector<vector<double>> values(diameter, vector<double>(diameter, 0));

	int startX = 0;
	int endX = end;
	int startY = 0;
	int endY = end;

	double noiseMin = 0;
	double noiseMax = 0;

	for (int i = 0; i < diameter; i++) {
		for (int j = 0; j < diameter; j++) {
			int x = (startX + i * ((endX - startX) / diameter));
			int y = (startY + j * ((endY - startY) / diameter));
			values[i][j] = 0.5 * (myNoise.GetNoise(x, y) + 1);  // Puts it in the range of 0 to 1

			if (values[i][j] > noiseMax) {
				noiseMax = values[i][j];
			}
		}
	}

	double lowN = values[0][0];
	double highN = values[0][0];

	for (int i = 0; i < diameter; i++) {
		for (int j = 0; j < diameter; j++) {
			values[i][j] = (values[i][j] - noiseMin) / (noiseMax - noiseMin);  // Normalizing

			if (values[i][j] < lowN) {
				lowN = values[i][j];
			}
			if (values[i][j] > highN) {
				highN = values[i][j];
			}
		}
	}


	for (int i = 0; i < diameter; i++) {
		for (int j = 0; j < diameter; j++) {
			values[i][j] = CreatePlanet::adjustRange(values[i][j], lowN, highN, adjustedMin, 1.0);

			values[i][j] = std::max(0.0, values[i][j] - gradient.gradient[i][j]);
		}
	}

	for (int y = 0; y < diameter; y++) {
		for (int x = 0; x < diameter; x++) {
			if (values[y][x] == 0.0) {  // Could be like < 0.1
				planetVector[y][x] = 0;
			} else if (values[y][x] < 0.4) {
				bool surface = false;
				for (int i = 0; i < 3 && !surface; i++) {  // Checks a 3x3 grid to see if any empty space is nearby
					for (int j = 0; j < 3; j++) {
						int gridY = y - 1 + i;
						int gridX = x - 1 + j;
						if (gridY < 0 || gridX < 0) {
							surface = true;
							break;
						}

						if (gridY >= values.size() || gridX >= values[y].size()) {
							surface = true;
							break;
						}

						if (values[gridY][gridX] == 0) {
							surface = true;
							break;
						}
					}
				}
				if (surface) {
					planetVector[y][x] = 1;
				} else {
					planetVector[y][x] = 2;
				}
			} else {
				planetVector[y][x] = 3;
			}
		}
	}
}

double CreatePlanet::adjustRange(double oldNum, double oldMin, double oldMax, double newMin, double newMax) {
	return ((((newMax - newMin) * (oldNum - oldMin)) / (oldMax - oldMin)) + newMin);
}

/*void printPlanet(const vector<vector<double>> myVector, string fileName) {
	std::ofstream myFile;
	myFile.open("output/" + fileName + ".ppm");
	myFile << "P3";
	myFile << " ";
	myFile << myVector[0].size();
	myFile << " ";
	myFile << myVector.size();
	myFile << " ";
	myFile << 255;
	myFile << "\n";

	for (int y = 0; y < myVector.size(); y++) {
		for (int x = 0; x < myVector[0].size(); x++) {
			//cout << "testVector[" << i << "][" << j << "] == " << testVector[i][j] << endl;
			//myFile << "255 0 ";
			//myFile << static_cast<int>(adjustRange(myVector[i][j], min, max, 0, 255));
			//myFile << " ";
			//myFile << static_cast<int>(adjustRange(myVector[i][j], min, max, 0, 255));
			//myFile << " ";
			//myFile << static_cast<int>(adjustRange(myVector[i][j], min, max, 0, 255));
			//myFile << " ";
			if (myVector[y][x] == 0.0) {  // Could be like < 0.1
				myFile << "0 0 0 ";
			} else if (myVector[y][x] < 0.4) {
				bool surface = false;
				for (int i = 0; i < 3 && !surface; i++) {  // Checks a 3x3 grid to see if any empty space is nearby
					for (int j = 0; j < 3; j++) {
						int gridY = y - 1 + i;
						int gridX = x - 1 + j;
						if (gridY < 0 || gridX < 0) {
							surface = true;
							break;
						}

						if (gridY >= myVector.size() || gridX >= myVector[y].size()) {
							surface = true;
							break;
						}

						if (myVector[gridY][gridX] == 0) {
							surface = true;
							break;
						}
					}
				}
				if (surface) {
					myFile << "34 177 76 ";
				} else {
					myFile << "185 122 87 ";
				}
				
			} else {
				myFile << "127 127 127 ";
			}
		}
		myFile << "\n";
	}
	myFile.close();	
}

void grayscaleVectorToPPM(const vector<vector<double>> myVector, string fileName) {
	double max = std::numeric_limits<double>::lowest();

	double min = std::numeric_limits<double>::max();

	for (int i = 0; i < myVector.size(); i++) {
		max = std::max(max, *std::max_element(std::begin(myVector[i]), std::end(myVector[i])));
		min = std::min(min, *std::min_element(std::begin(myVector[i]), std::end(myVector[i])));
	}

	// cout << max << endl;
	// cout << min << endl;

	std::ofstream myFile;
	myFile.open("output/" + fileName + ".ppm");
	myFile << "P3";
	myFile << " ";
	myFile << myVector[0].size();
	myFile << " ";
	myFile << myVector.size();
	myFile << " ";
	myFile << 255;
	myFile << "\n";

	for (int i = 0; i < myVector.size(); i++) {
		for (int j = 0; j < myVector[0].size(); j++) {
			//cout << "testVector[" << i << "][" << j << "] == " << testVector[i][j] << endl;
			//myFile << "255 0 ";
			myFile << static_cast<int>(adjustRange(myVector[i][j], min, max, 0, 255));
			myFile << " ";
			myFile << static_cast<int>(adjustRange(myVector[i][j], min, max, 0, 255));
			myFile << " ";
			myFile << static_cast<int>(adjustRange(myVector[i][j], min, max, 0, 255));
			myFile << " ";
		}
		myFile << "\n";
	}
	myFile.close();
}
*/
