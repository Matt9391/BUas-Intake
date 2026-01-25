#include "./tmpl8/surface.h"
#include "./tmpl8/template.h"

#pragma once

namespace Tmpl8 {
	class Player;

	//base class for all objects / entities except the player
	class Entity
	{
	public:
		Entity(vec2 pos, vec2 size);

		//check if the entity inteserct with the player
		bool intersectPlayer(Player& player); 

		//virtual method to allow child classes to implement custom behavior
		virtual void update(float dt, Player& player) = 0;

		//virtual method to allow child classes to implement custom behavior
		virtual void draw(Surface* screen, vec2 cameraOffset) = 0;

		//function that draw entity hitbox
		void drawHitBox(Surface* screen, vec2 cameraOffset, Pixel clr = 0x00000);
		 
	protected:
		vec2 pos;
		vec2 size;

		Pixel clr;
	};

}
