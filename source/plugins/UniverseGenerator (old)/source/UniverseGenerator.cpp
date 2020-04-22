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

#include "UniverseGenerator.h"

using namespace godot;


void UniverseGenerator::_register_methods() {
	register_method("_process", &UniverseGenerator::_process);
	register_method("generateGalaxy", &UniverseGenerator::generateGalaxy);
	register_method("getGalaxy", &UniverseGenerator::getGalaxy);
}

UniverseGenerator::UniverseGenerator() {
}

UniverseGenerator::~UniverseGenerator() {

}

void UniverseGenerator::_init() {

}

void UniverseGenerator::_process(float delta) {

}

void UniverseGenerator::generateGalaxy(String nameInput, String seedInput, int pixelsInput, double cloudsFrequencyInput, int armsInput, double radialDistanceMultInput, double clusterStddevInput, double densityInput, double aInput, double bInput, int extraStarsInput, int densityGridInput, double cloudsMultInput) {
	std::string name(toStandardString(nameInput));
	std::string seed(toStandardString(seedInput));
	myUniverse.myGalaxy.generate(name, seed, pixelsInput, cloudsFrequencyInput, armsInput, radialDistanceMultInput, clusterStddevInput, densityInput, aInput, bInput, extraStarsInput, densityGridInput, cloudsMultInput);
}



ImageTexture * UniverseGenerator::getGalaxy() {
	// TODO: Allow strings to be input as seeds instead of ints
	Godot::print("testhereg");

	Godot::print("here1");

	Image *m = Image::_new();

	Godot::print("here2");

	int pixels = myUniverse.myGalaxy.getPixels();

	Godot::print("here3");

	// TODO: Change the 5 to the proper enum
	m->create(pixels, pixels, false, 5);

	Godot::print("here4");

	m->lock();

	Godot::print("here5");

	for (int y = 0; y < pixels; y++) {
		for (int x = 0; x < pixels; x++) {
			int curr = myUniverse.myGalaxy.starAtPosition(x, y);
			m->set_pixel(x, y, Color(myUniverse.myGalaxy.getRed(curr), myUniverse.myGalaxy.getGreen(curr), myUniverse.myGalaxy.getBlue(curr), myUniverse.myGalaxy.getAlpha(curr)));
		}
	}

	Godot::print("here6");

	m->unlock();

	Godot::print("here7");

	ImageTexture *t = ImageTexture::_new();

	Godot::print("here8");

	t->create_from_image(m);

	Godot::print("here9");

	t->set_flags(0);  // Disables filtering

	Godot::print("here10");

	return t;
}

std::string UniverseGenerator::toStandardString(String oldString) {
	return std::string(oldString.alloc_c_string());
}
