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

#ifndef PLANETGENERATOR_RANDCLASS_H
#define PLANETGENERATOR_RANDCLASS_H

#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <sstream>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/split_member.hpp>

class RandClass {
	private:
		friend class boost::serialization::access;
		/*template<class Archive>
		void serialize(Archive & ar, const unsigned int version) {
			ar & generator;
			ar & seed;

			ar & min;
			ar & max;
		}*/
		template<class Archive>
		void save(Archive & ar, const unsigned int version) const {
			// ar << boost::serialization::base_object<const base_class_of_T>(*this);

			std::stringstream ss;
			ss << generator;
			std::string generatorString = ss.str();
			ar << generatorString;

			ar << seed;

			ar << min;
			ar << max;
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

			ar >> min;
			ar >> max;
		}

		template<class Archive>
		void serialize(Archive & ar, const unsigned int file_version) {
			boost::serialization::split_member(ar, *this, file_version);
		}

		std::mt19937 generator;
		std::string seed;

		int min;
		int max;

	public:
		RandClass();
		explicit RandClass(std::string);
		RandClass(std::string seedInput, int minInput, int maxInput);
		RandClass(int, int);
		void setSeed();
		void setSeed(std::string);
		void printInfo();
		int next();
		int next(int, int);
		double next(double minInput, double maxInput);
		double nextNormal(double mean, double stddev);
		int nextAltNormal();
		int nextAltNormal(int minInput, int maxInput);
};

#endif  // PLANETGENERATOR_RANDCLASS_H
