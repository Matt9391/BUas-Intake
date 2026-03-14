#pragma once
#include <Scenes/Scene.h>
#include <Utils/MapHandler.h>

#include <array>
#include <memory>
#include <vector>

namespace Tmpl8 {
	class Enemy;
	class Player;
	class vec2;
	class Camera2D;
	class Surface;
	class Game;
	class HUD;
	//FishScene inherits from Scene
	class FishScene : public Scene
	{
	public:
		FishScene(Game& game, std::string mapName, Surface& tileset, std::string voidChar);

		void onEnter(Player& player, Camera2D& camera, HUD& hud) override;
		void onExit(Player& player) override; 
 
		void update(float dt, Camera2D& camera, Player& player, HUD& hud) override;

		void draw(Surface* screen, Camera2D& camera, Player& player, HUD& hud) override;
	private:
		//current active maps
		std::array<Map, 2> currentMap;
		//vector of pointers to enemies 
		std::vector<std::unique_ptr<Enemy>> enemies;
	};

}


