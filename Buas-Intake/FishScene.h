#include "Scene.h"
#include "MapHandler.h"
#include <array>

#pragma once

namespace Tmpl8 {
	class Enemy;

	//FishScene inherits from Scene
	class FishScene : public Scene
	{
	public:
		void onEnter(Player& player, Camera2D& camera) override;
		void onExit(Player& player) override; 
 
		void update(float dt, Camera2D& camera, Player& player) override;

		void draw(Surface* screen, Camera2D& camera, Player& player) override;
	private:
		//current active maps
		std::array<Map, 2> currentMap;
		//vector of pointers to enemies 
		std::vector<Enemy*> enemies;
	};

}


