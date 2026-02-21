#include <cstdio>
#include "../../tmpl8/template.h"
#include "../../tmpl8/surface.h"
#include "../Utils/Text.h"
#include "../Utils/functions.h"
#include "../Gameplay/Player.h"
#include "../GFX/HUD.h"
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
		priceTextPosition(pos + vec2(56, 22)),
		alertTextPosition(pos + vec2(-56, 80)),
		showAlert(false),
		alertTime(2000),
		alertElapsedTime(0),
		firstFine(long long(totalDebt * 0.70)),
		lastFine(long long(totalDebt * 0.30))
	{
		this->textHover = "Pay your debt";
		this->textHoverPosition = vec2(pos + vec2(0, -56));
		this->alertText = "You can't be forgiven yet";
	}

	void DebtHolder::setTexts(vec2 cameraOffset) {
		this->texts.clear();

		this->texts.push_back({ this->textHover, (this->textHoverPosition - cameraOffset), 1 });
		this->texts.push_back({ "Debt left to pay: ", (this->priceTextPosition - cameraOffset), 1 });
		this->texts.push_back({ formatCoins(long long(totalDebt - paidDebt)), (this->priceTextPosition + vec2(50, 16) - cameraOffset), 1 });

		if (this->showAlert) {
			this->texts.push_back({ this->alertText, (this->alertTextPosition - cameraOffset), 1 });
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