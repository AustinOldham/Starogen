// Copyright (C) 2020  Austin Oldham
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

#ifndef GALAXYGENERATOR_H
#define GALAXYGENERATOR_H

#include <string>

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Image.hpp>
#include <ImageTexture.hpp>
#include <Texture.hpp>
#include <String.hpp>

#include "CreateGalaxy.h"

namespace godot {

class GalaxyGenerator : public Object {
	GODOT_CLASS(GalaxyGenerator, Object)

	private:
		CreateGalaxy myGalaxyGenerator;

	public:
		// NOTE: Static methods do not work

		static void _register_methods();

		GalaxyGenerator();
		~GalaxyGenerator();

		void _init();

		void _process(float delta);
		void generateGalaxy();
		ImageTexture * getGalaxy();  // Rename this to getGalaxyImage.

		int at(int x, int y);

		float getRed(int index);
		float getGreen(int index);
		float getBlue(int index);
		float getAlpha(int index);

		String getName();
		String getSeed();
		int getPixels();
		double getCloudsFrequency();
		int getArms();
		double getRadialDistanceMult();
		double getClusterStddev();
		double getDensity();
		double getSpiralA();
		double getSpiralB();
		int getExtraStars();
		double getCloudsMult();
		double getDensityMult();

		bool setName(String nameInput);
		bool setSeed(String seedInput);
		bool setPixels(int pixelsInput);
		bool setCloudsFrequency(double cloudsFrequencyInput);
		bool setArms(int armsInput);
		bool setRadialDistanceMult(double radialDistanceMultInput);
		bool setClusterStddev(double clusterStddevInput);
		bool setDensity(double densityInput);
		bool setSpiralA(double spiralAInput);
		bool setSpiralB(double spiralBInput);
		bool setExtraStars(int extraStarsInput);
		// bool setDensityGrid(int densityGridInput);
		bool setCloudsMult(double cloudsMultInput);
		bool setDensityMult(double densityMultInput);

		std::string toStandardString(String oldString);
		String toGodotString(std::string oldString);

		bool saveGalaxy(String pathInput);
		bool loadGalaxy(String pathInput, String fileNameInput);
};

}

#endif
