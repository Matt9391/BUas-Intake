#include "Entity.h"
#include <string>

#pragma once
namespace Tmpl8 {
	class Player;
	class Surface;
	class vec2;

	//InteractableObject inherits from Entity
	class InteractableObject : public Entity
	{
	public:
		InteractableObject(int type, vec2 pos, vec2 size);
		 
		virtual void update(float dt, Player& player);

		virtual void interact(Player& player);

		virtual void showText(Surface* screen, vec2 cameraOffset);

		virtual void draw(Surface* screen, vec2 cameraOffset);

		//index of the interactable object type in the file
		int type;

	protected:

		//position to show the text
		vec2 textPosition;
		//text to show when hovering the object
		std::string textHover;

	};
}

