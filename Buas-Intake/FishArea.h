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

		void draw(Surface* screen, vec2 cameraOffset) override;

	private:
		void moveIndx(float dt);
		bool enable;

		vec2 barPosition;
		vec2 indxPosition;
		vec2 textPosition;
		
		float xIndxPos;

		bool display;
		
		float angle;
		float maxAngle;

		float range;

		char lastInput;
		char input;

		std::array<Sprite*, 2> fishingSprites;
	};

	float mapValue(float x, float inMin, float inMax, float outMin, float outMax);
	float constrain(float value, float min, float max);
}
