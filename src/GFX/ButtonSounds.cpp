#pragma once
#include <iostream>
#include "../../tmpl8/template.h"
#include "../DataTypes/PrintableText.h"
#include "../DataTypes/SceneType.h"
#include "../Utils/functions.h"
#include "ButtonSounds.h"
#include "../game.h"
#include "Button.h"

namespace Tmpl8 {

	ButtonSounds::ButtonSounds(const PrintableText& text, const vec2& fontSize) :
		Button(text, fontSize),
		soundsState(true)
	{}

	void ButtonSounds::onClick(Game& game) {
		this->soundsState = !this->soundsState;
		this->text.text = this->soundsState ? "Disable Sounds" : "Enable Sounds";
		game.getAudioManager().setSoundPlaying(this->soundsState);
	}
}