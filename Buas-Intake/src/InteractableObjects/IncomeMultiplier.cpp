#include <cstdio>
#include "../../tmpl8/template.h"
#include "../../tmpl8/surface.h"
#include "../Utils/Text.h"
#include "../Utils/functions.h"
#include "../Gameplay/Player.h"
#include "../game.h"

#include "IncomeMultiplier.h"

namespace Tmpl8 {
	float IncomeMultiplier::price = 100.f;

	void IncomeMultiplier::loadPrice(float loadedPrice) {
		price = loadedPrice;
	}

	float IncomeMultiplier::getPrice() {
		return price;
	}

	IncomeMultiplier::IncomeMultiplier(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size),
		priceTextPosition(pos + vec2(20, -44)), 
		alertTextPosition(pos + vec2(0, 56)),
		showAlert(false),
		alertTime(2000),
		alertElapsedTime(0)
	{
		this->textHover = "Income multiplier";
		this->textHoverPosition = vec2(pos + vec2(0, -56));
		this->alertText = "Not enough coins";
	}

	void IncomeMultiplier::setTexts(vec2 cameraOffset) {
		this->texts.clear();

		this->texts.push_back({ this->textHover,(this->textHoverPosition - cameraOffset), 1 });
		this->texts.push_back({ "Price: ", (this->priceTextPosition - cameraOffset), 1 });
		this->texts.push_back({ formatCoins(long long(price)), (this->priceTextPosition + vec2(42, 0) - cameraOffset), 1 });
		if (this->showAlert) {
			this->texts.push_back({ this->alertText, (this->alertTextPosition - cameraOffset), 1 });
		}
		
	}

	void IncomeMultiplier::interact(Player& player, Game& game) {
		//check if the player has enough coins
		if (player.getCoins() < this->price) {
			this->showAlert = true;
			return;
		}

		//if so, spend the coins and apply the income multiplier 
		player.spendCoins(int(this->price));

		player.setMultiplier(player.getMultiplier() * 1.5f);

		//increase the price for the next purchase
		this->price *= 2.2;
	}

	void IncomeMultiplier::update(float dt, Player& player) {
		//if alert is showing, update the timer
		if (this->showAlert) {
			this->alertElapsedTime += dt;
			if (this->alertElapsedTime > alertTime) {
				this->alertElapsedTime = 0;
				this->showAlert = false;
			}
		}
	}


};