#include "InteractableObject.h"
#pragma once

namespace Tmpl8 {

	class Seller : public InteractableObject
	{
	public:
		Seller(int type, vec2 pos, vec2 size);

		void interact(Player& player) override;
	
	private:

	};
}

