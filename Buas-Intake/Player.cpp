#include "Player.h"
#include "HumanState.h"
#include "Text.h"

#include <Windows.h>

namespace Tmpl8 {

	Player::Player(Sprite& humanSprite, std::array<Map, 2>* currentMap) :
		humanSprite(humanSprite),
		currentMap(currentMap),
		pos({ ScreenWidth / 2, ScreenHeight / 2 }),
		size({ 32, 16 }),
		speed(0.15),
		firstFrame(0),
		lastFrame(1),
		currentFrame(0),
		timeBetweenFrames(70),
		timeElapsedBF(0),
		velocity(0, 0),
		input(' '),
		fishing(false),
		coins(100)
	{
		this->setState(0);
		humanSprite.SetFrame(38);
	}

	void Player::update(float dt) {
		//this->handleInput();
		this->state->handleInput(*this);
		this->move(dt);
		this->playAnimation(dt);

		//printf("FISHESSS\n");
		//for (Fish& fish : this->fishInventory) {
		//	printf("%d, %.0f\n", fish.rarity, fish.value);
		//}
		//printf("FINE----------------------\n");
	}

	/*void Player::handleInput() {
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
	}*/

	void Player::setAnimRange(int first, int last) {
		if (first != firstFrame) {
			currentFrame = first;
		}
		this->firstFrame = first;
		this->lastFrame = last;
	}

	void Player::playAnimation(float dt) {
		if (this->fishing)
			return;
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
		if (this->fishing)
			return;

		this->nextPos = this->pos;

		this->velocity = vec2(this->dir.x, this->dir.y);

		if (this->velocity.length() != 0)
			this->velocity.normalize();

		this->velocity *= speed * dt;

		this->nextPos += velocity;

		vec2 xNextPos(this->nextPos.x, this->pos.y);
		vec2 yNextPos(this->pos.x, this->nextPos.y);

		//to check collision on both axis separately
		if (!MapHandler::isSolid((*this->currentMap)[1], xNextPos, this->size, 32)&&
			!MapHandler::isSolid((*this->currentMap)[0], xNextPos, this->size, 32)) {
			this->pos.x = xNextPos.x;
		}
		if (!MapHandler::isSolid((*this->currentMap)[1], yNextPos, this->size, 32) &&
			!MapHandler::isSolid((*this->currentMap)[0], yNextPos, this->size, 32)) {
			this->pos.y = yNextPos.y;
		}
		/*
		if (!MapHandler::isSolid((*this->currentMap)[1], nextPos, this->size, 32)&&
			!MapHandler::isSolid((*this->currentMap)[0], nextPos, this->size, 32)) {
			this->pos = this->nextPos;
		}*/

	}

	void Player::draw(Surface* screen, vec2 cameraOffset) {
		//this->showHitbox(screen, cameraOffset);
		if (this->visual == PlayerVisual::Human) {
			int yDrawPos = int(this->pos.y - this->size.y * 2  - cameraOffset.y);
			int xDrawPos = int(this->pos.x + 1 - cameraOffset.x);
			this->humanSprite.Draw(screen, xDrawPos, yDrawPos);
		}

		Text::drawString(std::to_string(this->coins), screen, vec2(64, 64));
	}

	void Player::clearFishes() {
		this->fishInventory.clear();
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

	char Player::getInput() {
		return this->input;
	}

	bool Player::isInteracting() {
		return this->interacting;
	}

	bool Player::isFishing() {
		return this->fishing;
	}

	long long Player::getCoins() {
		return this->coins;
	}

	std::vector<Fish> Player::getFishes() {
		return this->fishInventory;
	}

	void Player::setInteracting(bool state) {
		this->interacting = state;
	}

	void Player::setFishing(bool state) {
		this->fishing = state;
	}

	void Player::setPos(const vec2& pos) {
		this->pos = pos;
	}
	
	void Player::setDir(const vec2& dir) {
		this->dir = dir;
	}
	void Player::setInput(const char& input) {
		this->input = input;
	}

	void Player::setState(int state) {
		if (state == 0) {
			this->state = new HumanState();
			this->visual = PlayerVisual::Human;
		}
		//if (state == 1)
			//this->state = new HumanState();

	}

	void Player::setCoins(long long coins) {
		this->coins = coins;
	}
	
	void Player::addCoins(int coins) {
		this->coins += coins;
	}

	void Player::addFish(Fish fish) {
		this->fishInventory.push_back(fish);
	}

	void Player::showHitbox(Surface* screen, vec2 cameraOffset) {
		vec2 size = this->size;
		Pixel red = 0xFF0000; // formato: 0xRRGGBB

		Pixel* buffer = screen->GetBuffer();
		int pitch = screen->GetPitch(); // pixel per riga
		vec2 pos(this->pos.x - cameraOffset.x, this->pos.y - cameraOffset.y);

		for (int dy = 0; dy < size.y; dy++)
		{
			int py = int(pos.y) + dy;
			if (py < 0 || py >= screen->GetHeight()) continue;

			for (int dx = 0; dx < size.x; dx++)
			{
				int px = int(pos.x) + dx;
				if (px < 0 || px >= screen->GetWidth()) continue;

				buffer[px + py * pitch] = red;
			}
		}
	}
}