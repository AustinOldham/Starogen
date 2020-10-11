extends Node2D

func _ready():
	$CanvasLayer/MarginContainer/HSplitContainer2/VBoxContainer2/GalaxyBox/Galaxy.load_galaxy(UserPreferences.current_galaxy)
