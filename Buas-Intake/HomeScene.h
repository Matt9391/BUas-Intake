#include "Scene.h"
#include <string>
#include "template.h"
#pragma once

namespace Tmpl8 {

	class HomeScene : public Scene
	{
	public:
		void onEnter(Player& player, Camera2D& camera) override;
		void onExit() override;

		void update(float dt, Camera2D& camera, Player& player) override;

		void draw(Surface* screen, Camera2D& camera, Player& player) override;
	private:
		std::string playText;
		vec2 playTextPosition;
		 
	};

};


