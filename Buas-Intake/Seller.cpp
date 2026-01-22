#include "Seller.h"
#include "Player.h"
#include "Fish.h"
#include "ChestObject.h"
#include "Game.h"
#include <vector>


namespace Tmpl8 {

	Seller::Seller(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size)
	{
		this->textHover = "Seller";
		this->textPosition = vec2(pos + vec2(26, -44));
	} 

	void Seller::interact(Player& player) {
		float totalValue = 0;

		printf("FISHESS\n");
		for (Fish& fish : player.getFishes()) {
			printf("%d, %.2f\n", fish.rarity, fish.value);
			totalValue += fish.value;
		}
		for (ChestObject& chest : player.getChests()) {
			printf("%d, %.2f\n", chest.type, chest.value);
			totalValue += chest.value;
		}

		player.addCoins(int(totalValue));

		Game::checkAchievements(player);

		player.clearFishInventory();
		player.clearChestInventory();
	}

}