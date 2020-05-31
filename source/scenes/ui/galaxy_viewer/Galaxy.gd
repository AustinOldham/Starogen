# Copyright (C) 2020  Austin Oldham
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

onready var star_info_panel = get_node("../../../VBoxContainer/StarInfoPanel")

var star_dict = {}

var zoom_factor = 1.1

var current_spread_factor = 1

func _ready():
	pass

func _input(event):
	if event is InputEventMouse:
		if event.is_pressed() and not event.is_echo():
			var mouse_position = event.position
			if event.button_index == BUTTON_WHEEL_UP:
				_zoom_at_point(zoom_factor, mouse_position)
			elif event.button_index == BUTTON_WHEEL_DOWN:
				_zoom_at_point(1 / zoom_factor, mouse_position)
	if event is InputEventMouseButton and event.button_index == BUTTON_LEFT and event.is_pressed():
		self._on_click()


func _zoom_at_point(zoom_change, mouse_position):
	scale = scale * zoom_change
	var delta_x = (mouse_position.x - global_position.x) * (zoom_change - 1)
	var delta_y = (mouse_position.y - global_position.y) * (zoom_change - 1)
	global_position.x = global_position.x - delta_x
	global_position.y = global_position.y - delta_y


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

func generate_galaxy():
	_delete_old_stars()
	print("Generation started")
	galaxy_generator.generateGalaxy()
	print("Generation complete")
	_draw_stars()

func load_galaxy(galaxy_name):
	load_galaxy_path(UserPreferences.default_save_path, galaxy_name)

func load_galaxy_path(path, galaxy_name):
	var dir = Directory.new()
	dir.make_dir_recursive(path)
	# TODO: Use the galaxy manager instead
	galaxy_generator.loadGalaxy(path, galaxy_name)
	_delete_old_stars()
	_draw_stars()

func save_galaxy():
	save_galaxy_path(UserPreferences.default_save_path)

func save_galaxy_path(path):
	var dir = Directory.new()
	dir.make_dir_recursive(path)
	print(path)
	galaxy_generator.saveGalaxy(path)

func _draw_stars():
	print("Drawing stars")
	star_dict.clear()
	for y in range(galaxy_generator.getPixels()):
		for x in range(galaxy_generator.getPixels()):
			if (galaxy_generator.getStarTypeIDAt(x, y) != -1):
				# print(Vector2(x, y))
				var new_star = galaxy_star.instance()
				add_child(new_star)
				new_star.original_coordinates = Vector2(x, y)
				new_star.set_position(Vector2(x, y))
				var curr = galaxy_generator.getStarTypeIDAt(x, y)
				new_star.get_node("Sprite").modulate = Color(galaxy_generator.getRed(curr), galaxy_generator.getGreen(curr), galaxy_generator.getBlue(curr), galaxy_generator.getAlpha(curr))
				star_dict[Vector2(x, y)] = new_star
	print("Finished drawing stars")
	_spread_stars(current_spread_factor)

func _delete_old_stars():
	for node in get_children():
		node.queue_free()

func _spread_stars(factor):
	current_spread_factor = factor
	for node in get_children():
		node.position = node.original_coordinates * factor

func _on_StarSpreadEdit_text_entered(new_text):
	if (!new_text.empty() and new_text.is_valid_float() and int(new_text) > 0):
		_spread_stars(int(new_text))


func _on_click():
	print("Click")
	print(get_global_mouse_position())
	print(get_global_transform().origin)

	var x = (get_global_mouse_position().x - get_global_transform().origin.x) / scale.x
	var y = (get_global_mouse_position().y - get_global_transform().origin.y) / scale.y
	x = x / current_spread_factor
	y = y / current_spread_factor
	x = int(x)
	y = int(y)

	print("sprite x: " + str(x) + "  sprite y: " + str(y))
	if (x < galaxy_generator.getPixels() and y < galaxy_generator.getPixels() and x >= 0 and y >= 0):
		print("Contained")
		var curr_star = star_dict.get(Vector2(x, y))
		if (curr_star != null):
			print(galaxy_generator.getStarNameAt(curr_star.original_coordinates.x, curr_star.original_coordinates.y) + " is a star at " + str(curr_star.original_coordinates.x) + " " + str(curr_star.original_coordinates.y))
			star_info_panel.get_node("ScrollContainer/VBoxContainer/DynamicCurrStarLabel").text = galaxy_generator.getStarNameAt(curr_star.original_coordinates.x, curr_star.original_coordinates.y)
			
