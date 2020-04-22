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

#ifndef CREATEUNIVERSE_H
#define CREATEUNIVERSE_H

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cassert>
#include <functional>


#include <iomanip>
// delete this later


#include <nlohmann/json.hpp>
#include "RandClass/RandClass.h"
#include "FastNoise/FastNoise.h"

class CreateUniverse {
	private:
		class Galaxy {
			private:
				struct StarType;
				RandClass starClusterGen;
				FastNoise galacticCloudNoise;

				std::vector<std::vector<int>> galaxyMap;
				std::vector<std::vector<double>> densityMap;
				std::vector<std::vector<double>> galacticClouds;
				std::vector<StarType> starList;

				std::string name;
				std::string seed;
				int pixels;  // Width of the galaxy
				//double coreLocation;  // Proportion of the distance between the center and the edge that makes up the core (currently unused).
				int arms;
				double radialDistanceMult;
				double clusterStddev;
				double density;
				double a;
				double b;
				bool extraStars;
				int densityGrid;
				double cloudsMult;

				void generate();
				void createDensityMap();
				void createClouds();
				void starCluster(int x, int y, int num, double stddev, double distanceProportion);
				int plotStar(double distanceProportion);
				std::vector<double> getAngles(int num, double additional);
				std::string getName(std::string nameInput);
				std::string getSeed(std::string seedInput);
				int getArms(int armsInput);
				double getClusterStddev(double clusterStddevInput);
				double getRadialDistanceMult(double radialDistanceMultInput);
				double getDensity(double densityInput);
				double getA(double aInput);
				double getB(double bInput);
				bool getExtraStars(int extraStarsInput);
				int getDensityGrid(int densityGridInput);
				double getCloudsMult(double cloudsMultInput);
				double getMult(double t, double a, double b);
				double logSpiralX(double t, double theta, double a, double b);
				double logSpiralY(double t, double theta, double a, double b);
				double logSpiralX(double t, double theta, double mult);
				double logSpiralY(double t, double theta, double mult);
				bool isFinished(std::vector<bool> finished);
				double radialDistance(int x, int y, double centerX, double centerY);

				void initializeContainers();
				std::vector<StarType> readStarFile(std::string fileName);

				void getProbabilities();


			public:
				const double PI = std::atan(1.0)*4;

				Galaxy();

				// NOTE: The default arguments will likely be removed and instead be the default in the game.
				void generate(std::string nameInput, std::string seedInput = "", int pixelsInput = 500, double cloudsFrequencyInput = 0.05, int armsInput = -1, double radialDistanceMultInput = -1.0, double clusterStddevInput = -1.0, double densityInput = -1.0, double aInput = 0.1, double bInput = 0.3, int extraStarsInput = -1, int densityGridInput = -1, double cloudsMultInput = -1.0);

				int starAtPosition(int x, int y);
				float getRed(int index);
				float getGreen(int index);
				float getBlue(int index);
				float getAlpha(int index);
				int getPixels();

				void saveGalaxy();
		};

		class Planet {
			std::string name;
			std::string seed;
		};

		class Star {
			std::string name;
			std::string seed;

			int starTypeID;

			std::vector<Planet> thePlanets;
		};
		



	public:
		Galaxy myGalaxy;
		Star currentStar;				
};



struct CreateUniverse::Galaxy::StarType {
	std::string name;
	std::string type;

	// int id;
	double chance;
	double adjustedChance;

	float red;
	float green;
	float blue;
	float alpha;
};






#endif  // CREATEUNIVERSE_H