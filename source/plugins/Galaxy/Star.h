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

#ifndef STAR_H
#define STAR_H

#include <string>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "Planet.h"

class Star {
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version) {
			ar & name;
			ar & seed;
			ar & starTypeID;
			ar & planetList;
		}
		std::string name;
		// std::string seed;
		unsigned int seed;

		int starTypeID;

		std::vector<Planet> planetList;  // An ordered list of planets orbiting this star
	public:
		Star();
		explicit Star(int id);

		int getStarTypeID();
		std::string getName();
		std::vector<Planet> getPlanetList();
		std::vector<std::string> getPlanetNameList();  // Returns a list of all planet names in the vector. TODO: Add another option to get a vector with the planet names and the orbiting moons after each planet name (maybe add a special character in front of it to mark it as a moon so it is easier to render in Godot)

		bool setName(std::string nameInput);
		// bool setSeed(int seedInput);
		bool setSeed(unsigned int seedInput);
		bool addPlanet(Planet planetInput);
		bool insertPlanet(Planet planetInput, int index);
		bool removePlanet(Planet planetInput);
};

#endif  // STAR_H
