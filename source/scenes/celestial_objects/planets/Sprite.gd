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

extends Sprite

onready var planet_generator = preload("res://plugins/PlanetGenerator/bin/PlanetGenerator.gdns").new()

func _ready():
	randomize()
	var seed_input = int(rand_range(0, 2147483647))
	#seed_input = 2078663171
	self.texture = planet_generator.getPlanet(seed_input, 100)
	scale = Vector2(5, 5)
	_create_collision_polygon()


func _create_collision_polygon():
	#NOTE: This is probably very inefficient and was done this way due to simplicity. I might write an optimized version if performance becomes an issue.
	var bm = BitMap.new()
	bm.create_from_image_alpha(texture.get_data())
	var rect = Rect2(position.x, position.y, texture.get_width(), texture.get_height())
	var my_array = bm.opaque_to_polygons(rect, 0.0001)
	var my_polygon = Polygon2D.new()
	my_polygon.set_polygons(my_array)
	for i in range(my_polygon.polygons.size()):
		var my_collision = CollisionPolygon2D.new()
		my_collision.set_polygon(my_polygon.polygons[i])
		my_collision.scale = scale
		get_parent().call_deferred("add_child", my_collision)

func _generate():
	var seed_input = int(rand_range(0, 2147483647))
	print(seed_input)
	self.texture = planet_generator.getPlanet(seed_input, 100)	
	_create_collision_polygon()

func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == BUTTON_LEFT and event.is_pressed():
			#self._generate()
			pass