#ifndef PLANETGENERATOR_H
#define PLANETGENERATOR_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Image.hpp>
#include <ImageTexture.hpp>
#include <Texture.hpp>

namespace godot {

class PlanetGenerator : public Sprite {
	GODOT_CLASS(PlanetGenerator, Sprite)

private:
	float time_passed;
	float time_emit;
	float amplitude;
	float speed;

public:
	static void _register_methods();

	PlanetGenerator();
	~PlanetGenerator();

	void _init(); // our initializer called by Godot

	void _process(float delta);
	void set_speed(float p_speed);
	void set_planet();
	float get_speed();
};

}

#endif
