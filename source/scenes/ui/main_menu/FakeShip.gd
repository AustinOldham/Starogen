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

var rotation_multiplier
var direction

func _ready():
	speed = 45
	randomize()
	rotation_degrees = (randf() * 8) * 45
	#print(rotation_degrees)
	direction = Vector2(1,0).rotated(rotation)

func _physics_process(delta):
	move_and_collide(direction * speed * delta)
