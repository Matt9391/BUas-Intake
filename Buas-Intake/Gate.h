#include "InteractableObject.h"

#pragma once
namespace Tmpl8 {

	class Gate : public InteractableObject
	{
	public:
		Gate(int type, vec2 pos, vec2 size);

		void interact(Player& player) override;

		//void showText(Surface* screen, vec2 cameraOffset) override;
		 
		//void draw(Surface* screen, vec2 cameraOffset) override;
	private:

	};
}

