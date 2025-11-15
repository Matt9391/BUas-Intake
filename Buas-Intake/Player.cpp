#include "Player.h"
#include <Windows.h>

namespace Tmpl8 {
	Player::Player(Sprite& humanSprite, std::array<Map, 2>* currentMap) :
		humanSprite(humanSprite),
		currentMap(currentMap),
		pos({ScreenWidth / 2, ScreenHeight/2}),
		size({32, 32}),
		speed(0.1),
		firstFrame(0),
		lastFrame(1),
		currentFrame(0),
		timeBetweenFrames(70),
		timeElapsedBF(0)
	{
		humanSprite.SetFrame(38);
	}

	void Player::update(float dt) {
		this->handleInput();
		this->move(dt);
		this->playAnimation(dt);
	}

	void Player::handleInput() {
		this->dir = { 0,0 };
		
		if (GetAsyncKeyState('A')) {
			this->dir.x = -1;
			this->setAnimRange(8, 15);
		}
		if (GetAsyncKeyState('D')) {
			this->dir.x = 1;
			this->setAnimRange(0, 7);
		}
		if (GetAsyncKeyState('W')) {
			this->dir.y = -1;
			this->setAnimRange(24, 31);
		}
		if (GetAsyncKeyState('S')) {
			this->dir.y = 1;
			this->setAnimRange(16, 23);
		}

		if (this->dir.x == 0 && this->dir.y == 0) {
			this->setAnimRange(32, 38);
		}
	}

	void Player::setAnimRange(int first, int last) {
		if (first != firstFrame) {
			currentFrame = first;
		}
		this->firstFrame = first;
		this->lastFrame = last;
	}

	void Player::playAnimation(float dt) {
		timeElapsedBF += dt;
		if (timeElapsedBF > timeBetweenFrames) {
			timeElapsedBF = 0;
			currentFrame++;
			
			if (currentFrame > lastFrame) {
				currentFrame = firstFrame;
			}

			this->humanSprite.SetFrame(currentFrame);
		}
	}

	void Player::move(float dt) {
		this->nextPos = this->pos;

		this->nextPos += vec2(this->dir.x * speed * dt, this->dir.y * speed * dt);

		if (!MapHandler::isSolid((*this->currentMap)[1], nextPos, 32)) {
			this->pos = this->nextPos;
		}

	}

	void Player::draw(Surface* screen, vec2 cameraOffset) {
		this->humanSprite.Draw(screen, this->pos.x - cameraOffset.x, this->pos.y - this->size.y - cameraOffset.y);
	}

	vec2 Player::getPos() {
		return this->pos;
	}
}