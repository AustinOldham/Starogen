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
var density_mult = 1


func _ready():
	pass


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
	galaxy_generator.generateGalaxy(name_input, seed_input, pixels, clouds_frequency, arms, radial_distance_mult, cluster_stddev, density, a, b, extra_stars, density_grid, clouds_mult, density_mult)
	$CanvasLayer/MarginContainer/HSplitContainer/VBoxContainer2/GalaxyBox/Galaxy/Sprite.texture = galaxy_generator.getGalaxy()
	print("Generation complete")


func _on_Start_pressed():
	pass # Replace with function body.


func _on_DensityMultEdit_text_changed(new_text):
	density_mult = _check_input_float(new_text, "Density Mult", 1.0, true, 0.0)
	print(density_mult)
