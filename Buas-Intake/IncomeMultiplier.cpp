#include "IncomeMultiplier.h"
#include "Text.h"
#include "Player.h"

namespace Tmpl8 {

	IncomeMultiplier::IncomeMultiplier(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size),
		multiplier(1),
		price(100.f),
		priceTextPosition(pos + vec2(0, 0)),
		alertTextPosition(pos + vec2(0, 32)),
		showAlert(false),
		alertTime(2000),
		alertElapsedTime(0)
	{
		this->textHover = "Income multiplier";
		char buffer[64];
		snprintf(buffer, sizeof(buffer), "price: %.2f", price);
		priceText = buffer;
		this->textPosition = vec2(pos + vec2(0, -48));
		this->alertText = "Not enough coins";
	}

	void IncomeMultiplier::showText(Surface* screen, vec2 cameraOffset) {
		Text::drawString(this->textHover, screen, (this->textPosition - cameraOffset));
		Text::drawString(this->priceText, screen, (this->priceTextPosition - cameraOffset));
		if (this->showAlert) {
			Text::drawString(this->alertText, screen, (this->alertTextPosition - cameraOffset));
		}
	}

	void IncomeMultiplier::interact(Player& player) {
		if (player.getCoins() < this->price) {
			this->showAlert = true;
			return;
		}
		printf("price: %2.f", price);

		this->multiplier *= 1.5;

		player.spendCoins(this->price);

		player.setMultiplier(this->multiplier);

		this->price *= this->multiplier;

		printf("price: %2.f", price);
		char buffer[64];
		snprintf(buffer, sizeof(buffer), "price: %.2f", price);
		priceText = buffer;

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