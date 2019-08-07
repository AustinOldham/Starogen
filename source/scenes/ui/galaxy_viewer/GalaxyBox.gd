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

extends ViewportContainer

var width = 500

func _ready():
	pass

func _input(event):
	if event is InputEventMouseButton and event.button_index == BUTTON_LEFT and event.is_pressed():
		self.on_click()

func on_click():
	print("Click")
	print(get_global_mouse_position())
	print(get_global_transform().origin)
	var x = get_global_mouse_position().x - get_global_transform().origin.x
	var y = get_global_mouse_position().y - get_global_transform().origin.y
	print("x: " + str(x) + "  y: " + str(y))
	if (x < width and y < width and x >= 0 and y >= 0):
		print("Contained")