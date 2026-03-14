#include <DataTypes/PrintableText.h>
#include <DataTypes/SceneType.h>
#include <Utils/functions.h>
#include "Button.h"

#include <template.h>

namespace Tmpl8 {

	Button::Button(PrintableText text, const vec2& fontSize) :
		text(text),
		fontSize(fontSize),
		elapsedTime(0.f),
		timer(200.f),
		disabled(false)
	{}

	bool Button::mouseHover(vec2 mousePos) const {
			return  mousePos.x > text.pos.x - 1.f * fontSize.x * text.scale &&
					mousePos.x < text.pos.x + (1 + getMaxLengthLines(text.text)) * fontSize.x * text.scale &&
					mousePos.y > text.pos.y - 1.f * fontSize.y * text.scale &&
					mousePos.y < text.pos.y + (1 + countLines(text.text)) * fontSize.y * text.scale;
	}

	void Button::update(float dt) {
		if (disabled) {
			this->elapsedTime += dt;
			if (this->elapsedTime > this->timer) {
				this->disabled = false;
				this->elapsedTime = 0.f;
			}
		}
	}

	void Button::setDisable(bool disable) {
		this->disabled = disable;
	}

	void Button::onClick(Game& game) {
		this->disabled = true;
	}

	bool Button::isDisabled() const {
		return this->disabled;
	}

	PrintableText Button::getText() const {
		return this->text;
	}
}