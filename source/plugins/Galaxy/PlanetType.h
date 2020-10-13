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

#ifndef PLANETTYPE_H
#define PLANETTYPE_H

#include <cstdint>
#include <string>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/unordered_map.hpp>

#include "InorganicResourceType.h"

class PlanetType {
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version) {
			ar & name;
			ar & type;

			ar & planetTypeID;

			ar & customInorganicResourceMap;
		}

	public:
		inline PlanetType() {
			planetTypeID = -1;
		}

		std::string name;
		std::string type;

		uint16_t planetTypeID;

		std::unordered_map<std::string, InorganicResourceType> customInorganicResourceMap;  // Contains the planet-specific overrides
};



#endif  // PLANETTYPE_H
