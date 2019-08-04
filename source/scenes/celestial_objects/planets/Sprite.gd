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

extends Sprite

onready var planet_generator = preload("res://plugins/PlanetGenerator/bin/PlanetGenerator.gdns").new()

func _ready():
	randomize()
	self.texture = planet_generator.getPlanet(int(rand_range(0, 2147483647)), 100)
	self.scale.x = 5
	self.scale.y = 5

#func _process(delta):
#	pass
