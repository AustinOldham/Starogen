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

	register_method("setName", &GalaxyGenerator::setName);
	register_method("setSeed", &GalaxyGenerator::setSeed);
	register_method("setPixels", &GalaxyGenerator::setPixels);
	register_method("setCloudsFrequency", &GalaxyGenerator::setCloudsFrequency);
	register_method("setArms", &GalaxyGenerator::setArms);
	register_method("setRadialDistanceMult", &GalaxyGenerator::setRadialDistanceMult);
	register_method("setClusterStddev", &GalaxyGenerator::setClusterStddev);
	register_method("setDensity", &GalaxyGenerator::setDensity);
	register_method("setSpiralA", &GalaxyGenerator::setSpiralA);
	register_method("setSpiralB", &GalaxyGenerator::setSpiralB);
	register_method("setExtraStars", &GalaxyGenerator::setExtraStars);
	register_method("setCloudsMult", &GalaxyGenerator::setCloudsMult);
	register_method("setDensityMult", &GalaxyGenerator::setDensityMult);

}

GalaxyGenerator::GalaxyGenerator() {
}

GalaxyGenerator::~GalaxyGenerator() {

}

void GalaxyGenerator::_init() {

}

void GalaxyGenerator::_process(float delta) {

}

void GalaxyGenerator::generateGalaxy() {
	myGalaxyGenerator.run();
}



ImageTexture * GalaxyGenerator::getGalaxy() {
	// TODO: Allow strings to be input as seeds instead of ints
	Godot::print("testhereg");

	Godot::print("here1");

	Image *m = Image::_new();

	Godot::print("here2");

	int pixels = myGalaxyGenerator.getPixels();

	Godot::print("here3");

	// TODO: Change the 5 to the proper enum
	m->create(pixels, pixels, false, 5);

	Godot::print("here4");

	m->lock();

	Godot::print("here5");

	for (int y = 0; y < pixels; y++) {
		for (int x = 0; x < pixels; x++) {
			int curr = myGalaxyGenerator.at(x, y);
			m->set_pixel(x, y, Color(myGalaxyGenerator.getRed(curr), myGalaxyGenerator.getGreen(curr), myGalaxyGenerator.getBlue(curr), myGalaxyGenerator.getAlpha(curr)));
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

bool GalaxyGenerator::setName(String nameInput) {
	return myGalaxyGenerator.setName(toStandardString(nameInput));
}

bool GalaxyGenerator::setSeed(String seedInput) {
	return myGalaxyGenerator.setSeed(toStandardString(seedInput));
}

bool GalaxyGenerator::setPixels(int pixelsInput) {
	return myGalaxyGenerator.setPixels(pixelsInput);
}

bool GalaxyGenerator::setCloudsFrequency(double cloudsFrequencyInput) {
	return myGalaxyGenerator.setCloudsFrequency(cloudsFrequencyInput);
}

bool GalaxyGenerator::setArms(int armsInput) {
	return myGalaxyGenerator.setArms(armsInput);
}

bool GalaxyGenerator::setRadialDistanceMult(double radialDistanceMultInput) {
	return myGalaxyGenerator.setRadialDistanceMult(radialDistanceMultInput);
}

bool GalaxyGenerator::setClusterStddev(double clusterStddevInput) {
	return myGalaxyGenerator.setClusterStddev(clusterStddevInput);
}

bool GalaxyGenerator::setDensity(double densityInput) {
	return myGalaxyGenerator.setDensity(densityInput);
}

bool GalaxyGenerator::setSpiralA(double spiralAInput) {
	return myGalaxyGenerator.setSpiralA(spiralAInput);
}

bool GalaxyGenerator::setSpiralB(double spiralBInput) {
	return myGalaxyGenerator.setSpiralB(spiralBInput);
}

bool GalaxyGenerator::setExtraStars(int extraStarsInput) {
	return myGalaxyGenerator.setExtraStars(extraStarsInput);
}

bool GalaxyGenerator::setCloudsMult(double cloudsMultInput) {
	return myGalaxyGenerator.setCloudsMult(cloudsMultInput);
}

bool GalaxyGenerator::setDensityMult(double densityMultInput) {
	return myGalaxyGenerator.setDensityMult(densityMultInput);
}

std::string GalaxyGenerator::toStandardString(String oldString) {
	return std::string(oldString.alloc_c_string());
}
