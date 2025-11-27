#include "FishArea.h"
#include "Player.h"
#include "Text.h"

namespace Tmpl8 {
	FishArea::FishArea(int type, vec2 pos, vec2 size, Sprite& barSprite) :
		InteractableObject(type,pos,size),
		barSprite(barSprite),
		barPosition(pos + vec2(-16, 64))
	{}

	void FishArea::interact(Player& player) {
		if(player.isFishing())
			player.setFishing(false);
		else
			player.setFishing(true);
	}

	void FishArea::showText(Surface* screen, vec2 cameraOffset) {
		Text::drawString("press 'F' to enter start fishing", screen, (this->pos - cameraOffset ));
		printf("IM PRINTING");
	}

	void FishArea::draw(Surface* screen, vec2 cameraOffset) {
		//this->drawHitBox(screen, cameraOffset);
		this->barSprite.Draw(screen, this->barPosition.x - cameraOffset.x, this->barPosition.y - cameraOffset.y);
	}
}