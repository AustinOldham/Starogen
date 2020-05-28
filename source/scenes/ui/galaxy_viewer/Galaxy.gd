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


func _ready():
	pass


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


func _on_Recenter_pressed():
	global_position = get_parent().get_parent().get_global_transform().origin
	scale = Vector2(1, 1)
