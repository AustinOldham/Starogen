extends WindowDialog

func _ready():
	pass

func _on_WarningPopup_resized():
	$MarginContainer.rect_size = rect_size


func _on_CheckBox_toggled(button_pressed):
	UserPreferences.hide_censored_words_popup = bool(button_pressed)
