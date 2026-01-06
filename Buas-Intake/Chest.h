#include "InteractableObject.h"
#include "FastNoiseLite.h"

#pragma once

namespace Tmpl8 {

	class Chest : public InteractableObject	
	{
	public:
		Chest(int type, vec2 pos, vec2 size, Sprite* chestsSprite, int frame);

		void interact(Player& player) override;

		void update(float dt, Player& player) override;

		void draw(Surface* screen, vec2 cameraOffset);

	private:
		float mapValue(float value, float inMin, float inMax, float outMin, float outMax);

		static FastNoiseLite noise;

		bool enabled;

		float timeX;
		float timeY;
		
		float value;

		vec2 maxPos;
		vec2 minPos;

		int frame;
		Sprite* chestsSprite;


	};


}