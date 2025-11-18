#include "template.h"
#include "surface.h"
#include <array>
#include "MapHandler.h"
#include "PlayerState.h"
#include "PlayerVisual.h"
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
		vec2 getDir();
		vec2 getSize();


		void setPos(const vec2& pos);
		void setDir(const vec2& dir);
		void setState(int state);

		void setAnimRange(int first, int last);

	private:


		void playAnimation(float dt);

		int firstFrame;
		int lastFrame;
		int currentFrame;	
		float timeBetweenFrames;
		float timeElapsedBF;

		vec2 pos;
		vec2 nextPos;
		vec2 size;
		vec2 velocity;

		float speed;

		vec2 dir;
		Sprite &humanSprite;

		PlayerState* state;
		PlayerVisual visual;

		std::array<Map, 2> *currentMap;
		//Sprite &fishSprite;

	};

}
