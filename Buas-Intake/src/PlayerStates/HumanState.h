#pragma once
#include "PlayerState.h"

namespace Tmpl8 {
	class Player;

	//HumanState inherits from PlayerState
	class HumanState : public PlayerState
	{
	public:
		void enter(Player& player) override;

		void handleInput(Player& player) override;
	private:
	};
}

