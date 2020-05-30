extends Node

var current_galaxy = ""
var default_save_path = ""

func _ready():
	default_save_path = OS.get_user_data_dir() + "/saves"
