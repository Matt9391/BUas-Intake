#include <DataTypes/Fish.h>
#include <DataTypes/ChestObject.h>
#include <Gameplay/Player.h>
#include <InteractableObjects/InteractableObject.h>
#include "Seller.h"

#include <game.h>
#include <template.h>

namespace Tmpl8 {

	Seller::Seller(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size)
	{
		this->textHover = "Seller";
		this->textHoverPosition = vec2(pos + vec2(26, -44));
	}  

	void Seller::interact(Player& player, Game& game) {
		//total value of fishes and chests
		float totalValue = 0;

		for (const Fish& fish : player.getFishes()) {
			totalValue += fish.value;
		}

		for (const ChestObject& chest : player.getChests()) {
			totalValue += chest.value;
		}
		
		if (totalValue <= 0.f)
			return;

		player.addCoins(int(totalValue));
		player.payDebt(int(totalValue));

		game.getAudioManager().playCoinSound();

		//check for achievements based on new coins total
		game.checkAchievements(player);

		//clear inventories after selling
		player.clearFishInventory();
		player.clearChestInventory();
	}

	void Seller::setTexts(vec2 cameraOffset) {
		this->texts.clear();

		this->texts.push_back({ this->textHover, this->textHoverPosition - cameraOffset, 1, false, true});

	}

}