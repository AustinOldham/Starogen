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
	int diameter;
public:
	static void _register_methods();

	PlanetGenerator();
	~PlanetGenerator();

	void _init();

	void _process(float delta);
	void set_planet();
	ImageTexture * get_planet();
};

}

#endif
