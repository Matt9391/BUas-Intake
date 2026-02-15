
#pragma once

namespace Tmpl8 {

	class Player;
	class Surface;
	class Sprite;

	//base class for player states
	class PlayerState
	{
	public:
		virtual ~PlayerState() {}
		 
		virtual void enter(Player& player) = 0;

		virtual void handleInput(Player& player) = 0;

		float getSprintSpeed();
	protected:
		float sprintSpeed;
	};
}

