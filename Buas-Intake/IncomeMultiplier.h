#include "InteractableObject.h"
#include <string>

#pragma once
namespace Tmpl8 {
	class Surface;
	class Player;
	class vec2;
	class Game;

	//IncomeMultiplier inherits from InteractableObject
	class IncomeMultiplier : public InteractableObject
	{
	public:
		IncomeMultiplier(int type, vec2 pos, vec2 size);
		
		void update(float dt, Player& player) override;
		 
		void interact(Player& player, Game& game) override;
		
		void showText(Surface* screen, vec2 cameraOffset) override;

		static void loadPrice(float loadedPrice);

		static float getPrice();
	private:

		//price needed to buy the income multiplier
		static float price;

		//text to show when not enough coins
		std::string alertText;

		vec2 priceTextPosition;
		vec2 alertTextPosition;

		//alert variables
		bool showAlert;
		float alertTime;
		float alertElapsedTime;

	};


};