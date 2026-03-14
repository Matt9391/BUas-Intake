#include <DataTypes/Fish.h>
#include <Gameplay/Player.h>
#include <InteractableObjects/InteractableObject.h>
#include <Utils/Text.h>
#include <Utils/functions.h>

#include "FishArea.h"

#include <game.h>
#include <surface.h>
#include <template.h>

#include <array>
#include <cmath>
#include <cstdlib>
#include <Windows.h>

namespace Tmpl8 {	

	FishArea::FishArea(int type, vec2 pos, vec2 size, std::array<Sprite*, 3> fishingSprites) :
		InteractableObject(type, pos, size),
		enable(false),
		showFishCard(false),
		barPosition(pos + vec2(-16, 72)),
		indxPosition(pos + vec2(+31, 72)),
		cardPosition(pos + vec2(16, 32)),
		textCardPosition(pos + vec2(-40, 96)),
		cardText("press 'Space' to fish"),
		indxSpeed(0.0035f),
		xIndxPos(0),
		range(45),
		angle(0),
		maxAngle(2.f * 3.14),
		elapsedTimeFishCard(0),
		fishCardMaxTime(2000),
		elapsedTimeSpace(500),
		rebounceTime(0),
		fishingSprites(fishingSprites)
	{
		textHoverPosition = vec2(pos + vec2(-46, -32));
		textHover = "press 'F' to start fishing";
	}

	void FishArea::interact(Player& player, Game& game) {
		//handle player interaction within the fishing area
		//check if the player is currently fishing
		if (player.isFishing()) {
			//disable fishing state and fishing area
			player.setFishing(false);
			this->enable = false;
			this->showFishCard = false;
			this->textHover = "press 'F' to start fishing";
			this->cardText = "press 'Space' to fish";
			this->textCardPosition = this->pos + vec2(-40, 96);
		}else {
			//otherwise enable all
			player.setFishing(true);
			this->enable = true;
			this->textHover = "press 'F' to stop fishing";
		}
	}

	void FishArea::fish(float dt, Player& player) {
		//skip if fishing is on cooldown
		if (this->showFishCard)
			return;

		this->elapsedTimeSpace += dt;
		
		this->angle += indxSpeed * dt;

		//reset angle after a full rotation
		if (this->angle > maxAngle)
			this->angle = 0;

		this->xIndxPos = std::sin(angle) * this->range;

		//check if player can fish
		if (this->elapsedTimeSpace < this->rebounceTime) {
			return;
		}
		
		//check if the player has pressed space
		if(GetAsyncKeyState(' ') & 0x8000) {
			this->elapsedTimeSpace = 0;
			
			//calculate the percentage based on abs(index position):
			//closer to 0 -> higher %, further -> lower %
			float fishPercentage = mapValue(std::abs(this->xIndxPos), 0, this->range, 1.0, 0.01) * 100.f;

			this->showFishCard = true;
			
			//default values
			FishRarity rarity = FishRarity::COMMON;
			float value = 0;

			if (fishPercentage < 50) {
				rarity = FishRarity::COMMON;
				this->cardText = "A common fish!";
				this->textCardPosition = this->pos + vec2(-16, 96);
				value = 80;
			}
			else if (fishPercentage >= 50 && fishPercentage < 75) {
				rarity = FishRarity::RARE;
				this->cardText = "A rare fish!";
				value = 150;
				this->textCardPosition = this->pos + vec2(-8, 96);
			}
			else if (fishPercentage >= 75 && fishPercentage < 90) {
				rarity = FishRarity::EPIC;
				this->cardText = "A epic fish!";
				this->textCardPosition = this->pos + vec2(-8, 96);
				value = 300;
			}
			else if (fishPercentage >= 90) {
				rarity = FishRarity::LEGENDARY;
				this->cardText = "A legendary fish!";
				this->textCardPosition = this->pos + vec2(-24, 96);
				value = 500;
			}

			Fish fish = { rarity, value};

			player.addFish(fish);

			//set fish sprite frame based on rarity
			(*this->fishingSprites[2]).SetFrame(rarity);

			//reset the angle to set the index postion on the left
			this->angle = -3.14 / 2.f;
		}

	}


	void FishArea::update(float dt, Player& player) {
		//check whether the fish area is enabled
		if (!this->enable)
			return;

		this->fish(dt, player);

		//check whether the fishCard is enabled
		if (this->showFishCard) {
			this->elapsedTimeFishCard += dt;

			if (this->elapsedTimeFishCard > this->fishCardMaxTime) {
				//disable the fishCard after fixed time
				this->showFishCard = false;
				this->elapsedTimeFishCard = 0;
				this->cardText = "press 'Space' to fish";
				this->textCardPosition = this->pos + vec2(-40, 96);
			}
		}
	}

	void FishArea::setTexts(vec2 cameraOffset) {
		this->texts.clear();

		this->texts.push_back({ this->textHover, textHoverPosition - cameraOffset, 1, false});
		if (!this->enable)
			return;

		this->texts.push_back({ this->cardText, textCardPosition - cameraOffset, 1, false});
	}

	void FishArea::draw(Surface* screen, vec2 cameraOffset) {
		if (!this->enable)
			return;
		// "- cameraOffset.x/y" to keep the sprites fixed according to the camera
		(*this->fishingSprites[0]).Draw(screen, int(this->barPosition.x - cameraOffset.x), int(this->barPosition.y - cameraOffset.y));
		(*this->fishingSprites[1]).Draw(screen, int(this->indxPosition.x - cameraOffset.x + this->xIndxPos), int(this->indxPosition.y - cameraOffset.y));

		if (!this->showFishCard)
			return;

		(*this->fishingSprites[2]).Draw(screen, int(this->cardPosition.x - cameraOffset.x), int(this->cardPosition.y - cameraOffset.y));
	}
}