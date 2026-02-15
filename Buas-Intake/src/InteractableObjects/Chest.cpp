#include "../../tmpl8/surface.h"
#include "../../tmpl8/template.h"
#include "../Utils/Randomize.h"
#include "../Utils/functions.h"
#include "../Utils/FastNoiseLite.h"
#include "../Utils/MapHandler.h"
#include "../Gameplay/Player.h"
#include "../InteractableObjects/InteractableObject.h"
#include "../DataTypes/ChestObject.h"
#include "../game.h"

#include "Chest.h"

namespace Tmpl8 {
		
	FastNoiseLite Chest::noise;

	Chest::Chest(int type, vec2 pos, vec2 size, Sprite* chestsSprite, int frame) :
		InteractableObject(type, pos, size),
		enabled(true),
		//random values for time x and y
		timeX(Randomize::randomFloat(0.f, 1000000.f)),
		timeY(Randomize::randomFloat(0.f, 1000000.f)),
		value(0.f),
		maxPos(0),
		minPos(0),
		frame(frame)
	{
		Chest::noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
		
		this->chestsSprite = chestsSprite;

		this->maxPos = this->pos + float(MapHandler::tileSize * 2);
		this->minPos = this->pos - float(MapHandler::tileSize * 2);
		
		//maps the chest value based on its frame. Just to make it more dynamic
		this->value = mapValue(float(frame), 0.f, 3.f, 50.f, 1000.f);

		this->textHover = "Treasure Chest";
	}


	void Chest::update(float dt, Player& player) {
		if (!this->enabled) return;
		 
		this->timeX += dt * 0.05f; // x-speed
		this->timeY += dt * 0.05f; // y-speed

		float xValue = noise.GetNoise(timeX, 0.f); //from -1 to 1
		float yValue = noise.GetNoise(0.f, timeY); //from -1 to 1
		
		//maps the position based on noise values within its bounds
		this->pos.x = mapValue(xValue, -1.f, 1.f, this->minPos.x, this->maxPos.x);
		this->pos.y = mapValue(yValue, -1.f, 1.f, this->minPos.y, this->maxPos.y);

		this->textPosition = pos - vec2(16, 0);
	}


	void Chest::interact(Player& player, Game& game) {
		if (!this->enabled) return;

		//if "caught" it create a Chest Object that stores
		//the current frame and value. needed for the player's inventory
		ChestObject chestObject = { this->frame, this->value };

		player.addChest(chestObject);

		//once its caught it gets disabled
		this->enabled = false;
		this->textHover = "";
	}

	void Chest::draw(Surface* screen, vec2 cameraOffset) {
		if (!this->enabled) return;

		//since all chests share the same sprite, the frame is set each draw cycle
		(*this->chestsSprite).SetFrame(frame);
		// "- cameraOffset.x/y" to move the chest according to the camera
		(*this->chestsSprite).Draw(screen, int(this->pos.x - cameraOffset.x), int(this->pos.y - cameraOffset.y));
	}

}