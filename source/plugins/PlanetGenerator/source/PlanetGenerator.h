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

#ifndef PLANETGENERATOR_H
#define PLANETGENERATOR_H

#include <vector>
#include <cmath>

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Image.hpp>
#include <ImageTexture.hpp>
#include <Texture.hpp>
#include <String.hpp>

#include "FastNoise/FastNoise.h"
#include "RadialGradient/RadialGradient.h"
#include "CreatePlanet.h"

namespace godot {

class PlanetGenerator : public Object {
	GODOT_CLASS(PlanetGenerator, Object)

	private:
		// TODO: Make CreatePlanet.cpp be the only one storing variables like this.
		int diameter;
	public:
		// NOTE: Static methods do not work

		static void _register_methods();

		PlanetGenerator();
		~PlanetGenerator();

		void _init();

		void _process(float delta);
		ImageTexture * getPlanet(int seed, int diameter);
};

}

#endif
