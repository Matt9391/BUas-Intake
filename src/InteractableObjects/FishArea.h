#pragma once

#include <InteractableObjects/InteractableObject.h>

#include <array>
#include <string>


namespace Tmpl8 {
	class Game;
	class vec2;
	class Sprite;
	class Player;
	class Surface;

	//FishArea inherits from InteractableObject
	class FishArea : public InteractableObject
	{
	public:
		FishArea(int type, vec2 pos, vec2 size, std::array<Sprite*, 3> fishingSprites);
		 
		void update(float dt, Player& player) override; 
		void interact(Player& player,Game& game) override;

		void setTexts(vec2 cameraOffset) override;

		void draw(Surface* screen, vec2 cameraOffset) override;

	private:
		//handle player fishing
		void fish(float dt, Player& player);
		
		//fish area enabled or disabled
		bool enable;
		
		bool showFishCard;

		//slider position
		vec2 barPosition;
		//origin of the slider index position
		vec2 indxPosition;

		vec2 cardPosition;
		vec2 textCardPosition;
		std::string cardText;

		float indxSpeed;
		//current slider index position
		float xIndxPos;
		//range of motion (x-coordinate) of the index
		float range;
		
		//current angle used to calculate the index position
		float angle;
		//max angle at which the current angle is reset
		float maxAngle;
		
		float elapsedTimeFishCard; 
		float fishCardMaxTime; 

 		//elapsed time since last space press
		float elapsedTimeSpace;
		//minimum time required before pressing again
		float rebounceTime; 

		std::array<Sprite*, 3> fishingSprites;
	};

}
