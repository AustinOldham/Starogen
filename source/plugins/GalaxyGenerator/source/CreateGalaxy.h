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
#include <utility>
#include <stdexcept>
#include <filesystem>


#include <iomanip>
// delete this later


#include <nlohmann/json.hpp>
#include <boost/functional/hash.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "RandClass/RandClass.h"
#include "FastNoise/FastNoise.h"
#include "Star.h"
#include "Galaxy.h"
#include "WordGenerator.h"

class CreateGalaxy {
	private:
		RandClass starClusterGen;
		FastNoise cloudNoise;
		Galaxy myGalaxy;

		struct StarType;
		// class Galaxy;
		// class Star;
		// class Planet;
		// TODO: Move this inside the galaxy class.
		std::vector<StarType> starList;  // TODO: Rename to starTypeList.

		// TODO: Test the 2D vector version later on in order to determine whether or not speed should be sacrificed for memory.
		// std::vector<std::vector<int>> blankGalaxyMap;
		// std::vector<std::vector<Star>> galaxyMap;
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
		int extraStars;  // Whether or not an extra, less dense cluster of stars is added. TODO: Add extra variables that control the density and number of stars added.
		// int densityGrid;
		double cloudsFrequency;
		double cloudsMult;
		double densityMult;

		void generate();
		void createApproximateDensityMap();
		void createClouds();
		void starCluster(int x, int y, int num, double stddev, int distanceProportionInt);
		Star plotStar(int distanceProportionInt);
		void populateEmptyStars();
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
		std::vector<StarType> readStarFile(std::string fileNameInput);
		//std::vector<std::vector<std::string>> readFile(std::string fileName);
		//std::vector<std::string> splitString(const std::string &s, char delimiter);
		//std::unordered_map<std::string, int> getIDMap();
		//std::vector<std::string> getNumToString();
		void getProbabilities();  // This may be removed when discrete_distribution is used.
		//std::vector<std::vector<float>> getColors();

	public:
		const double PI = std::atan(1.0)*4;

		CreateGalaxy();

		void run();

		void createPlanets();

		Star at(int x, int y);

		float getRed(int index);
		float getGreen(int index);
		float getBlue(int index);
		float getAlpha(int index);

		std::string getName();
		std::string getSeed();
		int getPixels();
		double getCloudsFrequency();
		int getArms();
		double getRadialDistanceMult();
		double getClusterStddev();
		double getDensity();
		double getSpiralA();
		double getSpiralB();
		int getExtraStars();
		double getCloudsMult();
		double getDensityMult();

		std::string getStarNameAt(int x, int y);
		int getStarTypeIDAt(int x, int y);

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
		int suggestExtraStars();
		double suggestCloudsMult();

		bool saveGalaxy(std::string pathInput);
		bool loadGalaxy(std::string pathInput, std::string fileNameInput);

		bool setCensoredWordsPath(std::string pathInput);
};

struct CreateGalaxy::StarType {  // TODO: Move this over to Galaxy.h and refactor the code to make that possible so this can be stored
	std::string name;
	std::string type;

	// TODO: Add starTypeID to this list (as uint16_t?) which is the index of this type in the array in CreateGalaxy

	// int id;
	double chance;
	double adjustedChance;
	double meanPlanets;

	float red;
	float green;
	float blue;
	float alpha;

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & name;
		ar & type;

		ar & chance;
		ar & adjustedChance;
		ar & meanPlanets;

		ar & red;
		ar & green;
		ar & blue;
		ar & alpha;
	}
};



#endif  // CREATEGALAXY_H
