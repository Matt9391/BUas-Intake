#include <string>
#include "../../tmpl8/template.h"
#include "Scene.h"

#pragma once

namespace Tmpl8 {
	class Player;
	class vec2;
	class Camera2D;
	class Surface;
	class Game;
	class HUD;

	class HomeScene : public Scene
	{
	public:

		HomeScene(Game& game);

		void onEnter(Player& player, Camera2D& camera) override;
		void onExit(Player& player) override;

		void update(float dt, Camera2D& camera, Player& player, HUD& hud) override;

		void draw(Surface* screen, Camera2D& camera, Player& player, HUD& hud) override;
	private:

		std::string playText;
		vec2 playTextPosition;
		
		std::string howToPlayText;
		vec2 howToPlayTextPosition;
		
		std::string UIText;
		vec2 UITextPosition;
		
		std::string whatIsText;
		vec2 whatIsTextPosition;
		
		std::string resetText;
		vec2 resetTextPosition;
		
		vec2 gameTitlePos;
	};

};


