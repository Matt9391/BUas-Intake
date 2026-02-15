#include <array>
#include <string>
#include "InteractableObject.h"

#pragma once

namespace Tmpl8 {
	class Game;
	class vec2;
	class Sprite;
	class Player;

	//FishArea inherits from InteractableObject
	class FishArea : public InteractableObject
	{
	public:
		FishArea(int type, vec2 pos, vec2 size, std::array<Sprite*, 3> fishingSprites);
		 
		void update(float dt, Player& player) override; 
		void interact(Player& player,Game& game) override;

		void showText(Surface* screen, vec2 cameraOffset) override;

		void draw(Surface* screen, vec2 cameraOffset) override;

	private:
		//handle player fishing
		void fish(float dt, Player& player);
		//fish area enabled or disabled
		bool enable;
		//variable to show or hide the caught fish
		bool showFishCard;

		//slider position
		vec2 barPosition;
		//origin of the slider index position
		vec2 indxPosition;
		//position of the caught fish card
		vec2 cardPosition;
		//position of card text
		vec2 textCardPosition;
		//text that display the fish type
		std::string cardText;

		//current slider index position
		float xIndxPos;
		//range of motion (x-coordinate) of the index
		float range;
		
		//current angle used to calculate the index position
		float angle;
		//max angle at which the current angle is reset
		float maxAngle;
		
		//elapsed time while the card is enabled
		float elapsedTimeFishCard; 
		//max time the card can stay enabled
		float fishCardMaxTime; 

 		//elapsed time since last space press
		float elapsedTimeSpace;
		//minimum time required before pressing again
		float rebounceTime; 

		std::array<Sprite*, 3> fishingSprites;
	};

}
