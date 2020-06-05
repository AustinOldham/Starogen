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

class Planet {
	private:
		std::string name;

		int planetTypeID;

		double averageTemperature;  // Kelvin

		std::unordered_map<std::string, double> inorganic_resources;  // Stores which resources (carbon, iron, etc., not from organisms) are available on a planet and how much remains.
		std::unordered_map<std::string, double> gases;  // Stores which types of gases are present in the atmosphere and at what concentration.

	public:
		Planet();
}

#endif  // PLANET_H
