#include <Gameplay/Player.h>
#include <InteractableObjects/InteractableObject.h>
#include <Utils/functions.h>
#include <Utils/Text.h>

#include "IncomeMultiplier.h"

#include <game.h>
#include <template.h>
#include <surface.h>

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
		alertElapsedTime(0),
		priceMultilpier(2.2f),
		incomeMultilpier(1.5f)
	{
		this->textHover = "      'F'\nIncome multiplier";
		this->textHoverPosition = vec2(pos + vec2(5, -66));
		this->alertText = "Not enough coins";
	}

	void IncomeMultiplier::setTexts(vec2 cameraOffset) {
		this->texts.clear();

		this->texts.push_back({ this->textHover,(this->textHoverPosition - cameraOffset), 1, false, true });
		this->texts.push_back({ "Price: " + formatCoins(long long(price)), (this->priceTextPosition - cameraOffset), 1, false, true });
		
		if (this->showAlert) {
			this->texts.push_back({ this->alertText, (this->alertTextPosition - cameraOffset), 1, false });
		}
		
	}

	void IncomeMultiplier::interact(Player& player, Game& game) {
		//check if the player has enough coins
		if (player.getCoins() < this->price) {
			this->showAlert = true;
			return;
		}

		player.spendCoins(int(this->price));

		player.setMultiplier(player.getMultiplier() * this->incomeMultilpier);

		//increase the price for the next purchase
		this->price *= this->priceMultilpier;
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