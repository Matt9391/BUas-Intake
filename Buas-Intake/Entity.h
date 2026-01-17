#include "template.h"
#include "surface.h"

#pragma once

namespace Tmpl8 {
	class Player;

	class Entity
	{
	public:
		Entity(vec2 pos, vec2 size);

		bool intersectPlayer(Player& player);

		virtual void update(float dt, Player& player) = 0;

		virtual void draw(Surface* screen, vec2 cameraOffset) = 0;

		void drawHitBox(Surface* screen, vec2 cameraOffset, Pixel clr = 0x00000);
		 
	protected:
		vec2 pos;
		vec2 size;

		Pixel clr;
	};

}
