#include "PlayerState.h"

#pragma once
namespace Tmpl8 {
	class Player;

	//FishState inherits from PlayerState
	class FishState : public PlayerState
	{
	public:
		void enter(Player& player) override;

		void handleInput(Player& player) override;

	private:
	}; 
	 
}
