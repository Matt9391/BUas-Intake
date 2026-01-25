#include "FishArea.h"
#include "Player.h"
#include "Text.h"
#include <Windows.h>
#include "Fish.h"
#include "functions.h"

namespace Tmpl8 {

	

	FishArea::FishArea(int type, vec2 pos, vec2 size, std::array<Sprite*, 3> fishingSprites) :
		InteractableObject(type, pos, size),
		fishingSprites(fishingSprites),
		barPosition(pos + vec2(-16, 72)),
		indxPosition(pos + vec2(+31, 72)),
		cardPosition(pos + vec2(16, 32)),
		textCardPosition(pos + vec2(-46, 96)),
		range(45),
		angle(0),
		maxAngle(2.f * 3.14),
		xIndxPos(0),
		enable(false),
		elapsedTimeSpace(500),
		rebounceTime(0),
		showFishCard(false),
		elapsedTimeFishCard(0),
		fishCardMaxTime(2000)
	{
		textPosition = vec2(pos + vec2(-46, -32));
		textHover = "press 'F' to start fishing";
	}

	void FishArea::interact(Player& player) {
		if (player.isFishing()) {
			player.setFishing(false);
			this->enable = false;
			this->showFishCard = false;
			this->textHover = "press 'F' to start fishing";
		}else {
			player.setFishing(true);
			this->enable = true;
			this->textHover = "press 'F' to stop fishing";
		}
	}

	void FishArea::fish(float dt, Player& player) {
		if (this->showFishCard)
			return;

		this->elapsedTimeSpace += dt; //spacebar pressed
		 
		this->angle += 0.0035f * dt; 
		//this->angle = 3.14 / -2.f;
		if (this->angle > maxAngle)
			this->angle = 0;

		this->xIndxPos = std::sin(angle) * this->range;

		if (this->elapsedTimeSpace < this->rebounceTime) {
			return;
		}
		
		this->elapsedTimeSpace = 0;

		if(GetAsyncKeyState(' ') & 0x8000) {
			float fishPercentage = mapValue(std::abs(this->xIndxPos), 0, this->range, 1.0, 0.01) * 100.f;
			this->showFishCard = true;
			printf("%.2f PRESSEDD\n", fishPercentage);
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

			(*this->fishingSprites[2]).SetFrame(rarity);

			//printf("%d e %d\n", rarity, fish.rarity);
			player.addFish(fish);
			this->angle = -3.14 / 2.f;
		}

		//printf("%.2f\n", xIndxPos);
	}


	void FishArea::update(float dt, Player& player) {
		if (!this->enable)
			return;

		this->fish(dt, player);


		if (this->showFishCard) {
			this->elapsedTimeFishCard += dt;

			if (this->elapsedTimeFishCard > this->fishCardMaxTime) {
				this->showFishCard = false;
				printf("STOPPPP: %.2f\n", this->elapsedTimeFishCard);
				this->elapsedTimeFishCard = 0;
			}
		}
	}

	void FishArea::showText(Surface* screen, vec2 cameraOffset) {
		Text::drawString(this->textHover, screen, (this->textPosition - cameraOffset));
	}

	void FishArea::draw(Surface* screen, vec2 cameraOffset) {
		//this->drawHitBox(screen, cameraOffset);
		if (!this->enable)
			return;

		(*this->fishingSprites[0]).Draw(screen, int(this->barPosition.x - cameraOffset.x), int(this->barPosition.y - cameraOffset.y));
		(*this->fishingSprites[1]).Draw(screen, int(this->indxPosition.x - cameraOffset.x + this->xIndxPos), int(this->indxPosition.y - cameraOffset.y));

		if (!this->showFishCard)
			return;

		(*this->fishingSprites[2]).Draw(screen, int(this->cardPosition.x - cameraOffset.x), int(this->cardPosition.y - cameraOffset.y));
		Text::drawString(this->cardText, screen, textCardPosition - cameraOffset);
	}	
}