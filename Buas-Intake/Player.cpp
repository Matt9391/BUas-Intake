#include "Player.h"
#include <Windows.h>


namespace Tmpl8 {
	Player::Player(Sprite& humanSprite, std::array<Map, 2>* currentMap) :
		humanSprite(humanSprite),
		currentMap(currentMap),
		pos({ScreenWidth / 2, ScreenHeight/2}),
		size({32, 32}),
		speed(0.1)
	{
		humanSprite.SetFrame(38);
	}

	void Player::update(float dt) {
		this->handleInput();
		this->move(dt);
	}

	void Player::handleInput() {
		this->dir = { 0,0 };
		if (GetAsyncKeyState('A'))
			this->dir.x = -1;
		if (GetAsyncKeyState('D'))
			this->dir.x = 1;
		if (GetAsyncKeyState('W'))
			this->dir.y = -1;
		if (GetAsyncKeyState('S'))
			this->dir.y = 1;
	}

	void Player::move(float dt) {
		this->nextPos = this->pos;

		this->nextPos += vec2(this->dir.x, this->dir.y);

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