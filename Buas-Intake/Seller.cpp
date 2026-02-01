#include "Seller.h"
#include "Player.h"
#include "Fish.h"
#include "ChestObject.h"
#include "Game.h"
#include <cstdio>
#include "InteractableObject.h"
#include "tmpl8/template.h"


namespace Tmpl8 {

	Seller::Seller(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size)
	{
		this->textHover = "Seller";
		this->textPosition = vec2(pos + vec2(26, -44));
	}  

	void Seller::interact(Player& player) {
		//count total value of fishes and chests
		float totalValue = 0;

		printf("FISHESS\n");
		for (Fish& fish : player.getFishes()) {
			totalValue += fish.value;
		}
		for (ChestObject& chest : player.getChests()) {
			totalValue += chest.value;
		}

		player.addCoins(int(totalValue));

		//check for achievements based on new coins total
		Game::checkAchievements(player);

		//clear inventories after selling
		player.clearFishInventory();
		player.clearChestInventory();
	}

}