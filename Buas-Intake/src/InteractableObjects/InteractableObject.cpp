#include <cstdio>
#include "../../tmpl8/surface.h"
#include "../../tmpl8/template.h"
#include "../Utils/Text.h"
#include "../Gameplay/Player.h"
#include "../game.h"

#include "InteractableObject.h"
#include <vector>
#include "../DataTypes/PrintableText.h"
#include "../Entities/Entity.h"
#include "../GFX/HUD.h"

namespace Tmpl8 {

	InteractableObject::InteractableObject(int type, vec2 pos, vec2 size) :
		Entity(pos,size),
		type(type),
		textHover("Plain text"),
		textHoverPosition(pos)
	{}
	 
	//blank class methods
	void InteractableObject::update(float dt, Player& player) {}

	void InteractableObject::interact(Player& player, Game& game) { 
		printf("Interacted\n");
	}

	std::vector <PrintableText>InteractableObject::getTexts() {
		return this->texts;
	}

	void InteractableObject::setTexts(vec2 cameraOffset) {
		this->texts.clear();

		this->texts.push_back({ this->textHover, this->textHoverPosition - cameraOffset, 1 });
	
}

	void InteractableObject::clearTexts() {
		this->texts.clear();
	}

	void InteractableObject::draw(Surface* screen, vec2 cameraOffset) {}

	
}