#include "InteractableObject.h"
#pragma once

namespace Tmpl8 {

	class FishArea : public InteractableObject
	{
	public:
		FishArea(int type, vec2 pos, vec2 size, Sprite& barSprite);
		
		void interact(Player& player) override;

		void showText(Surface* screen, vec2 cameraOffset) override;

		void draw(Surface* screen, vec2 cameraOffset) override;

	private:

		vec2 barPosition;
		Sprite& barSprite;

	};

}
