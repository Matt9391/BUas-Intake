#include "InteractableObject.h"
#include "FastNoiseLite.h" //Noise library (not mine)

#pragma once

namespace Tmpl8 {

	//Chest inherits from InteractableObject
	class Chest : public InteractableObject	
	{
	public:
		Chest(int type, vec2 pos, vec2 size, Sprite* chestsSprite, int frame);

		void interact(Player& player) override; 

		void update(float dt, Player& player) override;

		void draw(Surface* screen, vec2 cameraOffset);

	private:

		//static variable to avoid re-initializing for each chest
		static FastNoiseLite noise;

		//enable or disable the chest.
		//Since the number of chests is limited, I prefer to disable them when caught
		//instead of removing them from the vector storing them. It's not entirely correct,
		//but it avoids pointer/address issues and an extra loop. 
		//I wouldn't do this for something like bullets.
		bool enabled;
		
		//noise time for x and y axes
		float timeX;
		float timeY;
		
		//chest coin value
		float value;

		//area in which the chest can move 
		vec2 maxPos;
		vec2 minPos;

		//sprite frame of the chest
		int frame;

		Sprite* chestsSprite;


	};


}