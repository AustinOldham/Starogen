//Copyright (C) 2020  Austin Oldham
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

#ifndef CUSTOMDISCRETEDISTRIBUTION_H
#define CUSTOMDISCRETEDISTRIBUTION_H

#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/split_member.hpp>


class CustomDiscreteDistribution {
	private:
		friend class boost::serialization::access;

		template<class Archive>
		void save(Archive & ar, const unsigned int version) const {
			// ar << boost::serialization::base_object<const base_class_of_T>(*this);

			std::stringstream ss;
			ss << generator;
			std::string generatorString = ss.str();
			ar << generatorString;

			ar << seed;

			ar << distribution;
		}

		template<class Archive>
		void load(Archive & ar, const unsigned int version) {
			// ar >> boost::serialization::base_object<base_class_of_T>(*this);

			std::string generatorString;
			ar >> generatorString;
			std::stringstream ss;
			ss.str(generatorString);
			ss >> generator;

			ar >> seed;

			ar >> distribution;
		}

		template<class Archive>
		void serialize(Archive & ar, const unsigned int file_version) {
			boost::serialization::split_member(ar, *this, file_version);
		}

		std::mt19937 generator;
		std::string seed;

		std::discrete_distribution<int> distribution;

		void setSeed();

	public:
		CustomDiscreteDistribution();
		explicit CustomDiscreteDistribution(std::string);
		void setSeed(std::string);
		void setWeights(std::vector<int> weightsVector);
		int next();
};



#endif  // CUSTOMDISCRETEDISTRIBUTION_H