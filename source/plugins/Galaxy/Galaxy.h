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

#ifndef GALAXY_H
#define GALAXY_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <utility>

#include <boost/functional/hash.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/unordered_map.hpp>

#include "ParsedTypes/InorganicResourceType.h"
#include "ParsedTypes/PlanetType.h"
#include "ParsedTypes/StarType.h"
#include "Star.h"
#include "WordGenerator.h"

class Galaxy {
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version) {
			ar & myWordGenerator;

			ar & name;
			ar & seed;
			ar & pixels;
			ar & arms;
			ar & radialDistanceMult;
			ar & clusterStddev;
			ar & density;
			ar & spiralA;
			ar & spiralB;
			ar & extraStars;
			ar & cloudsFrequency;
			ar & cloudsMult;
			ar & densityMult;
			ar & seedHash;
			ar & nextUniqueID;

			ar & blankGalaxyMap;  // This may be unnecessary.
			ar & galaxyMap;

			ar & blankStar;

			ar & inorganicResourceTypeMap;
			ar & inorganicResourceTypeList;

			ar & starTypeList;

			ar & planetTypeList;
		}

		WordGenerator myWordGenerator;  // TODO: Add a function to clear this each time a new galaxy is generated so the old words are not taken.

		std::string name;
		std::string seed;
		int pixels;  // Stores the width of the galaxy.
		// double coreLocation;  // Proportion of the distance between the center and the edge that makes up the core (currently unused).
		int arms;  // Stores the number of arms the spiral galaxy should have.
		double radialDistanceMult;  // Changes the density of stars (this should be replaced with some type of "base density" constant since densityMult basically does the same thing).
		double clusterStddev;  // The standard deviation of the random offset applied to each star when a cluster is placed.
		double density;  // Arbitrary value of the density of stars (in the current implementation, increases the total number of star clusters).
		double spiralA;  // Arbitrary value that influences the shape of the spiral.
		double spiralB;  // Rate of increase of the spiral (arbitrary value, can be calculated with b = cot(alpha) where alpha is the angle between the radius and the tangent).
		int extraStars;  // Whether or not an extra, less dense cluster of stars is added. TODO: Add extra variables that control the density and number of stars added.
		double cloudsFrequency;
		double cloudsMult;
		double densityMult;
		unsigned int seedHash;
		unsigned int nextUniqueID;  // If the size of this becomes an issue, convert everything to uint64_t (maybe the fast version).

		Star blankStar;  // Returned when the "at" function is given the coordinates to empty space and is added for optimization

		std::unordered_map<std::string, uint16_t> inorganicResourceTypeMap;  // Used so planets can be stored efficiently (resource name string -> 16-bit int (inorganicResourceTypeID) -> resource amount).
		std::vector<InorganicResourceType> inorganicResourceTypeList;  // Used when determining the proportions of resources on a planet. Also used to find the resource type given the ID.

		std::vector<StarType> starTypeList;

		std::vector<PlanetType> planetTypeList;

	public:
		Galaxy();

		std::unordered_map<std::pair<int, int>, int, boost::hash<std::pair<int, int>>> blankGalaxyMap;
		std::unordered_map<std::pair<int, int>, Star, boost::hash<std::pair<int, int>>> galaxyMap;  // TODO: See if this can be made private

		Star at(int x, int y);  // Returns the star at these coordinates. Returns blankStar if there is no star there.

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
		unsigned int getNextUniqueID();

		float getStarColorRed(int starTypeID);
		float getStarColorGreen(int starTypeID);
		float getStarColorBlue(int starTypeID);
		float getStarColorAlpha(int starTypeID);

		InorganicResourceType getInorganicResourceType(std::string nameInput);
		InorganicResourceType getInorganicResourceType(int typeID);  // TODO: Consider making this const

		const std::vector<StarType> getStarTypeList();  // TODO: Consider adding a method to get an iterator

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
		bool setCloudsMult(double cloudsMultInput);
		bool setDensityMult(double densityMultInput);
		bool setSeedHash(unsigned int seedHashInput);

		// bool setStarTypeList(std::vector<StarType> starTypeListInput);  // TODO: Implement this
		bool setInorganicResourceTypeList(std::vector<InorganicResourceType> inorganicResourceTypeListInput);
		bool setInorganicResourceTypeMap(std::unordered_map<std::string, uint16_t> inorganicResourceTypeMapInput);

		bool setPlanetTypeList(std::vector<PlanetType> planetTypeListInput);

		bool setStarTypeList(std::vector<StarType> starTypeListInput);

		bool capitalize(std::string& wordInput);

		std::string generateName(int keyInput);
		std::string generateName(std::string keyInput);

		bool clearNames();
		bool setCensoredWordsPath(std::string pathInput);
};

#endif  // GALAXY_H
