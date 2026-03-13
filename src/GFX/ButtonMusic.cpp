#pragma once
#include <iostream>
#include "../../tmpl8/template.h"
#include "../DataTypes/PrintableText.h"
#include "../DataTypes/SceneType.h"
#include "../Utils/functions.h"
#include "ButtonMusic.h"
#include "../game.h"
#include "Button.h"

namespace Tmpl8 {

	ButtonMusic::ButtonMusic(const PrintableText& text, const vec2& fontSize) :
		Button(text, fontSize),
		musicState(true)
	{}

	void ButtonMusic::onClick(Game& game) {
		this->musicState= !this->musicState;
		this->text.text = this->musicState ? "Disable music" : "Enable music";
		game.getAudioManager().setMusicPlaying(this->musicState);
	}
}