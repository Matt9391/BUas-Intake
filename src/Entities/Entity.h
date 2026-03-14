#pragma once

#include <surface.h>
#include <template.h>

namespace Tmpl8 {
	class Player;
	struct PrintableBox;
	class Surface;

	//base class for all objects/entities except the player
	class Entity
	{
	public:
		Entity(vec2 pos, vec2 size);

		//check if the entity inteserct with the player
		bool intersectPlayer(Player& player); 

		virtual void update(float dt, Player& player) = 0;
		virtual void draw(Surface* screen, vec2 cameraOffset) = 0;

		//return the hitbox of the entity
		PrintableBox getBox(vec2 cameraOffset) const;
	protected:
		vec2 pos;
		vec2 size;

		Pixel clr;
	};

}
