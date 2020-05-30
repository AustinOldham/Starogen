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

extends CanvasLayer


func _ready():
	$MarginContainer/VBoxContainer/MenuOptions/Continue.connect("pressed", self, "continue_game")
	$MarginContainer/VBoxContainer/MenuOptions/NewGame.connect("pressed", self, "new_game")
	$MarginContainer/VBoxContainer/MenuOptions/Options.connect("pressed", self, "options")
	$MarginContainer/VBoxContainer/MenuOptions/Credits.connect("pressed", self, "credits")
	$MarginContainer/VBoxContainer/MenuOptions/Quit.connect("pressed", self, "quit_game")

func continue_game():
	# get_tree().change_scene("res://prototypes/sample_space/SampleSpace.tscn")
	get_tree().change_scene("res://scenes/ui/SaveSelector.tscn")

func new_game():
	get_tree().change_scene("res://scenes/ui/galaxy_viewer/GalaxyViewer.tscn")

func options():
	pass

func credits():
	pass

func quit_game():
	get_tree().quit()
