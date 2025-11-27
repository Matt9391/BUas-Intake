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

		virtual void update(float dt);

		virtual void interact(Player& player);

		virtual void showText(Surface* screen, vec2 cameraOffset);
		virtual void draw(Surface* screen, vec2 cameraOffset);

		void drawHitBox(Surface* screen, vec2 cameraOffset);
	protected:
		int type;
		vec2 pos;
		vec2 size;
	};
}

