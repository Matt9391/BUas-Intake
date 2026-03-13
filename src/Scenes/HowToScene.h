#include <string>
#include "../../tmpl8/template.h"
#include "Scene.h"
#include "../GFX/Button.h"
#include <memory>
#include "../GFX/ButtonSceneChanger.h"

#pragma once

namespace Tmpl8 {
	class Player;
	class vec2;
	class Camera2D;
	class Surface;
	class Game;
	class HUD;

	class HowToScene : public Scene
	{
	public:

		HowToScene(Game& game, std::string mapName, Surface& tileset, std::string voidChar);

		void onEnter(Player& player, Camera2D& camera, HUD& hud) override;
		void onExit(Player& player) override;

		void update(float dt, Camera2D& camera, Player& player, HUD& hud) override;

		void draw(Surface* screen, Camera2D& camera, Player& player, HUD& hud) override;
	private:

	};

};


