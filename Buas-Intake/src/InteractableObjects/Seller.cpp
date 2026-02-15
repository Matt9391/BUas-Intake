#include <cstdio>
#include "../../tmpl8/template.h"
#include "../Gameplay/Player.h"
#include "InteractableObject.h"
#include "../DataTypes/Fish.h"
#include "../DataTypes/ChestObject.h"
#include "../game.h"

#include "Seller.h"

namespace Tmpl8 {

	Seller::Seller(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size)
	{
		this->textHover = "Seller";
		this->textPosition = vec2(pos + vec2(26, -44));
	}  

	void Seller::interact(Player& player, Game& game) {
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
		player.payDebt(int(totalValue));

		//check for achievements based on new coins total
		game.checkAchievements(player);

		//clear inventories after selling
		player.clearFishInventory();
		player.clearChestInventory();
	}

}