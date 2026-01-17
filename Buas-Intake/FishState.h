#include "PlayerState.h"

#pragma once
namespace Tmpl8 {
	class Player;

	class FishState : public PlayerState
	{
	public:
		void enter(Player& player) override;

		void handleInput(Player& player) override;

		void update(Player& player) override;
	private:
	};
	 
}
