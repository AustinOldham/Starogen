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

signal invalid_check(type)

var x = -1
var y = -1
var last_width = 500

var is_invalid = false
var name_input = ""
var seed_input = ""
var pixels = 500
var clouds_mult = -1.0
var clouds_frequency = 0.05
var arms = -1
var radial_distance_mult = -1.0
var cluster_stddev = -1.0
var density = -1.0
var a = 0.1
var b = 0.3
var extra_stars = -1
var density_grid = -1


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
			self.on_click()

func _zoom_scale(direction):
	#print(global_scale)
	var temp = scale + Vector2(0.1, 0.1) * direction * 5.0
	if (temp.x <= 0.00001 or temp.y <= 0.00001):
		pass
	else:
		scale = temp

func _process(delta):
	if (Input.is_action_pressed("ui_right")):
		global_position += Vector2(-0.1, 0.0) * 50
	if (Input.is_action_pressed("ui_left")):
		global_position += Vector2(0.1, 0.0) * 50

	if (Input.is_action_pressed("ui_up")):
		global_position += Vector2(0.0, 0.1) * 50
	elif (Input.is_action_pressed("ui_down")):
		global_position += Vector2(0.0, -0.1) * 50

func _draw():
		var roundX = int(x)
		var roundY = int(y)
		if (roundX >= 0 or roundY >= 0):
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

func on_click():
	print("Click")
	print(get_global_mouse_position())
	print(get_global_transform().origin)
	print(get_transform().origin)
	var localX = (get_global_mouse_position().x - get_global_transform().origin.x) / scale.x
	var localY = (get_global_mouse_position().y - get_global_transform().origin.y) / scale.y
	print("sprite x: " + str(localX) + "  sprite y: " + str(localY))
	if (localX < last_width and localY < last_width and localX >= 0 and localY >= 0):
		print("Contained")
		x = localX
		y = localY
		update()

func _check_input_float(text, type, default, less_than, invalid_num):
	if (text.empty()):
		emit_signal("invalid_check", "")
		return default
	elif (text.is_valid_float()):
		if (less_than):
			if (float(text) <= invalid_num):
				emit_signal("invalid_check", type)
				return default
			else:
				emit_signal("invalid_check", "")
				return float(text)
		else:
			if (float(text) >= invalid_num):
				emit_signal("invalid_check", type)
				return default
			else:
				emit_signal("invalid_check", "")
				return float(text)
	else:
		emit_signal("invalid_check", type)
		return default

func _check_input_int(text, type, default, less_than, invalid_num):
	if (text.empty()):
		emit_signal("invalid_check", "")
		return default
	elif (text.is_valid_float()):
		if (less_than):
			if (int(text) <= invalid_num):
				emit_signal("invalid_check", type)
				return default
			else:
				emit_signal("invalid_check", "")
				return int(text)
		else:
			if (int(text) >= invalid_num):
				emit_signal("invalid_check", type)
				return default
			else:
				emit_signal("invalid_check", "")
				return int(text)
	else:
		emit_signal("invalid_check", type)
		return default

func _on_CloudsMultEdit_text_changed(new_text):
	clouds_mult = _check_input_float(new_text, "Clouds Mult", -1.0, true, 0.0)



func _on_NameEdit_text_changed(new_text):
	name_input = new_text


func _on_SeedEdit_text_changed(new_text):
	seed_input = new_text


func _on_SizeEdit_text_changed(new_text):
	pixels = _check_input_int(new_text, "Size", 500, true, 0)


func _on_CloudsFrequencyEdit_text_changed(new_text):
	clouds_frequency = _check_input_float(new_text, "Clouds Frequency", 0.05, true, 0.0)


func _on_ArmsEdit_text_changed(new_text):
	arms = _check_input_int(new_text, "Arms", -1, true, 0)


func _on_RadialDistanceMultEdit_text_changed(new_text):
	radial_distance_mult = _check_input_float(new_text, "Radial Distance Mult", -1.0, true, 0.0)


func _on_ClusterStddevEdit_text_changed(new_text):
	cluster_stddev = _check_input_float(new_text, "Cluster Stddev", -1.0, true, 0.0)


func _on_DensityEdit_text_changed(new_text):
	density = _check_input_float(new_text, "Density", -1.0, true, 0.0)


func _on_AEdit_text_changed(new_text):
	if (new_text.is_valid_float()):
		a = float(new_text)
		emit_signal("invalid_check", "")
	elif (new_text.empty()):
		a = 0.1
		emit_signal("invalid_check", "")
	else:
		a = 0.1
		emit_signal("invalid_check", "A")


func _on_BEdit_text_changed(new_text):
	if (new_text.is_valid_float()):
		if (float(new_text) <= 0):
			b = 0.3
			emit_signal("invalid_check", "B")
		else:
			b = float(new_text)
			emit_signal("invalid_check", "")
	elif (new_text.empty()):
		b = 0.3
		emit_signal("invalid_check", "")
	else:
		b = 0.3
		emit_signal("invalid_check", "B")


func _on_ExtraStarsEdit_item_selected(ID):
	if (ID == 1):
		extra_stars = 1
	elif (ID == 2):
		extra_stars = 0
	else:
		extra_stars = -1


func _on_DensityGridEdit_text_changed(new_text):
	density_grid = _check_input_int(new_text, "Density Grid", -1, true, 0)


func _on_Generate_pressed():
	print("Generation started")
	galaxy_generator.generateGalaxy(name_input, seed_input, pixels, clouds_frequency, arms, radial_distance_mult, cluster_stddev, density, a, b, extra_stars, density_grid, clouds_mult)
	self.texture = galaxy_generator.getGalaxy()
	print("Generation complete")


func _on_Recenter_pressed():
	global_position = get_parent().get_parent().get_global_transform().origin
	scale = Vector2(1, 1)
