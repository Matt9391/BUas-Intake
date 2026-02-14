#include "StaminaShop.h"
#include "Text.h"
#include "Player.h"
#include <cstdio>
#include "InteractableObject.h"
#include "tmpl8/surface.h"
#include "tmpl8/template.h"
#include "Game.h"

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
		alertElapsedTime(0)
	{
		this->textHover = "Stamina shop";
		this->textPosition = vec2(pos + vec2(12, -56));
		this->alertText = "Not enough coins";
	}
	
	void StaminaShop::showText(Surface* screen, vec2 cameraOffset) {
		Text::drawString(this->textHover, screen, (this->textPosition - cameraOffset));
		Text::drawString("Price: ", screen, (this->priceTextPosition - cameraOffset));
		Text::drawCoins(screen, (this->priceTextPosition + vec2(42, 0) - cameraOffset), long long(price));
		if (this->showAlert) {
			Text::drawString(this->alertText, screen, (this->alertTextPosition - cameraOffset));
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
		this->price *= 3;
		 
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