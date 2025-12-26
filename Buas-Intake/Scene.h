#include "surface.h"


#pragma once

namespace Tmpl8 {
	class Player;
	class Camera2D;

	class Scene
	{
	public:
		virtual ~Scene() = default;

		virtual void onEnter(Player& player, Camera2D& camera) = 0;
		virtual void onExit() = 0;

		virtual void update(float dt, Camera2D& camera, Player& player) = 0;

		virtual void draw(Surface* screen, Camera2D& camera, Player& player) = 0;

	private:
	};

}
