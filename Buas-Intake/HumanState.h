#pragma once
#include "PlayerState.h"

namespace Tmpl8 {
	class Player;

	class HumanState : public PlayerState
	{
	public:
		void enter(Player& player) override;

		void handleInput(Player& player) override;
		
		void update(Player& player) override;

		//void draw(Player& player, Surface* screen, vec2 cameraOffset) override;
	private:
	};
}

