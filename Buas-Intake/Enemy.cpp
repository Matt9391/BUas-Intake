#include "Enemy.h"

namespace Tmpl8 {

	Enemy::Enemy(vec2 pos, vec2 size, Sprite& sprite) :
		Entity(pos, size),
		enemySprite(sprite)
	{}
	
	void Enemy::update(float dt, Player& player) {

	}

	void Enemy::draw(Surface* screen, vec2 cameraOffset)
	{
		this->enemySprite.Draw(screen, this->pos.x - cameraOffset.x, this->pos.y - cameraOffset.y);
	}

}
