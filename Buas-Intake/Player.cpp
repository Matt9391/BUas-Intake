#include "Player.h"
#include "HumanState.h"

#include <Windows.h>

namespace Tmpl8 {

	Player::Player(Sprite& humanSprite, std::array<Map, 2>* currentMap) :
		humanSprite(humanSprite),
		currentMap(currentMap),
		pos({ ScreenWidth / 2, ScreenHeight / 2 }),
		size({ 32, 32 }),
		speed(0.15),
		firstFrame(0),
		lastFrame(1),
		currentFrame(0),
		timeBetweenFrames(70),
		timeElapsedBF(0),
		velocity(0, 0)
	{
		this->setState(0);
		humanSprite.SetFrame(38);
	}

	void Player::update(float dt) {
		//this->handleInput();
		this->state->handleInput(*this);
		this->move(dt);
		this->playAnimation(dt);
	}

	void Player::handleInput() {
		this->dir = { 0,0 };

		if (GetAsyncKeyState('A')) {
			this->dir.x = -1;
			this->setAnimRange(8, 15);
		}
		else if (GetAsyncKeyState('D')) {
			this->dir.x = 1;
			this->setAnimRange(0, 7);
		}
		if (GetAsyncKeyState('W')) {
			this->dir.y = -1;
			if (this->dir.x == 0)
				this->setAnimRange(24, 31);
		}
		else if (GetAsyncKeyState('S')) {
			this->dir.y = 1;
			if (this->dir.x == 0)
				this->setAnimRange(16, 23);
		}

		if (this->dir == vec2(0, 0))
			this->setAnimRange(32, 38);
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

		this->velocity = vec2(this->dir.x, this->dir.y);

		if (this->velocity.length() != 0)
			this->velocity.normalize();

		this->velocity *= speed * dt;

		this->nextPos += velocity;

		if (!MapHandler::isSolid((*this->currentMap)[1], nextPos, 32)) {
			this->pos = this->nextPos;
		}

	}

	void Player::draw(Surface* screen, vec2 cameraOffset) {
		if (this->visual == PlayerVisual::Human) {
			float yDrawPos = this->pos.y - this->size.y - this->size.y / 2.f - cameraOffset.y;
			float xDrawPos = this->pos.x - this->size.x / 2.f - cameraOffset.x;
			this->humanSprite.Draw(screen, xDrawPos, yDrawPos);
		}
	}

	vec2 Player::getPos() {
		return this->pos;
	}
	vec2 Player::getDir() {
		return this->dir;
	}
	vec2 Player::getSize() {
		return this->size;
	}

	void Player::setPos(const vec2& pos) {
		this->pos = pos;
	}
	
	void Player::setDir(const vec2& dir) {
		this->dir = dir;
	}

	void Player::setState(int state) {
		if (state == 0) {
			this->state = new HumanState();
			this->visual = PlayerVisual::Human;
		}
		//if (state == 1)
			//this->state = new HumanState();

	}
}