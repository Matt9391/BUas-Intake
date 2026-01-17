#include "InteractableObject.h"
#include "Player.h"
#include "Text.h"

namespace Tmpl8 {

	InteractableObject::InteractableObject(int type, vec2 pos, vec2 size) :
		Entity(pos,size),
		type(type),
		textHover("Plain text"),
		textPosition(pos)
	{}
	 
	void InteractableObject::update(float dt, Player& player) {
		
	}

	void InteractableObject::interact(Player& player) {
		printf("BOBBI\n");
	}

	void InteractableObject::showText(Surface* screen, vec2 cameraOffset) {
		Text::drawString(this->textHover, screen, this->textPosition - cameraOffset);
	}

	void InteractableObject::draw(Surface* screen, vec2 cameraOffset) {
		//this->drawHitBox(screen, cameraOffset);
	}

	
}