#include <cstdio>
#include "../../tmpl8/template.h"
#include "../../tmpl8/surface.h"
#include "../Utils/Text.h"
#include "../Gameplay/Player.h"
#include "../game.h"

#include "DebtHolder.h"

namespace Tmpl8 {
	long long DebtHolder::totalDebt = 1'000'000'000;
	long long DebtHolder::paidDebt = 0;

	void DebtHolder::loadPaidDebt(long long loadedDebt) {
		paidDebt = loadedDebt;
	}

	long long DebtHolder::getPaidDebt() {
		return paidDebt;
	}

	DebtHolder::DebtHolder(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size),
		priceTextPosition(pos + vec2(20, -44)),
		alertTextPosition(pos + vec2(0, 56)),
		showAlert(false),
		alertTime(2000),
		alertElapsedTime(0),
		firstFine(long long(totalDebt * 0.70)),
		lastFine(long long(totalDebt * 0.30))
	{
		this->textHover = "Pay your debt";
		this->textPosition = vec2(pos + vec2(0, -56));
		this->alertText = "You can't be forgiven yet";
	}

	void DebtHolder::showText(Surface* screen, vec2 cameraOffset) {
		Text::drawString(this->textHover, screen, (this->textPosition - cameraOffset));
		Text::drawString("Price: ", screen, (this->priceTextPosition - cameraOffset));
		Text::drawCoins(screen, (this->priceTextPosition + vec2(42, 0) - cameraOffset), long long(totalDebt));
		if (this->showAlert) {
			Text::drawString(this->alertText, screen, (this->alertTextPosition - cameraOffset));
		}
	}

	void DebtHolder::interact(Player& player, Game& game) {
		//check if the "first" part of the debt is paid
		if (this->paidDebt < this->firstFine) {
			this->showAlert = true;
			return;
		}
		//if paid
		//check if the player has enough coins to pay off the full debt
		if (player.getCoins() >= this->lastFine) {
			//if so, spend the coins and pay the debt
			player.spendCoins(int(this->lastFine));
			printf("GAME DONE");
		}else {
			this->alertText = "You still have to an ultimate fine of 300M";
			this->showAlert = true;
		}

	}

	void DebtHolder::update(float dt, Player& player) {
		//if alert is showing, update the timer
		if (this->showAlert) {
			this->alertElapsedTime += dt;
			if (this->alertElapsedTime > alertTime) {
				this->alertElapsedTime = 0;
				this->showAlert = false;
			}
		}
	}
}