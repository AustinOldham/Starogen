#include "PlanetGenerator.h"

using namespace godot;

void PlanetGenerator::_register_methods() {
	register_method("_process", &PlanetGenerator::_process);
	register_method("set_planet", &PlanetGenerator::set_planet);
	register_method("get_planet", &PlanetGenerator::get_planet);
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

void PlanetGenerator::set_planet() {
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

ImageTexture * PlanetGenerator::get_planet() {
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
	return t;
}
