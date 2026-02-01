#include "Enemy.h"
#include "Randomize.h"
#include "functions.h"
#include "Player.h"
#include "Entity.h"
#include "tmpl8/surface.h"
#include "tmpl8/template.h"

namespace Tmpl8 {

	Enemy::Enemy(vec2 pos, vec2 size, vec2 endPos, float startOffset, Sprite& sprite) :
		Entity(pos, size),
		enemySprite(sprite),
		startPos(pos),
		endPos(endPos),
		//randomized to add variation
		speed(Randomize::randomFloat(0.09, 0.25)),
		startOffset(startOffset),
		elapsedTime(0.f),
		currentFrame(0),
		firstFrame(0),
		lastFrame(0),
		timeElapsedBF(0.f),
		//maps frame duration based on the speed
		timeBetweenFrames(mapValue(speed, 0.09, 0.25, 150.f, 50.f)),
		canAttack(false),
		attackCooldown(100.f),
		attackElapsedTime(0.f)
	{
		this->setAnimRange(0, 9);
	}
	
	void Enemy::update(float dt, Player& player) {
		//start after the start offset
		if (this->elapsedTime < this->startOffset) {
			this->elapsedTime += dt;
			return;
		}
		
		this->attackElapsedTime += dt;

		if (this->attackElapsedTime > this->attackCooldown) {
			this->canAttack = true;
		}

		//calculate the direction vector for movement
		vec2 dir = this->endPos - this->pos;
		float distance = dir.length();

		//check if close to the end
		if (distance <= this->speed || distance == 0.0f) {
			//set the end position
			pos = this->endPos;
			//swap the start and end position to reverse direction
			vec2 temp = this->endPos;
			this->endPos = this->startPos;
			this->startPos = temp;

			//set the animation range according to the direction
			if (this->startPos.x < this->endPos.x) {
				this->setAnimRange(0, 9);
			}
			else {
				this->setAnimRange(10, 19);
			}
		}

		dir.normalize(); //make it a unit vector
		this->pos += dir * speed * dt;

		this->playAnimation(dt);
	}

	void Enemy::attack(Player& player) {
		if (this->canAttack) {
			//steal coins from the player as an attack
			player.stealCoins(50);
			this->canAttack = false;
			this->attackElapsedTime = 0;
		}
	}

	void Enemy::setAnimRange(int first, int last) {
		//update the range if not the same range
		if (first != this->firstFrame) {
			this->currentFrame = first;
		}
		this->firstFrame = first;
		this->lastFrame = last;
	}

	void Enemy::playAnimation(float dt) {
		timeElapsedBF += dt;
		//update the current frame
		if (timeElapsedBF > timeBetweenFrames) {
			timeElapsedBF = 0;
			currentFrame++;

			if (currentFrame > lastFrame) {
				currentFrame = firstFrame;
			}

		}
	}

	void Enemy::draw(Surface* screen, vec2 cameraOffset)
	{
		//since all enemies share the same sprite, the frame is set each draw cycle
		this->enemySprite.SetFrame(this->currentFrame);
		// "- cameraOffset.x/y" to move the chest according to the camera
		this->enemySprite.Draw(screen, int(this->pos.x - cameraOffset.x), int(this->pos.y - cameraOffset.y));
	} 
	 
}
