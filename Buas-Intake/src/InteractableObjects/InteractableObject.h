#include <string>
#include <vector>
#include "../Entities/Entity.h"
#include "../GFX/HUD.h"
#include "../DataTypes/PrintableText.h"

#pragma once
namespace Tmpl8 {
	class Player;
	class Surface;
	class vec2;
	class Game;

	//InteractableObject inherits from Entity
	class InteractableObject : public Entity
	{
	public:
		InteractableObject(int type, vec2 pos, vec2 size);
		 
		virtual void update(float dt, Player& player);

		virtual void interact(Player& player, Game& game);

		virtual void draw(Surface* screen, vec2 cameraOffset);

		virtual std::vector <PrintableText>getTexts();

		virtual void setTexts(vec2 cameraOffset);

		void clearTexts();

		//index of the interactable object type in the file
		int type;

	protected:

		//position to show the text
		vec2 textHoverPosition;
		//text to show when hovering the object
		std::string textHover;

		std::vector<PrintableText> texts;

	};
}

