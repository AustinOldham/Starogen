#include "PlanetGenerator.h"

using namespace godot;

void PlanetGenerator::_register_methods() {
	register_method("_process", &PlanetGenerator::_process);
	register_method("change_this", &PlanetGenerator::change_this);
	register_property<PlanetGenerator, float>("amplitude", &PlanetGenerator::amplitude, 10.0);
	register_property<PlanetGenerator, float>("speed", &PlanetGenerator::set_speed, &PlanetGenerator::get_speed, 1.0);

	register_signal<PlanetGenerator>((char *)"position_changed", "node", GODOT_VARIANT_TYPE_OBJECT, "new_pos", GODOT_VARIANT_TYPE_VECTOR2);
}

PlanetGenerator::PlanetGenerator() {
}

PlanetGenerator::~PlanetGenerator() {
	// add your cleanup here
}

void PlanetGenerator::_init() {
	// initialize any variables here
	time_passed = 0.0;
	amplitude = 10.0;
	speed = 1.0;
	PlanetGenerator::set_planet();
}

void PlanetGenerator::_process(float delta) {
	time_passed += speed * delta;

	Vector2 new_position = Vector2(
		amplitude + (amplitude * sin(time_passed * 2.0)),
		amplitude + (amplitude * cos(time_passed * 1.5))
	);

	set_position(new_position);

	time_emit += delta;
	if (time_emit > 1.0) {
		emit_signal("position_changed", this, new_position);

		time_emit = 0.0;
	}
}

void PlanetGenerator::set_speed(float p_speed) {
	speed = p_speed;
}

float PlanetGenerator::get_speed() {
	return speed;
}

void PlanetGenerator::set_planet() {
	Godot::print("This is test1");
	Image *m = Image::_new();
	if (m == NULL) {
		Godot::print("true");
	} else {
		Godot::print("false");
	}
	Godot::print("This is test2");
	m->create(500, 500, false, 5);
	Godot::print("This is test3");
	m->lock();
	Godot::print("This is test4");
	for (int i = 0; i < 500; i++) {
		//Godot::print("This is test5");
		for (int j = 0; j < 500; j++) {
			//Godot::print("This is test6");
			m->set_pixel(i, j, Color(0, 1, 0, 1));
			//Godot::print("This is test7");
		}
		//Godot::print("This is test8");
	}
	Godot::print("This is test9");
	m->unlock();
	Godot::print("This is test10");
	ImageTexture *t = ImageTexture::_new();
	Godot::print("This is test11");
	t->create_from_image(m);
	Godot::print("This is test12");
	set_texture(t);
	Godot::print("This is testX");
}
