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

var editableImage
#var imageSize = Vector2(800, 600)
#var imageSize = Vector2(10, 20)
var imageSize = Vector2(100, 100)
var imageFormat = Image.FORMAT_RGBA8
var imageTexture

func _ready():
	#Image is a built-in type
	#editableImage = Image(imageSize.x, imageSize.y, false, imageFormat)
	editableImage = Image.new()
	editableImage.create(imageSize.x, imageSize.y, false, imageFormat) 
	
	print("here")
	editableImage.lock()
	#for x in range(10):
	#	for y in range(20):
	#		editableImage.set_pixel(x, y, Color( 0, 1, 0, 1 ))
	
	for x in range(100):
		for y in range(100):
			editableImage.set_pixel(x, y, Color( 0, 1, 0, 1 ))
	
	
	editableImage.unlock()
	imageTexture = ImageTexture.new()
	imageTexture.create_from_image(editableImage)
	$Sprite.texture = imageTexture
	$Sprite.scale.x = 10
	#set_process_input(true)

#func _input(event):
#	if(event is InputEventMouseMotion):
#		editableImage.set_pixel(get_viewport().get_mouse_position().x, get_viewport().get_mouse_position().y, Color(0, 0, 0))
#		imageTexture.set_data(editableImage)
#		imageTexture.set_data(editableImage)
#		#print(get_viewport().get_mouse_position())