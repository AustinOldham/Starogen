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


const ClickableStar = preload("res://scenes/ui/galaxy_viewer/ClickableStar.gd")


func _ready():
	var i = 0
	var objects = 25
	var columns = int(sqrt(objects))
	$GalaxyGrid.columns = columns
	while (i < objects):
		var myButton = ClickableStar.new()
		myButton.set_modulate(Color(0, 0.5, 0, 1))
		var myTexture = load("res://images/ui/galaxy_viewer/white_pixel.png")
		myButton.texture_normal = myTexture
		myButton.connect("pressed", self, "my_button_test", [myButton])
		$GalaxyGrid.add_child(myButton)
		i = i + 1

func my_button_test(myButton):
	print(myButton.num)

