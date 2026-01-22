#include "IncomeMultiplier.h"
#include "Text.h"
#include "Player.h"

namespace Tmpl8 {
	float IncomeMultiplier::price = 100.f;

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
		Text::printCoins(screen, (this->priceTextPosition + vec2(42,0) - cameraOffset), long long(price));
		if (this->showAlert) {
			Text::drawString(this->alertText, screen, (this->alertTextPosition - cameraOffset));
		}
	}

	void IncomeMultiplier::interact(Player& player) {
		if (player.getCoins() < this->price) {
			this->showAlert = true;
			return;
		}
		printf("pre price: %2.f ", price);
 
		player.spendCoins(int(this->price));

		player.setMultiplier(player.getMultiplier() * 1.5f);

		this->price *= 2.2;

		printf("post price: %2.f\n", price);

	}

	void IncomeMultiplier::update(float dt, Player& player) {
		if (this->showAlert) {
			this->alertElapsedTime += dt;
			if (this->alertElapsedTime > alertTime) {
				this->alertElapsedTime = 0;
				this->showAlert = false;
			}
		}
	}

	void IncomeMultiplier::draw(Surface* screen, vec2 cameraOffset) {
		//this->drawHitBox(screen, cameraOffset, 0xFF00FF);
		//this->drawHitBox(screen, cameraOffset);
		
	}

};