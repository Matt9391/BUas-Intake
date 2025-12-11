#include "IncomeMultiplier.h"
#include "Text.h"

namespace Tmpl8 {

	IncomeMultiplier::IncomeMultiplier(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size),
		multiplier(1),
		price(100.f)
	{
		this->textHover = "Income multiplier";
		this->textPosition = vec2(pos + vec2(0, -48));
	}

	/*void IncomeMultiplier::showText(Surface* screen, vec2 cameraOffset) {
		Text::drawString(this->textHover, screen, (this->textPosition - cameraOffset));
	}*/

	void IncomeMultiplier::draw(Surface* screen, vec2 cameraOffset) {
		//this->drawHitBox(screen, cameraOffset, 0xFF00FF);
		//this->drawHitBox(screen, cameraOffset);
	}

};