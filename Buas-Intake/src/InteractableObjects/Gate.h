#include "InteractableObject.h"

#pragma once
namespace Tmpl8 {
	class Player;
	class vec2;
	class Game;

	class Gate : public InteractableObject
	{
	public:
		Gate(int type, vec2 pos, vec2 size);

		void interact(Player& player, Game& game) override;
	private: 
	};
}

