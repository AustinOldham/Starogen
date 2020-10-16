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

#ifndef INORGANICRESOURCETYPE_H
#define INORGANICRESOURCETYPE_H

#include <cstdint>
#include <string>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

class InorganicResourceType {
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version) {
			ar & name;

			ar & chanceMultiplier;
			ar & abundanceMultiplier;

			ar & inorganicResourceTypeID;
		}

	public:
		// TODO: Consider moving this to a separate .cpp file if this causes problems
		inline InorganicResourceType() {
			inorganicResourceTypeID = -1;
			chanceMultiplier = 0;
			abundanceMultiplier = 0;
		}

		inline explicit InorganicResourceType(int inorganicResourceTypeIDinput) {
			inorganicResourceTypeID = inorganicResourceTypeIDinput;
			chanceMultiplier = 0;
			abundanceMultiplier = 0;
		}

		inline InorganicResourceType(const InorganicResourceType &old) {  // Copy constructor
			name = old.name;
			chanceMultiplier = old.chanceMultiplier;
			abundanceMultiplier = old.abundanceMultiplier;
			inorganicResourceTypeID = old.inorganicResourceTypeID;
		}

		std::string name;

		double chanceMultiplier;
		double abundanceMultiplier;

		uint16_t inorganicResourceTypeID;
};


#endif  // INORGANICRESOURCETYPE_H
