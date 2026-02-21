#include <string>
#include "InteractableObject.h"
#pragma once

namespace Tmpl8 {

	class vec2;
	class Player;
	class Surface;
	class Game;

	//StaminaShop inherits from InteractableObject
	class StaminaShop : public InteractableObject
	{
	public:
		StaminaShop(int type, vec2 pos, vec2 size);
		 
		void update(float dt, Player& player) override;

		void interact(Player& player, Game& game) override;

		void setTexts(vec2 cameraOffset) override;

		//load price from game saves
		static void loadPrice(float loadedPrice);
		
		static float getPrice();
	private:
		//current price of the stamina shop
		static float price;

		//alert if not enough coins
		std::string alertText;

		vec2 priceTextPosition;
		vec2 alertTextPosition;

		//alert variables
		bool showAlert;
		float alertTime;
		float alertElapsedTime;
	};
}

