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

extends PanelContainer

var width = 500

func _ready():
	pass

func _input(event):
	if event is InputEventMouseButton and event.button_index == BUTTON_LEFT and event.is_pressed():
		self.on_click()

func on_click():
	print("Click")
	print(get_global_mouse_position())
	print($Galaxy/Sprite.get_global_transform().origin)
	#var x = get_global_mouse_position().x - ($Galaxy/Sprite.get_global_transform().origin.x * (width / ($Galaxy/Sprite.scale.x * width)))
	#var y = get_global_mouse_position().y - ($Galaxy/Sprite.get_global_transform().origin.y * (width / ($Galaxy/Sprite.scale.y * width)))
	var x = (get_global_mouse_position().x - $Galaxy/Sprite.get_global_transform().origin.x) * (width / ($Galaxy/Sprite.scale.x * width))
	var y = (get_global_mouse_position().y - $Galaxy/Sprite.get_global_transform().origin.y) * (width / ($Galaxy/Sprite.scale.y * width))
	print("x: " + str(x) + "  y: " + str(y))
	if (x < width and y < width and x >= 0 and y >= 0):
		print("Contained")

