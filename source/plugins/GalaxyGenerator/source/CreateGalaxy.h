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

		struct StarType;
		class Galaxy;
		class Star;
		class Planet;
		std::vector<StarType> starList;

		std::vector<std::vector<int>> myGalaxy;
		std::vector<std::vector<double>> densityMap;
		std::vector<std::vector<double>> clouds;

		std::string name;
		std::string seed;
		int pixels;  // Stores the width of the galaxy.
		//double coreLocation;  // Proportion of the distance between the center and the edge that makes up the core (currently unused).
		int arms;  // Stores the number of arms the spiral galaxy should have.
		double radialDistanceMult;  // Changes the density of stars (this should be replaced with some type of "base density" constant since densityMult basically does the same thing).
		double clusterStddev;  // The standard deviation of the random offset applied to each star when a cluster is placed.
		double density;  // Arbitrary value of the density of stars (in the current implementation, increases the total number of star clusters).
		double spiralA;  // Arbitrary value that influences the shape of the spiral.
		double spiralB;  // Rate of increase of the spiral (arbitrary value, can be calculated with b = cot(alpha) where alpha is the angle between the radius and the tangent).
		bool extraStars;  // Whether or not an extra, less dense cluster of stars is added. TODO: Add extra variables that control the density and number of stars added.
		// int densityGrid;
		double cloudsFrequency;
		double cloudsMult;
		double densityMult;

		void generate();
		void createApproximateDensityMap();
		void createClouds();
		void starCluster(int x, int y, int num, double stddev, double distanceProportion);
		int plotStar(double distanceProportion);
		std::vector<double> calculateAngles(int num, double additional);
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
		std::vector<StarType> readStarFile(std::string fileName);
		//std::vector<std::vector<std::string>> readFile(std::string fileName);
		//std::vector<std::string> splitString(const std::string &s, char delimiter);
		//std::unordered_map<std::string, int> getIDMap();
		//std::vector<std::string> getNumToString();
		void getProbabilities();  // This may be removed when discrete_distribution is used.
		//std::vector<std::vector<float>> getColors();

	public:
		const double PI = std::atan(1.0)*4;

		CreateGalaxy();

		// NOTE: The default arguments will likely be removed and instead be the default in the game.
		// TODO: Replace this long list of parameters with individual setters in order to improve readability.
		void run(std::string nameInput, std::string seedInput = "", int pixelsInput = 500, double cloudsFrequencyInput = 0.05, int armsInput = -1, double radialDistanceMultInput = -1.0, double clusterStddevInput = -1.0, double densityInput = -1.0, double aInput = 0.1, double bInput = 0.3, int extraStarsInput = -1, int densityGridInput = -1, double cloudsMultInput = -1.0, double densityMultInput = 1.0);

		int at(int x, int y);

		float getRed(int index);
		float getGreen(int index);
		float getBlue(int index);
		float getAlpha(int index);

		int getPixels();
		int getArms();

		bool setName(std::string nameInput);
		bool setSeed(std::string seedInput);
		bool setPixels(int pixelsInput);
		bool setCloudsFrequency(double cloudsFrequencyInput);
		bool setArms(int armsInput);
		bool setRadialDistanceMult(double radialDistanceMultInput);
		bool setClusterStddev(double clusterStddevInput);
		bool setDensity(double densityInput);
		bool setSpiralA(double spiralAInput);
		bool setSpiralB(double spiralBInput);
		bool setExtraStars(int extraStarsInput);
		// bool setDensityGrid(int densityGridInput);
		bool setCloudsMult(double cloudsMultInput);
		bool setDensityMult(double densityMultInput);

		std::string suggestName();
		std::string suggestSeed();
		double suggestClusterStddev();
		double suggestRadialDistanceMult();
		double suggestDensity();
		double suggestSpiralA();
		double suggestSpiralB();
		bool suggestExtraStars();
		double suggestCloudsMult();

		void saveGalaxy();
};

struct CreateGalaxy::StarType {
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

// TODO: Put this in a completely separate file.
class CreateGalaxy::Galaxy {
	std::string name;
	std::string seed;

	int starAtPosition(int x, int y);
};

class CreateGalaxy::Star {
	std::string name;
	std::string seed;

	int starTypeID;
};

class CreateGalaxy::Planet {
	std::string name;
	std::string seed;
};

#endif  // CREATEGALAXY_H