#include "./tmpl8/surface.h"
#include "./tmpl8/template.h"
#include "Entity.h"
#include <string>

#pragma once
namespace Tmpl8 {
	class Player;

	class InteractableObject : public Entity
	{
	public:
		InteractableObject(int type, vec2 pos, vec2 size);
		 
		virtual void update(float dt, Player& player);

		virtual void interact(Player& player);

		virtual void showText(Surface* screen, vec2 cameraOffset);

		virtual void draw(Surface* screen, vec2 cameraOffset);

		int type;

	protected:
		

		vec2 textPosition;
		std::string textHover;

	};
}

