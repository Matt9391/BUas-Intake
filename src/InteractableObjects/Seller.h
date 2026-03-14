#pragma once

#include <InteractableObjects/InteractableObject.h>

namespace Tmpl8 {
	class vec2;
	class Player;
	class Game;

	//Seller inherits from InteractableObject
	class Seller : public InteractableObject
	{
	public:
		Seller(int type, vec2 pos, vec2 size);

		void interact(Player& player, Game& game) override;
		
		void setTexts(vec2 cameraOffset) override;

	private: 
	};
}

