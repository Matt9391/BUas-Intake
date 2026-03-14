#include <DataTypes/PrintableText.h>
#include <Entities/Entity.h>
#include <Gameplay/Player.h>
#include <GFX/HUD.h>
#include <Utils/Text.h>
#include "InteractableObject.h"

#include <game.h>
#include <surface.h>
#include <template.h>

#include <vector>

namespace Tmpl8 {

	InteractableObject::InteractableObject(int type, vec2 pos, vec2 size) :
		Entity(pos,size),
		type(type),
		textHover("Plain text"),
		textHoverPosition(pos)
	{}
	 
	//blank class methods
	void InteractableObject::update(float dt, Player& player) {}

	void InteractableObject::interact(Player& player, Game& game) {}

	std::vector <PrintableText>InteractableObject::getTexts() {
		return this->texts;
	}

	void InteractableObject::setTexts(vec2 cameraOffset) {
		this->texts.clear();

		this->texts.push_back({ this->textHover, this->textHoverPosition - cameraOffset, 1, false });
	
	}

	void InteractableObject::clearTexts() {
		this->texts.clear();
	}

	void InteractableObject::draw(Surface* screen, vec2 cameraOffset) {}

	
}