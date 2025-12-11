#include "template.h"
#include "surface.h"
#include <string>

#pragma once
namespace Tmpl8 {
	class Player;

	class InteractableObject
	{
	public:
		InteractableObject(int type, vec2 pos, vec2 size);

		bool intersectPlayer(Player& player);

		virtual void update(float dt, Player& player);

		virtual void interact(Player& player);

		virtual void showText(Surface* screen, vec2 cameraOffset);

		virtual void draw(Surface* screen, vec2 cameraOffset);

		void drawHitBox(Surface* screen, vec2 cameraOffset, Pixel clr = 0x00000);
	protected:
		Pixel clr;

		int type;
		vec2 pos;
		vec2 size;

		vec2 textPosition;
		std::string textHover;

	};
}

