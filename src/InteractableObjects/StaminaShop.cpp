#include <Utils/Text.h>
#include <Utils/functions.h>
#include <Gameplay/Player.h>
#include <InteractableObjects/InteractableObject.h>
#include "StaminaShop.h"

#include <game.h>
#include <surface.h>
#include <template.h>

namespace Tmpl8 {
	//deafult price of the stamina shop
	float StaminaShop::price = 200.f;

	void StaminaShop::loadPrice(float loadedPrice) {
		price = loadedPrice;
	}

	float StaminaShop::getPrice() {
		return price;
	}

	StaminaShop::StaminaShop(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size),
		priceTextPosition(pos + vec2(20, -44)),
		alertTextPosition(pos + vec2(0, 56)),
		showAlert(false),
		alertTime(2000), 
		alertElapsedTime(0),
		priceMultiplier(3.f)
	{
		this->textHover = "Stamina shop";
		this->textHoverPosition = vec2(pos + vec2(12, -56));
		this->alertText = "Not enough coins";
	}

	void StaminaShop::setTexts(vec2 cameraOffset) {
		this->texts.clear();

		this->texts.push_back({ this->textHover,(this->textHoverPosition - cameraOffset), 1, false, true });
		this->texts.push_back({ "Price: " + formatCoins(long long(price)), (this->priceTextPosition - cameraOffset), 1, false, true });
		if (this->showAlert) {
			this->texts.push_back({ this->alertText, (this->alertTextPosition - cameraOffset), 1, false });
		}

	}


	void StaminaShop::interact(Player& player, Game& game) {
		//check if the player has enough coins
		if (player.getCoins() < this->price) {
			this->showAlert = true;
			return;
		}
		
		player.spendCoins(int(this->price));

		player.addStamina(1000); //1000ms -> 1 second of stamina

		//triple the price for the next purchase
		this->price *= priceMultiplier;
		 
	}

	void StaminaShop::update(float dt, Player& player) {
		if (this->showAlert) {
			this->alertElapsedTime += dt;
			if (this->alertElapsedTime > alertTime) {
				this->alertElapsedTime = 0;
				this->showAlert = false;
			}
		}
	}

}