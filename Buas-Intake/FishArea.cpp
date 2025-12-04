#include "FishArea.h"
#include "Player.h"
#include "Text.h"
#include <Windows.h>

namespace Tmpl8 {

	enum Rarity {
		COMMON,
		RARE,
		EPIC,
		LEGENDARY
	};

	FishArea::FishArea(int type, vec2 pos, vec2 size, std::array<Sprite*, 2> fishingSprites) :
		InteractableObject(type, pos, size),
		fishingSprites(fishingSprites),
		barPosition(pos + vec2(-16, 64)),
		indxPosition(pos + vec2(+32, 64)),
		textPosition(pos + vec2(-46, -32)),
		range(44),
		angle(0),
		maxAngle(360),
		xIndxPos(0),
		enable(false),
		elapsedTimeSpace(500),
		rebounceTime(0),
		showFishCard(false),
		elapsedTimeFishCard(0),
		fishCardMaxTime(2000),
		fishPercentage(0)
	{}

	void FishArea::interact(Player& player) {
		if (player.isFishing()) {
			player.setFishing(false);
			this->enable = false;
		}else {
			player.setFishing(true);
			this->enable = true;
		}
	}

	void FishArea::moveIndx(float dt) {
		if (this->showFishCard)
			return;

		this->elapsedTimeSpace += dt;

		this->angle += 0.03;
		if (this->angle > maxAngle)
			this->angle = 0;

		this->xIndxPos = std::sin(angle) * this->range;

		if (this->elapsedTimeSpace < this->rebounceTime) {
			return;
		}

		
		
		this->elapsedTimeSpace = 0;

		if(GetAsyncKeyState(' ') & 0x8000) {
			this->fishPercentage = mapValue(std::abs(this->xIndxPos), 0, this->range, 1.0, 0.01) * 100.f;
			this->showFishCard = true;
			printf("%.2f\% PRESSEDD\n", fishPercentage);
		}

		//printf("%.2f\n", xIndxPos);
	}

	void FishArea::fishCard(float dt) {
		this->elapsedTimeFishCard += dt;

		if (this->elapsedTimeFishCard > this->fishCardMaxTime) {
			this->showFishCard = false;
			printf("STOPPPP: %.2f\n", this->elapsedTimeFishCard);
			this->elapsedTimeFishCard = 0;
			return;
		}

		Rarity rarity = Rarity::COMMON;

		if(this->fishPercentage < 50)
			rarity = Rarity::COMMON;
		else if(this->fishPercentage >= 50 && this->fishPercentage < 75)
			rarity = Rarity::RARE;
		else if(this->fishPercentage >= 75 && this->fishPercentage < 90)
			rarity = Rarity::EPIC;
		else if(this->fishPercentage >= 90)
			rarity = Rarity::LEGENDARY;

		printf("%d\n", rarity);
	}

	void FishArea::update(float dt) {
		if (!this->enable)
			return;

		this->moveIndx(dt);

		if (this->showFishCard) {
			this->fishCard(dt);
		}
	}

	void FishArea::showText(Surface* screen, vec2 cameraOffset) {
		Text::drawString("press 'F' to enter start fishing", screen, (this->textPosition - cameraOffset));
	
	}

	void FishArea::draw(Surface* screen, vec2 cameraOffset) {
		//this->drawHitBox(screen, cameraOffset);
		if (!this->enable)
			return;

		(*this->fishingSprites[0]).Draw(screen, this->barPosition.x - cameraOffset.x, this->barPosition.y - cameraOffset.y);
		(*this->fishingSprites[1]).Draw(screen, this->indxPosition.x - cameraOffset.x + this->xIndxPos, this->indxPosition.y - cameraOffset.y);
	}

	float mapValue(float x, float inMin, float inMax, float outMin, float outMax)
	{
		return (x - inMin) / (inMax - inMin) * (outMax - outMin) + outMin;
	}

	float constrain(float value, float min, float max) {
		if (value < min)
			return min;
		if (value > max)
			return max;
		return value;
	}
}