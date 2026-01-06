#include "Entity.h"
#pragma once

namespace Tmpl8 {


	class Enemy : public Entity
	{
	public:
		Enemy(vec2 pos, vec2 size, Sprite& sprite);
			
		void update(float dt, Player& player);

		void draw(Surface* screen, vec2 cameraOffset);


	private:
		Sprite& enemySprite;
	};


}