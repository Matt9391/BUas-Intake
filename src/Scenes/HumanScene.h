#include <array>
#include "../Utils/MapHandler.h"
#include "Scene.h"
#include <string>


#pragma once

namespace Tmpl8 {
	class Player;
	class Camera2D;
	class Surface;
	class HUD;
	class Game;

	class HumanScene : public Scene
	{
	public:
		HumanScene(Game& game, std::string mapName, Surface& tileset, std::string voidChar);
		void onEnter(Player& player, Camera2D& camera, HUD& hud) override;
		void onExit(Player& player) override;

		void update(float dt, Camera2D& camera, Player& player, HUD& hud) override;

		void draw(Surface* screen, Camera2D& camera, Player& player, HUD& hud) override;
	private:
		//current active maps
		std::array<Map, 2> currentMap;
	};
	 
}

