#include <array>
#include <vector>
#include <memory>
#include "../Utils/MapHandler.h"
#include "Scene.h"

#pragma once

namespace Tmpl8 {
	class Enemy;
	class Player;
	class vec2;
	class Camera2D;
	class Surface;
	class Game;

	//FishScene inherits from Scene
	class FishScene : public Scene
	{
	public:
		FishScene(Game& game);

		void onEnter(Player& player, Camera2D& camera) override;
		void onExit(Player& player) override; 
 
		void update(float dt, Camera2D& camera, Player& player) override;

		void draw(Surface* screen, Camera2D& camera, Player& player) override;
	private:
		//current active maps
		std::array<Map, 2> currentMap;
		//vector of pointers to enemies 
		std::vector<std::unique_ptr<Enemy>> enemies;
	};

}


