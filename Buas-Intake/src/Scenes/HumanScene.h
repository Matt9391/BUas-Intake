#include "Scene.h"
#include "../Utils/MapHandler.h"
#include <array>

#pragma once

namespace Tmpl8 {
	class Player;
	class Camera2D;
	class Surface;

	class HumanScene : public Scene
	{
	public:
		HumanScene(Game& game);

		void onEnter(Player& player, Camera2D& camera) override;
		void onExit(Player& player) override;

		void update(float dt, Camera2D& camera, Player& player) override;

		void draw(Surface* screen, Camera2D& camera, Player& player) override;
	private:
		//current active maps
		std::array<Map, 2> currentMap;
	};
	 
}

