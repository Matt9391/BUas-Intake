#include "Enemy.h"
#include "Randomize.h"
#include "functions.h"
#include "Player.h"

namespace Tmpl8 {

	Enemy::Enemy(vec2 pos, vec2 size, vec2 endPos, float startOffset, Sprite& sprite) :
		Entity(pos, size),
		startPos(pos),
		endPos(endPos),
		enemySprite(sprite),
		speed(Randomize::randomFloat(0.09, 0.25)),
		startOffset(startOffset),
		elapsedTime(0.f),
		firstFrame(0),
		lastFrame(0),
		currentFrame(0),
		timeElapsedBF(0.f),
		timeBetweenFrames(mapValue(speed, 0.09, 0.25, 150.f, 50.f)),
		canAttack(false),
		attackCooldown(100.f),
		attackElapsedTime(0.f)
	{
		this->setAnimRange(0, 9);
	}
	
	void Enemy::update(float dt, Player& player) {
		if (this->elapsedTime < this->startOffset) {
			this->elapsedTime += dt;
			return;
		}
		
		this->attackElapsedTime += dt;

		if (this->attackElapsedTime > this->attackCooldown) {
			this->canAttack = true;
		}

		vec2 dir = this->endPos - this->pos;
		float distance = dir.length();

		if (distance <= this->speed || distance == 0.0f) {
			pos = this->endPos;
			vec2 temp = this->endPos;
			this->endPos = this->startPos;
			this->startPos = temp;

			if (this->startPos.x < this->endPos.x) {
				this->setAnimRange(0, 9);
			}
			else {
				this->setAnimRange(10, 19);
			}
		}

		dir.normalize();
		this->pos += dir * speed * dt;

		this->playAnimation(dt);
	}

	void Enemy::attack(Player& player) {
		if (this->canAttack) {
			player.stealCoins(50);
			this->canAttack = false;
			this->attackElapsedTime = 0;
		}
	}

	void Enemy::setAnimRange(int first, int last) {
		if (first != firstFrame) {
			currentFrame = first;
		}
		this->firstFrame = first;
		this->lastFrame = last;
	}

	void Enemy::playAnimation(float dt) {
		timeElapsedBF += dt;
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
		this->enemySprite.SetFrame(this->currentFrame);
		this->enemySprite.Draw(screen, int(this->pos.x - cameraOffset.x), int(this->pos.y - cameraOffset.y));
	}
	 
}
