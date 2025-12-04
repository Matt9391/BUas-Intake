#include "InteractableObject.h"
#include <array>

#pragma once

namespace Tmpl8 {

	class FishArea : public InteractableObject
	{
	public:
		FishArea(int type, vec2 pos, vec2 size, std::array<Sprite*, 2> fishingSprites);
		
		void update(float dt) override;
		void interact(Player& player) override;

		void showText(Surface* screen, vec2 cameraOffset) override;

		void fishCard(float dt);

		void draw(Surface* screen, vec2 cameraOffset) override;

	private:
		void moveIndx(float dt);
		bool enable;
		bool showFishCard;

		vec2 barPosition;
		vec2 indxPosition;
		vec2 textPosition;
		
		float xIndxPos;
		
		float angle;
		float maxAngle;

		float range;
		
		float elapsedTimeFishCard; //time passed of showing fishCard
		float fishCardMaxTime; //time needed to pass
		float fishPercentage; 

		float elapsedTimeSpace; //time passed since you last pressed space
		float rebounceTime; // time needed to pass

		std::array<Sprite*, 2> fishingSprites;
	};

	float mapValue(float x, float inMin, float inMax, float outMin, float outMax);
	float constrain(float value, float min, float max);
}
