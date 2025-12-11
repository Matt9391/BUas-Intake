#include "InteractableObject.h"

#pragma once

namespace Tmpl8 {

	class StaminaShop : public InteractableObject
	{
	public:
		StaminaShop(int type, vec2 pos, vec2 size);

		//void showText(Surface* screen, vec2 cameraOffset) override;

		void draw(Surface* screen, vec2 cameraOffset) override;
	private:
	};
}

