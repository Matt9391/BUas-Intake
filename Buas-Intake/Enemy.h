#include "Entity.h"
#pragma once

namespace Tmpl8 {


	class Enemy : public Entity
	{
	public:
		Enemy(vec2 pos, vec2 size, vec2 endPos, float startOffset, Sprite& sprite);
			
		void update(float dt, Player& player);

		void setAnimRange(int first, int last);
		void playAnimation(float dt);

		void attack(Player& player);

		void draw(Surface* screen, vec2 cameraOffset);


	private:
		Sprite& enemySprite;
		vec2 startPos;
		vec2 endPos;

		float speed;
		float startOffset;
		float elapsedTime;

		int currentFrame;
		int firstFrame;
		int lastFrame;

		float timeElapsedBF;
		float timeBetweenFrames;

		bool canAttack;
		float attackCooldown;
		float attackElapsedTime;
	};


}