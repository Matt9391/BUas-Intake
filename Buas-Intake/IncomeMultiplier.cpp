#include "IncomeMultiplier.h"
#include "Text.h"
#include "Player.h"
#include "tmpl8/surface.h"
#include "tmpl8/template.h"
#include <cstdio>

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
		this->textPosition = vec2(pos + vec2(0, -56));
		this->alertText = "Not enough coins";
	}

	void IncomeMultiplier::showText(Surface* screen, vec2 cameraOffset) {
		Text::drawString(this->textHover, screen, (this->textPosition - cameraOffset));
		Text::drawString("Price: ", screen, (this->priceTextPosition - cameraOffset));
		Text::drawCoins(screen, (this->priceTextPosition + vec2(42,0) - cameraOffset), long long(price));
		if (this->showAlert) {
			Text::drawString(this->alertText, screen, (this->alertTextPosition - cameraOffset));
		}
	}

	void IncomeMultiplier::interact(Player& player) {
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