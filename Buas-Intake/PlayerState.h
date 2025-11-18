#include "template.h"
#pragma once

namespace Tmpl8 {

	class Player;
	class Surface;
	class Sprite;

	class PlayerState
	{
	public:
		virtual ~PlayerState() {}

		virtual void enter(Player& player) = 0;

		virtual void handleInput(Player& player) = 0;

		virtual void update(Player& player) = 0;

		//virtual void draw(Player& player, Surface* screen, vec2 cameraOffset) = 0;
	};
}

