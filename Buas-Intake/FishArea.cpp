#include "FishArea.h"

namespace Tmpl8 {
	FishArea::FishArea(int type, vec2 pos, vec2 size, Sprite& barSprite) :
		InteractableObject(type,pos,size),
		barSprite(barSprite),
		barPosition(pos)
	{}

	void FishArea::draw(Surface* screen, vec2 cameraOffset) {
		this->drawHitBox(screen, cameraOffset);
	}
}