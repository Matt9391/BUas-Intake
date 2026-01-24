#include "InteractableObject.h"
#include <array>
#include <string>

#pragma once

namespace Tmpl8 {

	class FishArea : public InteractableObject
	{
	public:
		FishArea(int type, vec2 pos, vec2 size, std::array<Sprite*, 3> fishingSprites);
		 
		void update(float dt, Player& player) override; 
		void interact(Player& player) override;

		void showText(Surface* screen, vec2 cameraOffset) override;

		void draw(Surface* screen, vec2 cameraOffset) override;

	private:
		void fish(float dt, Player& player);
		bool enable;
		bool showFishCard;

		vec2 barPosition;
		vec2 indxPosition;
		vec2 cardPosition;
		vec2 textCardPosition;
		
		std::string cardText;

		float xIndxPos;
		
		float angle;
		float maxAngle;

		float range;
		
		float elapsedTimeFishCard; //time passed of showing fishCard
		float fishCardMaxTime; //time needed to pass

		float elapsedTimeSpace; //time passed since you last pressed space
		float rebounceTime; // time needed to pass

		std::array<Sprite*, 3> fishingSprites;
	};

}
