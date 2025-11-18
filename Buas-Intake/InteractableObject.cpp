#include "InteractableObject.h"
#include "Player.h"

namespace Tmpl8 {

	InteractableObject::InteractableObject(vec2 pos, vec2 size) :
		pos(pos),
		size(size)
	{}

	bool InteractableObject::intersectPlayer(Player& player) {
		vec2 playerPos = player.getPos();
		vec2 playerSize = player.getSize();

		return (playerPos.x > this->pos.x &&
				playerPos.x < this->pos.x + this->size.x &&
				playerPos.y > this->pos.y &&
				playerPos.y < this->pos.y + this->size.y
				) ||
				(playerPos.x + playerSize.x > this->pos.x &&
				playerPos.x + playerSize.x < this->pos.x + this->size.x &&
				playerPos.y > this->pos.y &&
				playerPos.y < this->pos.y + this->size.y
				) ||
				(playerPos.x > this->pos.x &&
				playerPos.x < this->pos.x + this->size.x &&
				playerPos.y + playerSize.y > this->pos.y &&
				playerPos.y + playerSize.y < this->pos.y + this->size.y
				) ||
				(playerPos.x + playerSize.x > this->pos.x &&
				playerPos.x + playerSize.x < this->pos.x + this->size.x &&
				playerPos.y + playerSize.y > this->pos.y &&
				playerPos.y + playerSize.y < this->pos.y + this->size.y
				);

		return false;
	}

	void InteractableObject::drawHitBox(Surface* screen, vec2 cameraOffset) {
		const int size = this->size.x;
		Pixel red = 0xFF0000; // formato: 0xRRGGBB

		Pixel* buffer = screen->GetBuffer();
		int pitch = screen->GetPitch(); // pixel per riga
		vec2 pos(this->pos.x - cameraOffset.x, this->pos.y - cameraOffset.y);

		for (int dy = 0; dy < size; dy++)
		{
			int py = pos.y + dy;
			if (py < 0 || py >= screen->GetHeight()) continue;

			for (int dx = 0; dx < size; dx++)
			{
				int px = pos.x + dx;
				if (px < 0 || px >= screen->GetWidth()) continue;

				buffer[px + py * pitch] = red;
			}
		}
	}
}