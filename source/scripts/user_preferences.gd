extends Node

var current_galaxy = ""
var default_save_path = ""
var default_censored_words_path = ""
var hide_censored_words_popup = false

func _ready():
	default_save_path = OS.get_user_data_dir() + "/saves"
	default_censored_words_path = OS.get_user_data_dir() + "/censored_words_files"
