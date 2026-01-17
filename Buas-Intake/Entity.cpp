#include "Entity.h"
#include "Player.h"

namespace Tmpl8 {

	Entity::Entity(vec2 pos, vec2 size) :
		pos(pos),
		size(size),
		clr(0xFF0000)
	{}

	bool Entity::intersectPlayer(Player& player) {
		vec2 playerPos = player.getPos();
		vec2 playerSize = player.getSize();

		bool cond = (playerPos.x > this->pos.x &&
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

		if (cond)
			clr = 0x00FF00;
		else
			clr = 0xFF0000;

		return cond;
		 

	}

	void Entity::drawHitBox(Surface* screen, vec2 cameraOffset, Pixel clr) {
		if (clr != 0x00000)
			this->clr = clr;

		Pixel* buffer = screen->GetBuffer();
		int pitch = screen->GetPitch(); // pixel per riga
		vec2 pos(this->pos.x - cameraOffset.x, this->pos.y - cameraOffset.y);

		for (int dy = 0; dy < size.y; dy++)
		{
			int py = int(pos.y) + dy;
			if (py < 0 || py >= screen->GetHeight()) continue;

			for (int dx = 0; dx < size.x; dx++)
			{
				int px = int(pos.x) + dx;
				if (px < 0 || px >= screen->GetWidth()) continue;

				buffer[px + py * pitch] = this->clr;
			}
		}
	}
}