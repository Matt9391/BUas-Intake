#include "template.h"
#include "surface.h"

#pragma once
namespace Tmpl8 {
	class Player;

	class InteractableObject
	{
	public:
		InteractableObject(int type, vec2 pos, vec2 size);

		bool intersectPlayer(Player& player);

		//virtual void interact(Player& player) = 0;

		void drawHitBox(Surface* screen, vec2 cameraOffset);
	private:
		int type;
		vec2 pos;
		vec2 size;
	};
}

