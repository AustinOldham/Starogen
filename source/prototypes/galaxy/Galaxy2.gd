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

extends Node2D

onready var galaxy_generator = preload("res://plugins/GalaxyGenerator/bin/GalaxyGenerator.gdns").new()
const galaxy_star = preload("res://prototypes/galaxy/GalaxyStar.tscn")

func _ready():
	print("Generation started")
	galaxy_generator.generateGalaxy()
	for y in range(galaxy_generator.getPixels()):
		for x in range(galaxy_generator.getPixels()):
			if (galaxy_generator.at(x, y) != 0):
				var new_star = galaxy_star.instance()
				add_child(new_star)
				new_star.set_position(Vector2(x, y))
	# $Galaxy2/Sprite.texture = galaxy_generator.getGalaxy()
	print("Generation complete")


func _input(event):
	if event is InputEventMouseButton:
		if event.is_pressed():
			if event.button_index == BUTTON_WHEEL_DOWN:
				_zoom_scale(-1)
			if event.button_index == BUTTON_WHEEL_UP:
				_zoom_scale(1)
		if event.button_index == BUTTON_LEFT and event.is_pressed():
			# self.on_click()
			pass

func _zoom_scale(direction):
	#print(global_scale)
	var temp = get_scale() + Vector2(0.1, 0.1) * direction * 5.0
	if (temp.x <= 0.00001 or temp.y <= 0.00001):
		pass
	else:
		set_scale(temp)

func _process(delta):
	if (Input.is_action_pressed("ui_right")):
		global_position += Vector2(-0.1, 0.0) * 50
	if (Input.is_action_pressed("ui_left")):
		global_position += Vector2(0.1, 0.0) * 50

	if (Input.is_action_pressed("ui_up")):
		global_position += Vector2(0.0, 0.1) * 50
	elif (Input.is_action_pressed("ui_down")):
		global_position += Vector2(0.0, -0.1) * 50
