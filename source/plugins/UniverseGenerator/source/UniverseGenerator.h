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

#ifndef UNIVERSEGENERATOR_H
#define UNIVERSEGENERATOR_H

#include <string>

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Image.hpp>
#include <ImageTexture.hpp>
#include <Texture.hpp>
#include <String.hpp>

#include "CreateUniverse.h"

namespace godot {

class UniverseGenerator : public Object {
	GODOT_CLASS(UniverseGenerator, Object)

	private:
		CreateUniverse myUniverse;
	public:
		// NOTE: Static methods do not work

		static void _register_methods();

		UniverseGenerator();
		~UniverseGenerator();

		void _init();

		void _process(float delta);
		void generateGalaxy(String nameInput, String seedInput, int pixelsInput, double cloudsFrequencyInput, int armsInput, double radialDistanceMultInput, double clusterStddevInput, double densityInput, double aInput, double bInput, int extraStarsInput, int densityGridInput, double cloudsMultInput);
		ImageTexture * getGalaxy();

		std::string toStandardString(String oldString);
};

}

#endif
