#include "FishArea.h"
#include "Player.h"
#include "Text.h"
#include <Windows.h>
#include "Fish.h"

namespace Tmpl8 {

	

	FishArea::FishArea(int type, vec2 pos, vec2 size, std::array<Sprite*, 3> fishingSprites) :
		InteractableObject(type, pos, size),
		fishingSprites(fishingSprites),
		barPosition(pos + vec2(-16, 64)),
		indxPosition(pos + vec2(+31, 64)),
		cardPosition(pos + vec2(16, 24)),
		textCardPosition(pos + vec2(-46, 88)),
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

		this->elapsedTimeSpace += dt;

		this->angle += 0.0035 * dt;
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
			Rarity rarity = Rarity::COMMON;

			if (fishPercentage < 50) {
				rarity = Rarity::COMMON;
				this->cardText = "A common fish! + 10 Coins";
				player.addCoins(10);
			}
			else if (fishPercentage >= 50 && fishPercentage < 75) {
				rarity = Rarity::RARE;
				this->cardText = "A rare fish! + 20 Coins";
				player.addCoins(20);
			}
			else if (fishPercentage >= 75 && fishPercentage < 90) {
				rarity = Rarity::EPIC;
				this->cardText = "A epic fish! + 50 Coins";
				player.addCoins(50);
			}
			else if (fishPercentage >= 90) {
				rarity = Rarity::LEGENDARY;
				this->cardText = "A legendary fish! + 150 Coins";
				player.addCoins(150);

			}

			Fish fish = { rarity, 100.f};

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