# Copyright (C) 2019  Austin Oldham
#
# This file is part of Starogen.
#
# Starogen is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Starogen is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Starogen.  If not, see <https://www.gnu.org/licenses/>.

extends CelestialSprite

#onready var planet_generator = preload("res://plugins/PlanetGenerator/bin/PlanetGenerator.gdns").new()

var size

func _ready():
	randomize()
	size = 100
	var seed_input = int(rand_range(0, 2147483647))
	seed_input = 1103312258
	print(seed_input)
	#seed_input = 2078663171
	#self.texture = planet_generator.getPlanet(seed_input, size)
	#self.texture = load("res://images/application/starogen_logo_v2_256px.png")
	#scale = Vector2(50, 50) #5 normally
	scale = Vector2(5, 5)
	#self.scale = Vector2(100, 100)
	print("before")
	_create_collision_polygon()
	print("after")



"""func _generate():
	var seed_input = int(rand_range(0, 2147483647))
	print(seed_input)
	self.texture = planet_generator.getPlanet(seed_input, size)	
	_create_collision_polygon()"""

#func _input(event):
#	if event is InputEventMouseButton:
#		if event.button_index == BUTTON_LEFT and event.is_pressed():
#			#self._generate()
#			print(get_local_mouse_position())
#			pass

