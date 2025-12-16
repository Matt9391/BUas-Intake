#include "Seller.h"
#include "Player.h"
#include "Fish.h"
#include <vector>

namespace Tmpl8 {

	Seller::Seller(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size)
	{
		this->textHover = "Seller";
		this->textPosition = vec2(pos + vec2(10, -48));
	}

	void Seller::interact(Player& player) {
		std::vector<Fish> fishes = player.getFishes();
		float sumValues = 0;

		printf("FISHESS\n");
		for (Fish& fish : fishes) {
			printf("%d, %.2f\n", fish.rarity, fish.value);
			sumValues += fish.value;
		}

		player.addCoins(sumValues);

		player.clearFishes();
	}

}