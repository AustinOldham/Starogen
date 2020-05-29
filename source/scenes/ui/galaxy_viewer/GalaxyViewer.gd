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

const galaxy_star = preload("res://scenes/ui/galaxy_viewer/GalaxyStar.tscn")

signal invalid_check(type, value)

# TODO: Add a button to suggest values for empty boxes.

"""
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
"""

func _ready():
	_populate_entries()

"""
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
"""
"""
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
"""

func _populate_entries():
	var grid_container = $CanvasLayer/MarginContainer/HSplitContainer/VBoxContainer/GridContainer
	grid_container.get_node("NameEdit").text = galaxy_generator.getName()
	grid_container.get_node("SeedEdit").text = galaxy_generator.getSeed()
	grid_container.get_node("SizeEdit").text = str(galaxy_generator.getPixels())
	grid_container.get_node("CloudsFrequencyEdit").text = str(galaxy_generator.getCloudsFrequency())
	grid_container.get_node("ArmsEdit").text = str(galaxy_generator.getArms())
	grid_container.get_node("RadialDistanceMultEdit").text = str(galaxy_generator.getRadialDistanceMult())
	grid_container.get_node("ClusterStddevEdit").text = str(galaxy_generator.getClusterStddev())
	grid_container.get_node("DensityEdit").text = str(galaxy_generator.getDensity())
	grid_container.get_node("AEdit").text = str(galaxy_generator.getSpiralA())
	grid_container.get_node("BEdit").text = str(galaxy_generator.getSpiralB())
	grid_container.get_node("ExtraStarsEdit").text = str(galaxy_generator.getExtraStars())
	grid_container.get_node("DensityMultEdit").text = str(galaxy_generator.getDensityMult())
	grid_container.get_node("CloudsMultEdit").text = str(galaxy_generator.getCloudsMult())

func _check_input_text(text, type):
	if (text.empty()):
		emit_signal("invalid_check", type, true)  # Invalid input
		return false
	else:
		# emit_signal("invalid_check", type, false)  # Removed since a signal for valid input should only be made when the generator checks it.
		return true  # Valid input


func _check_input_float(text, type):
	if (text.empty()):
		emit_signal("invalid_check", type, true)  # Invalid input
		return false
	elif (text.is_valid_float()):
		# emit_signal("invalid_check", type, false)  # Removed since a signal for valid input should only be made when the generator checks it.
		return true   # Valid input
	else:
		emit_signal("invalid_check", type, true)  # Invalid input
		return false


func _check_input_int(text, type):
	return _check_input_float(text, type)


func _check_success(result, type):
	if (result == true):
		emit_signal("invalid_check", type, false)  # Valid input
	else:
		emit_signal("invalid_check", type, true)  # Invalid input


func _on_CloudsMultEdit_text_changed(new_text):
	var is_valid = _check_input_float(new_text, "Clouds Mult")
	if (is_valid):
		_check_success(galaxy_generator.setCloudsMult(float(new_text)), "Clouds Mult")


func _on_NameEdit_text_changed(new_text):
	var is_valid = _check_input_text(new_text, "Name")
	if (is_valid):
		_check_success(galaxy_generator.setName(new_text), "Name")


func _on_SeedEdit_text_changed(new_text):
	var is_valid = _check_input_text(new_text, "Seed")
	if (is_valid):
		_check_success(galaxy_generator.setSeed(new_text), "Seed")


func _on_SizeEdit_text_changed(new_text):
	var is_valid = _check_input_int(new_text, "Size")
	if (is_valid):
		_check_success(galaxy_generator.setPixels(int(new_text)), "Size")


func _on_CloudsFrequencyEdit_text_changed(new_text):
	var is_valid = _check_input_float(new_text, "Clouds Frequency")
	if (is_valid):
		_check_success(galaxy_generator.setCloudsFrequency(float(new_text)), "Clouds Frequency")


func _on_ArmsEdit_text_changed(new_text):
	var is_valid = _check_input_int(new_text, "Arms")
	if (is_valid):
		_check_success(galaxy_generator.setArms(int(new_text)), "Arms")


func _on_RadialDistanceMultEdit_text_changed(new_text):
	var is_valid = _check_input_float(new_text, "Radial Distance Mult")
	if (is_valid):
		_check_success(galaxy_generator.setRadialDistanceMult(float(new_text)), "Radial Distance Mult")


func _on_ClusterStddevEdit_text_changed(new_text):
	var is_valid = _check_input_float(new_text, "Cluster Stddev")
	if (is_valid):
		_check_success(galaxy_generator.setClusterStddev(float(new_text)), "Cluster Stddev")



func _on_DensityEdit_text_changed(new_text):
	var is_valid = _check_input_float(new_text, "Density")
	if (is_valid):
		_check_success(galaxy_generator.setDensity(float(new_text)), "Density")


func _on_AEdit_text_changed(new_text):
	var is_valid = _check_input_float(new_text, "SpiralA")
	if (is_valid):
		_check_success(galaxy_generator.setSpiralA(float(new_text)), "SpiralA")


func _on_BEdit_text_changed(new_text):
	var is_valid = _check_input_float(new_text, "SpiralB")
	if (is_valid):
		_check_success(galaxy_generator.setSpiralB(float(new_text)), "SpiralB")


func _on_ExtraStarsEdit_text_changed(new_text):
	var is_valid = _check_input_int(new_text, "Extra Stars")
	if (is_valid):
		_check_success(galaxy_generator.setExtraStars(int(new_text)), "Extra Stars")


func _on_DensityMultEdit_text_changed(new_text):
	var is_valid = _check_input_float(new_text, "Density Mult")
	if (is_valid):
		_check_success(galaxy_generator.setDensityMult(float(new_text)), "Density Mult")


func _on_Generate_pressed():
	var gui_galaxy = $CanvasLayer/MarginContainer/HSplitContainer/VBoxContainer2/GalaxyBox/Galaxy
	gui_galaxy.generate_galaxy()
"""
	_delete_old_stars()
	print("Generation started")
	galaxy_generator.generateGalaxy()
	var gui_galaxy = $CanvasLayer/MarginContainer/HSplitContainer/VBoxContainer2/GalaxyBox/Galaxy
	for y in range(galaxy_generator.getPixels()):
		for x in range(galaxy_generator.getPixels()):
			if (galaxy_generator.at(x, y) != 0):
				var new_star = galaxy_star.instance()
				gui_galaxy.add_child(new_star)
				new_star.original_coordinates = Vector2(x, y)
				new_star.set_position(Vector2(x, y))
				var curr = galaxy_generator.at(x, y)
				new_star.get_node("Sprite").modulate = Color(galaxy_generator.getRed(curr), galaxy_generator.getGreen(curr), galaxy_generator.getBlue(curr), galaxy_generator.getAlpha(curr))
	print("Generation complete")

func _delete_old_stars():
	var gui_galaxy = $CanvasLayer/MarginContainer/HSplitContainer/VBoxContainer2/GalaxyBox/Galaxy
	for node in gui_galaxy.get_children():
		node.queue_free()

func _spread_stars(factor):
	var gui_galaxy = $CanvasLayer/MarginContainer/HSplitContainer/VBoxContainer2/GalaxyBox/Galaxy
	for node in gui_galaxy.get_children():
		node.position = node.original_coordinates * factor
"""

func _on_Start_pressed():
	galaxy_generator.saveGalaxy("this is a placeholder")

"""
func _on_StarSpreadEdit_text_entered(new_text):
	if (!new_text.empty() and new_text.is_valid_float() and int(new_text) > 0):
		_spread_stars(int(new_text))
"""
