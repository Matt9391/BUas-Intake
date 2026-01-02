#include "Chest.h"
#include "Player.h"
#include "Randomize.h"

namespace Tmpl8 {
		
	FastNoiseLite Chest::noise;

	Chest::Chest(int type, vec2 pos, vec2 size, Sprite* chestsSprite, int frame) :
		InteractableObject(type, pos, size),
		frame(frame),
		basePos(pos)
	{
		Chest::noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
		this->chestsSprite = chestsSprite;
	}


	void Chest::update(float dt, Player& player) {
		static float timeX = 0.f;
		static float timeY = 0.f;

		timeX += dt * 0.5f; // velocità orizzontale
		timeY += dt * 0.3f; // velocità verticale

		float offsetX = noise.GetNoise(timeX, 0.f) * 1.f; // -1 a 1
		float offsetY = noise.GetNoise(0.f, timeY) * 1.f;

		pos.x = basePos.x + offsetX;
		pos.y = basePos.y + offsetY;
	}


	void Chest::interact(Player& player) {
		printf("SONO UNA CHESTTT");
		player.addCoins(100000);
	}

	void Chest::draw(Surface* screen, vec2 cameraOffset) {
		(*this->chestsSprite).SetFrame(frame);
		(*this->chestsSprite).Draw(screen, int(this->pos.x - cameraOffset.x), int(this->pos.y - cameraOffset.y));
	}


}