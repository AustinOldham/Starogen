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

extends Ship

var ai_rotation = 0 #0: nothing, 1: left, 2: right
var ai_thrust = 0 #0 through 4: nothing, 5: backwards, 5 through 10: forwards
var ai_rotation_time = 0
var ai_thrust_time = 0

func _ready():
	randomize()

func _physics_process(delta):
	ai_rotation_time += delta
	ai_thrust_time += delta
	if (ai_rotation_time > 1):
		ai_rotation_time = 0
		ai_rotation = randi() % 3
	if (ai_thrust_time > 4):
		ai_thrust_time = 0
		ai_thrust = randi() % 11
	if (ai_rotation == 1):
		rotation_degrees -= rotation_speed * delta
	if (ai_rotation == 2):
		rotation_degrees += rotation_speed * delta

	var new_direction = Vector2(1,0).rotated(rotation)

	if (ai_thrust > 5):
		current_direction = current_direction.linear_interpolate(new_direction, acceleration)
	elif (ai_thrust > 4):
		current_direction = current_direction.linear_interpolate(-new_direction, acceleration)
	else:
		current_direction = current_direction.linear_interpolate(Vector2(0,0), deceleration)

	move_and_collide(current_direction * speed * delta)
