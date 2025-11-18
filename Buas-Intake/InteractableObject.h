#include "template.h"
#include "surface.h"

#pragma once
namespace Tmpl8 {
	class Player;

	class InteractableObject
	{
	public:
		InteractableObject(vec2 pos, vec2 size);

		bool intersectPlayer(Player& player);

		void drawHitBox(Surface* screen, vec2 cameraOffset);
	private:
		vec2 pos;
		vec2 size;
	};
}

