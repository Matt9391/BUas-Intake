#include "InteractableObject.h"

#pragma once

namespace Tmpl8 {

	class StaminaShop : public InteractableObject
	{
	public:
		StaminaShop(int type, vec2 pos, vec2 size);

		void update(float dt, Player& player) override;

		void interact(Player& player) override;

		void showText(Surface* screen, vec2 cameraOffset) override;

		void draw(Surface* screen, vec2 cameraOffset) override;
	private:
		static float price;

		std::string alertText;

		vec2 priceTextPosition;
		vec2 alertTextPosition;

		bool showAlert;
		float alertTime;
		float alertElapsedTime;
	};
}

