#include <DataTypes/PrintableText.h>
#include <DataTypes/SceneType.h>
#include <Utils/functions.h>
#include <GFX/Button.h>
#include "ButtonDebug.h"

#include <game.h>
#include <template.h>

namespace Tmpl8 {

	ButtonDebug::ButtonDebug(const PrintableText& text, const vec2& fontSize) :
		Button(text, fontSize),
		debugState(false)
	{}

	void ButtonDebug::onClick(Game& game) {
		this->debugState = !this->debugState;
		this->text.text = this->debugState ? "Disable Debug" : "Enable Debug";
		game.setDebug(this->debugState);
	}
}