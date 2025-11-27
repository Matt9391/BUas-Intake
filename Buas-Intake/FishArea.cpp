#include "FishArea.h"
#include "Player.h"
#include "Text.h"
#include <Windows.h>

namespace Tmpl8 {
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
		input('-'),
		lastInput('-')
	{}

	void FishArea::interact(Player& player) {
		if (player.isFishing()) {
			player.setFishing(false);
			this->enable = true;
		}else {
			player.setFishing(true);
			this->enable = true;
		}
	}

	void FishArea::moveIndx(float dt) {
		this->lastInput = this->input;
		this->input = '-';

		this->angle += 0.03;
		if (this->angle > maxAngle)
			this->angle = 0;
		
		this->xIndxPos = std::sin(angle) * this->range;

		if (GetAsyncKeyState(' '))
			input = ' ';

		if(this->lastInput != this->input) {
			float percentage = mapValue(std::abs(this->xIndxPos), 0, this->range, 1.0, 0.01);
			printf("%.2f\n", percentage);
		}

		//printf("%.2f\n", xIndxPos);
	}

	void FishArea::update(float dt) {
		if (!this->enable)
			return;

		this->moveIndx(dt);
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