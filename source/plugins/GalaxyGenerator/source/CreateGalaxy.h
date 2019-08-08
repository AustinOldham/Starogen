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

#ifndef CREATEGALAXY_H
#define CREATEGALAXY_H

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

class CreateGalaxy {
	private:
		RandClass starClusterGen;
		FastNoise cloudNoise;

		struct StarInfo;
		std::vector<StarInfo> starList;

		std::vector<std::vector<int>> myGalaxy;
		std::vector<std::vector<double>> densityMap;
		std::vector<std::vector<double>> clouds;

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
		//void printWhiteGalaxy(const std::vector<std::vector<int>> myVector, std::string fileName);
		//void printGalaxy(const std::vector<std::vector<int>> myVector, std::string fileName);
		//void printDensityMap(const std::vector<std::vector<double>> myVector, std::string fileName);
		//void printClouds(const std::vector<std::vector<double>> myVector, std::string fileName);
		//void printColorPalette(std::string fileName);
		void initializeContainers();
		std::vector<StarInfo> readStarFile(std::string fileName);
		//std::vector<std::vector<std::string>> readFile(std::string fileName);
		//std::vector<std::string> splitString(const std::string &s, char delimiter);
		//std::unordered_map<std::string, int> getIDMap();
		//std::vector<std::string> getNumToString();
		void getProbabilities();
		//std::vector<std::vector<float>> getColors();

	public:
		const double PI = std::atan(1.0)*4;

		CreateGalaxy();

		// NOTE: The default arguments will likely be removed and instead be the default in the game.
		void generate(std::string nameInput, std::string seedInput = "", int pixelsInput = 500, double cloudsFrequencyInput = 0.05, int armsInput = -1, double radialDistanceMultInput = -1.0, double clusterStddevInput = -1.0, double densityInput = -1.0, double aInput = 0.1, double bInput = 0.3, int extraStarsInput = -1, int densityGridInput = -1, double cloudsMultInput = -1.0);

		int at(int x, int y);
		float getRed(int index);
		float getGreen(int index);
		float getBlue(int index);
		float getAlpha(int index);
		int getPixels();
};

struct CreateGalaxy::StarInfo {
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

#endif  // CREATEGALAXY_H