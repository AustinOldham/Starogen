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

#include "PlanetGenerator.h"

using namespace godot;


void PlanetGenerator::_register_methods() {
	register_method("_process", &PlanetGenerator::_process);
	register_method("setPlanet", &PlanetGenerator::setPlanet);
	register_method("getPlanet", &PlanetGenerator::getPlanet);
	//register_method("sharpRadialGradient", &PlanetGenerator::sharpRadialGradient);
	//register_method("radialDistance", &PlanetGenerator::radialDistance);
	//register_method("adjustRange", &PlanetGenerator::adjustRange);
}

PlanetGenerator::PlanetGenerator() {
}

PlanetGenerator::~PlanetGenerator() {
	// add your cleanup here
}

void PlanetGenerator::_init() {
	// PlanetGenerator::set_planet();
}

void PlanetGenerator::_process(float delta) {

}

void PlanetGenerator::setPlanet() {
	Image *m = Image::_new();
	m->create(500, 500, false, 5);
	m->lock();
	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < 500; j++) {
			m->set_pixel(i, j, Color(0, 1, 0, 1));
		}
	}
	m->unlock();
	ImageTexture *t = ImageTexture::_new();
	t->create_from_image(m);
	set_texture(t);
}

ImageTexture * PlanetGenerator::getPlanet(int seed, int diameter) {
	// TODO: Allow strings to be input as seeds instead of ints
	Godot::print("testhere");
	CreatePlanet planet(seed, diameter);
	//String testString(CreatePlanet::colors[0])
	//Godot::print(CreatePlanet::colors[1]);
	//RadialGradient<double> gradient;
	//gradient.sharpRadialGradient(diameter, diameter, 0, 1, 0.5);
	Image *m = Image::_new();
	// TODO: Change the 5 to the proper enum
	m->create(diameter, diameter, false, 5);
	m->lock();
	for (int y = 0; y < diameter; y++) {
		for (int x = 0; x < diameter; x++) {
			int curr = planet.planetVector[y][x];
			Godot::print(CreatePlanet::colors[curr][0]);
			m->set_pixel(x, y, Color(CreatePlanet::colors[curr][0], CreatePlanet::colors[curr][1], CreatePlanet::colors[curr][2], CreatePlanet::colors[curr][3]));
		}
	}
	m->unlock();
	ImageTexture *t = ImageTexture::_new();
	t->create_from_image(m);
	return t;
}

/*std::vector<std::vector<double>> PlanetGenerator::sharpRadialGradient(int width, int height, double smallest, double largest, double sharpMult) {
	// NOTE: sharpMult must range from 0 to 1
	std::vector<std::vector<double>> gradient(height, std::vector<double>(width, 0));

	double centerX = width / 2.0;
	double centerY = height / 2.0;

	double max;
	if (centerX > centerY) {
		max = centerY;
	} else {
		max = centerX;
	}

	double sharpRadius = max * sharpMult;
	double sharpMax = max - sharpRadius;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double distance = PlanetGenerator::radialDistance(x, y, centerX, centerY);
			if (distance > max) {
				distance = max;
			}
			distance = distance - sharpRadius;
			if (distance < 0) {
				distance = 0;
			}

			double value = PlanetGenerator::adjustRange(distance, 0, sharpMax, smallest, largest);
			gradient[y][x] = value;
		}
	}

	return gradient;
}

double PlanetGenerator::radialDistance(int x, int y, double centerX, double centerY) {
	double distanceX = std::pow(std::abs(centerX - x), 2);
	double distanceY = std::pow(std::abs(centerY - y), 2);
	return std::sqrt(distanceX + distanceY);
}



double PlanetGenerator::adjustRange(double oldNum, double oldMin, double oldMax, double newMin, double newMax) {
	return ((((newMax - newMin) * (oldNum - oldMin)) / (oldMax - oldMin)) + newMin);
}*/
