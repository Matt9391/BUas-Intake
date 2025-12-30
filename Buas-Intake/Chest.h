#include "InteractableObject.h"
#pragma once

namespace Tmpl8 {

	class Chest : public InteractableObject	
	{
	public:
		Chest(int type, vec2 pos, vec2 size, Sprite* chestsSprite);

		void interact(Player& player) override;

		void draw(Surface* screen, vec2 cameraOffset);

	private:

		Sprite* chestsSprite;
	};


}