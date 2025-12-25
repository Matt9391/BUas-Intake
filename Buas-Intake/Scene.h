#include "surface.h"


#pragma once

namespace Tmpl8 {
	class Player;

	class Scene
	{
	public:
		virtual ~Scene() = 0;

		virtual void onEnter() = 0;
		virtual void onExit() = 0;

		virtual void update(float dt, Player& player) = 0;

		virtual void draw(Surface* screen) = 0;

	private:
	};

}
