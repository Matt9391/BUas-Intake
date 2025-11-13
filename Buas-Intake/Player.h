#include "template.h"
#include "surface.h"
#include <array>
#include "MapHandler.h"
#pragma once

namespace Tmpl8 {

	class Player
	{
	public:

		Player(Sprite& humanSprite, std::array<Map, 2>* currentMap);

		void update(float dt);
		
		void move(float dt);
		
		void handleInput();

		void draw(Surface* screen, vec2 cameraOffset);

		vec2 getPos();

	private:
		vec2 pos;
		vec2 nextPos;
		vec2 size;

		float speed;

		vec2 dir;
		Sprite &humanSprite;

		std::array<Map, 2> *currentMap;
		//Sprite &fishSprite;

	};

}
