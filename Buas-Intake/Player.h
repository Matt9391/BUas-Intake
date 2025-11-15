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

		void setAnimRange(int first, int last);

		void playAnimation(float dt);

		int firstFrame;
		int lastFrame;
		int currentFrame;	
		float timeBetweenFrames;
		float timeElapsedBF;

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
