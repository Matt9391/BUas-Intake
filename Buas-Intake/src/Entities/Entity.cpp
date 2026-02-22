#include "../../tmpl8/surface.h"
#include "../../tmpl8/template.h"
#include "../Gameplay/Player.h"

#include "Entity.h"
#include "../DataTypes/PrintableBox.h"

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

	PrintableBox Entity::getBox(vec2 cameraOffset) {
		return { this->pos - cameraOffset, this->size, this->clr };
	}
}