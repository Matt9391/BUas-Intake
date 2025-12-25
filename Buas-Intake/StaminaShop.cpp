#include "StaminaShop.h"
#include "PlayerVisual.h"
#include "Player.h"
#include "MapHandler.h"
#include "game.h"

namespace Tmpl8 {

	StaminaShop::StaminaShop(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size)
	{
		this->textHover = "Stamina shop";
		this->textPosition = vec2(pos + vec2(10, -48));
	}

	void StaminaShop::interact(Player& player) {
		if (player.getPlayerVisual() == PlayerVisual::Human) {
			player.setState(1);
			Game::humanScene = false;
			player.loadMap(&MapHandler::maps2D);
		}
		else {
			player.setState(0); 
			Game::humanScene = true;
			player.loadMap(&MapHandler::mapsTdw	);
		}
	}

	void StaminaShop::draw(Surface* screen, vec2 cameraOffset) {
		//this->drawHitBox(screen, cameraOffset, 0xFF00FF);
		//this->drawHitBox(screen, cameraOffset);
	}
}