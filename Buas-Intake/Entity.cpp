#include "Entity.h"
#include "Player.h"
#include "tmpl8/surface.h"
#include "tmpl8/template.h"

namespace Tmpl8 {

	Entity::Entity(vec2 pos, vec2 size) :
		pos(pos),
		size(size),
		clr(0xFF0000) //default red color
	{}

	bool Entity::intersectPlayer(Player& player) {
		vec2 playerPos = player.getPos(); 
		vec2 playerSize = player.getSize();

		bool cond =(playerPos.x > this->pos.x && //top-left corner of player hitbox
					playerPos.x < this->pos.x + this->size.x &&
					playerPos.y > this->pos.y &&
					playerPos.y < this->pos.y + this->size.y
				   ) || //top-right corner of player hitbox
				   (playerPos.x + playerSize.x > this->pos.x &&
					playerPos.x + playerSize.x < this->pos.x + this->size.x &&
					playerPos.y > this->pos.y &&
					playerPos.y < this->pos.y + this->size.y
				   ) || //bottom-left corner of player hitbox
				   (playerPos.x > this->pos.x &&
					playerPos.x < this->pos.x + this->size.x &&
					playerPos.y + playerSize.y > this->pos.y &&
					playerPos.y + playerSize.y < this->pos.y + this->size.y
				   ) || //bottom-right corner of player hitbox
				   (playerPos.x + playerSize.x > this->pos.x &&
					playerPos.x + playerSize.x < this->pos.x + this->size.x &&
					playerPos.y + playerSize.y > this->pos.y &&
					playerPos.y + playerSize.y < this->pos.y + this->size.y
				   );

		//set the colour of the hitbox to green if colliding, red if not
		if (cond)
			clr = 0x00FF00; //green
		else
			clr = 0xFF0000; //redd

		return cond;
		 

	}

	void Entity::drawHitBox(Surface* screen, vec2 cameraOffset, Pixel clr) {
		if (clr != 0x00000)
			this->clr = clr;

		Pixel* buffer = screen->GetBuffer(); //gets the screen buffer (array of pixels)
		int pitch = screen->GetPitch(); //pixels for each row
		//set position of drawing
		vec2 pos(this->pos.x - cameraOffset.x, this->pos.y - cameraOffset.y);

		for (int dy = 0; dy < size.y; dy++)
		{
			//py = pixel y
			int py = int(pos.y) + dy; 
			//check if it's in the screen bounds
			if (py < 0 || py >= screen->GetHeight()) continue;

			for (int dx = 0; dx < size.x; dx++)
			{
				//px = pixel x
				int px = int(pos.x) + dx;
				//check if it's in the screen bounds
				if (px < 0 || px >= screen->GetWidth()) continue;

				//set the screen pixel (px+py*pitch) to the color
				buffer[px + py * pitch] = this->clr;
			}
		}
	}
}