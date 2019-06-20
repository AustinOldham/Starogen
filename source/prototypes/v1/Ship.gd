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

extends KinematicBody2D

export (int) var rotation_speed = 180
export (int) var speed = 150
export (float) var acceleration = 0.10
export (float) var deceleration = 0.01
var current_direction = Vector2(0,0)

func _physics_process(delta):
	if (Input.is_action_pressed("ui_left")):
		rotation_degrees -= rotation_speed * delta
	if (Input.is_action_pressed("ui_right")):
		rotation_degrees += rotation_speed * delta

	var new_direction = Vector2(1,0).rotated(rotation)

	if (Input.is_action_pressed("ui_up")):
		current_direction = current_direction.linear_interpolate(new_direction, acceleration)
	elif (Input.is_action_pressed("ui_down")):
		current_direction = current_direction.linear_interpolate(-new_direction, acceleration)
	else:
		current_direction = current_direction.linear_interpolate(Vector2(0,0), deceleration)

	move_and_collide(current_direction * speed * delta)