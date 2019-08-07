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

onready var galaxy_generator = preload("res://plugins/GalaxyGenerator/bin/GalaxyGenerator.gdns").new()

var localX = -1
var localY = -1

func _ready():
	randomize()
	galaxy_generator.generateGalaxy("testName", "testSeed", 500, 0.05, -1, -1.0, -1.0, -1.0, 0.1, 0.3, -1, -1, -1.0)
	self.texture = galaxy_generator.getGalaxy()
	#self.texture = load("res://images/application/starogen_logo_v2_256px.png")
	#self.scale.x = 5
	#self.scale.y = 5

func _input(event):
	if event is InputEventMouseButton:
		if event.is_pressed():
			if event.button_index == BUTTON_WHEEL_DOWN:
				zoom_camera(-1)
			if event.button_index == BUTTON_WHEEL_UP:
				zoom_camera(1)

#TODO: Add rounding to avoid float rounding errors

func zoom_camera(direction):
	#print(global_scale)
	var temp = scale + Vector2(0.1, 0.1) * direction * 5.0
	if (temp.x <= 0.01 or temp.y <= 0.01):
		pass
	else:
		scale = temp

func _process(delta):
	if (Input.is_action_pressed("ui_left")):
		global_position += Vector2(-0.1, 0.0) * 50
	if (Input.is_action_pressed("ui_right")):
		global_position += Vector2(0.1, 0.0) * 50

	if (Input.is_action_pressed("ui_down")):
		global_position += Vector2(0.0, 0.1) * 50
	elif (Input.is_action_pressed("ui_up")):
		global_position += Vector2(0.0, -0.1) * 50

func _draw():
		var roundX = int(localX)
		var roundY = int(localY)
		var black = Color(0.0, 0.0, 0.0, 1.0)
		var rect1 = Rect2(Vector2(roundX, roundY), Vector2(0.5, 0.5))
		draw_rect(rect1, black, false)
		var rect2 = Rect2(Vector2(roundX + 0.5, roundY), Vector2(0.5, 0.5))
		draw_rect(rect2, black, false)
		var rect3 = Rect2(Vector2(roundX + 0.5, roundY + 0.5), Vector2(0.5, 0.5))
		draw_rect(rect3, black, false)
		var rect4 = Rect2(Vector2(roundX, roundY + 0.5), Vector2(0.5, 0.5))
		draw_rect(rect4, black, false)
		var rect5 = Rect2(Vector2(roundX, roundY), Vector2(1.0, 1.0))
		draw_rect(rect5, Color(1.0, 1.0, 1.0, 1.0), false)
		print(scale)
