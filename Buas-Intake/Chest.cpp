#include "Chest.h"
#include "Player.h"
#include "Randomize.h"
#include "functions.h"
#include "ChestObject.h"

namespace Tmpl8 {
		
	FastNoiseLite Chest::noise;

	Chest::Chest(int type, vec2 pos, vec2 size, Sprite* chestsSprite, int frame) :
		InteractableObject(type, pos, size),
		frame(frame),
		timeX(Randomize::randomFloat(0.f, 1000000.f)),
		timeY(Randomize::randomFloat(0.f, 1000000.f)),
		maxPos(0),
		minPos(0),
		value(0.f),
		enabled(true)
	{
		Chest::noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
		this->chestsSprite = chestsSprite;

		this->maxPos = this->pos + float(MapHandler::tileSize * 2);
		this->minPos = this->pos - float(MapHandler::tileSize * 2);

		this->value = mapValue(float(frame), 0.f, 3.f, 50.f, 1000.f);

		this->textHover = "Treasuer Chest";
	}


	void Chest::update(float dt, Player& player) {
		if (!this->enabled) return;
		 
		this->timeX += dt * 0.05f; // velocità orizzontale
		this->timeY += dt * 0.05f; // velocità verticale

		float xValue = noise.GetNoise(timeX, 0.f); // -1 a 1
		float yValue = noise.GetNoise(0.f, timeY); // -1 a 1
		
		this->pos.x = mapValue(xValue, -1.f, 1.f, this->minPos.x, this->maxPos.x);
		this->pos.y = mapValue(yValue, -1.f, 1.f, this->minPos.y, this->maxPos.y);

		this->textPosition = pos - vec2(16, 0);

		//printf("N: %.2f\n", offsetX);
	}


	void Chest::interact(Player& player) {
		if (!this->enabled) return;

		ChestObject chestObject = { this->frame, this->value };

		player.addChest(chestObject);

		this->enabled = false;
		this->textHover = "";
	}

	void Chest::draw(Surface* screen, vec2 cameraOffset) {
		if (!this->enabled) return;

		(*this->chestsSprite).SetFrame(frame);
		(*this->chestsSprite).Draw(screen, int(this->pos.x - cameraOffset.x), int(this->pos.y - cameraOffset.y));
	}

	


}