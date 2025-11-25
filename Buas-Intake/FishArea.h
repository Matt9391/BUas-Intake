#include "InteractableObject.h"
#pragma once

namespace Tmpl8 {

	class FishArea : InteractableObject
	{
	public:
		FishArea(int type, vec2 pos, vec2 size, Sprite& barSprite);
		
		void draw(Surface* screen, vec2 cameraOffset);

	private:

		vec2 barPosition;
		Sprite& barSprite;

	};

}
