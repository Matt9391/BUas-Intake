#include "Entity.h"
#pragma once

namespace Tmpl8 {

	//Enemy inherits from Entity
	class Enemy : public Entity
	{
	public:
		Enemy(vec2 pos, vec2 size, vec2 endPos, float startOffset, Sprite& sprite);
			
		void update(float dt, Player& player); 

		//set the animation range
		void setAnimRange(int first, int last);

		//plays the animation according to the set range
		void playAnimation(float dt);

		void attack(Player& player);

		void draw(Surface* screen, vec2 cameraOffset);

	private:
		Sprite& enemySprite;
	
		vec2 startPos;
		vec2 endPos;

		float speed;
		//time offset before starting to move
		float startOffset;
		float elapsedTime;

		int currentFrame;
		int firstFrame;
		int lastFrame;

		//time elapsed between frames
		float timeElapsedBF;
		//time required between frames, frame duration
		float timeBetweenFrames;

		bool canAttack;
		//time required between attacks
		float attackCooldown;
		//time elapsed since last attack
		float attackElapsedTime;
	};


}