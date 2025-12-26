#include "Gate.h"
#include "PlayerVisual.h"
#include "Player.h"
#include "MapHandler.h"
#include "game.h"

namespace Tmpl8 {

	Gate::Gate(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size)
	{
		this->textHover = "Gate";
		this->textPosition = vec2(pos + vec2(10, -48));
	}

	void Gate::interact(Player& player) {
		if (player.getPlayerVisual() == PlayerVisual::Human) {
			Game::changeScene(1);
		}
		else {
			Game::changeScene(0);
		}
	}

	void Gate::draw(Surface* screen, vec2 cameraOffset) {
		//this->drawHitBox(screen, cameraOffset, 0xFF00FF);
		//this->drawHitBox(screen, cameraOffset);
	}
}