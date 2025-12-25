#include "Scene.h"
#include "MapHandler.h"

#include <array>

#pragma once

namespace Tmpl8 {

	class HumanScene : public Scene
	{
	public:
		void onEnter() override;
		void onExit() override;

		void update(float dt, Player& player) override;

		void draw(Surface* screen) override;
	private:
		std::array<Map, 2> currentMap;
	};

}

