// Copyright (C) 2019  Austin Oldham
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

#include "GalaxyGenerator.h"

using namespace godot;


void GalaxyGenerator::_register_methods() {
	register_method("_process", &GalaxyGenerator::_process);
	register_method("generateGalaxy", &GalaxyGenerator::generateGalaxy);
	register_method("getGalaxy", &GalaxyGenerator::getGalaxy);
}

GalaxyGenerator::GalaxyGenerator() {
}

GalaxyGenerator::~GalaxyGenerator() {

}

void GalaxyGenerator::_init() {

}

void GalaxyGenerator::_process(float delta) {

}

void GalaxyGenerator::generateGalaxy(String nameInput, String seedInput, int pixelsInput, double cloudsFrequencyInput, int armsInput, double radialDistanceMultInput, double clusterStddevInput, double densityInput, double aInput, double bInput, int extraStarsInput, int densityGridInput, double cloudsMultInput, double densityMultInput) {
	std::string name(toStandardString(nameInput));
	std::string seed(toStandardString(seedInput));
	myGalaxy.generate(name, seed, pixelsInput, cloudsFrequencyInput, armsInput, radialDistanceMultInput, clusterStddevInput, densityInput, aInput, bInput, extraStarsInput, densityGridInput, cloudsMultInput, densityMultInput);
}



ImageTexture * GalaxyGenerator::getGalaxy() {
	// TODO: Allow strings to be input as seeds instead of ints
	Godot::print("testhereg");

	Godot::print("here1");

	Image *m = Image::_new();

	Godot::print("here2");

	int pixels = myGalaxy.getPixels();

	Godot::print("here3");

	// TODO: Change the 5 to the proper enum
	m->create(pixels, pixels, false, 5);

	Godot::print("here4");

	m->lock();

	Godot::print("here5");

	for (int y = 0; y < pixels; y++) {
		for (int x = 0; x < pixels; x++) {
			int curr = myGalaxy.at(x, y);
			m->set_pixel(x, y, Color(myGalaxy.getRed(curr), myGalaxy.getGreen(curr), myGalaxy.getBlue(curr), myGalaxy.getAlpha(curr)));
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

std::string GalaxyGenerator::toStandardString(String oldString) {
	return std::string(oldString.alloc_c_string());
}
