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

#ifndef STARTYPE_H
#define STARTYPE_H

#include <cstdint>
#include <string>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/unordered_map.hpp>


class StarType {
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version) {
			ar & name;
			ar & type;

			ar & chance;
			ar & meanPlanets;

			ar & red;
			ar & green;
			ar & blue;
			ar & alpha;


			ar & starTypeID;

			ar & customInorganicResourceTypeMap;
		}

	public:
		inline StarType() {
			starTypeID = -1;
			chance = 0;
		}

		inline explicit StarType(int newID) {
			starTypeID = newID;
			chance = 0;
		}

		std::string name;
		std::string type;

		double chance;  // Percent chance that it is selected
		double meanPlanets;  // Average number of planets for this type

		float red;
		float green;
		float blue;
		float alpha;

		uint16_t starTypeID;

		std::unordered_map<std::string, InorganicResourceType> customInorganicResourceTypeMap;  // Contains the star-specific overrides (only affects the chance and abundance, not the properties of the element)
		// TODO: See if it's necessary to set it as an empty container (when there are no custom resources) or if it's fine the way it is
};



#endif  // STARTYPE_H
