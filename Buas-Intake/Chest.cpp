#include "Chest.h"
#include "Player.h"

namespace Tmpl8 {

	Chest::Chest(int type, vec2 pos, vec2 size, Sprite* chestsSprite) :
		InteractableObject(type, pos, size)
	{
		this->chestsSprite = chestsSprite;
		int frame = rand() % 4;
		(this->chestsSprite)->SetFrame(frame);
	}

	void Chest::interact(Player& player) {
		printf("SONO UNA CHESTTT");
		player.addCoins(100000);
	}

	void Chest::draw(Surface* screen, vec2 cameraOffset) {
		(*this->chestsSprite).Draw(screen, int(this->pos.x - cameraOffset.x), int(this->pos.y - cameraOffset.y));
	}


}