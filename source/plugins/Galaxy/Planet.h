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

#ifndef PLANET_H
#define PLANET_H

#include <string>
#include <unordered_map>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

class Planet {
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version) {
			ar & name;
			ar & seed;
			ar & planetTypeID;
			ar & averageTemperature;
			ar & inorganic_resources;
			ar & gases;
		}
		std::string name;
		unsigned int seed;

		int planetTypeID;

		double averageTemperature;  // Kelvin

		std::unordered_map<std::string, double> inorganic_resources;  // Stores which resources (carbon, iron, etc., not from organisms) are available on a planet and how much remains.
		// Resources will be in units zettagrams (10^21 grams)
		std::unordered_map<std::string, double> gases;  // Stores which types of gases are present in the atmosphere and at what concentration.

	public:
		Planet();
}

#endif  // PLANET_H
