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
		static FastNoiseLite noise;

		vec2 basePos;

		int frame;
		Sprite* chestsSprite;
	};


}