#include "Player.h"
#include "HumanState.h"
#include "FishState.h"
#include "Text.h"
#include "functions.h"
#include "Game.h"
#include <Windows.h>



namespace Tmpl8 {

	Player::Player(Sprite& humanSprite, Sprite& fishSprite) :
		humanSprite(humanSprite),
		fishSprite(fishSprite),
		currentMap(nullptr),
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
		coins(100),
		coinsMultiplier(1),
		sprinting(false),
		sprintElapsedTime(0.f),
		maxSprintTime(2000.f),
		sprintSpeed(0.35),
		baseSpeed(0.15),
		deadText("you got ate!! you've lost all your stuff"),
		deadTextPosition(pos),
		showDeadText(false),
		deadTimer(1000.f),
		deadTimeElapsed(0.f)
	{
		this->setState(0);
		humanSprite.SetFrame(38);
	}
	 
	void Player::update(float dt) {
		//this->handleInput();
		this->state->handleInput(*this);
		this->sprint(dt);
		this->move(dt);
		this->playAnimation(dt);

		if (showDeadText) {
			this->deadTimeElapsed += dt;
			if (this->deadTimeElapsed > this->deadTimer) {
				this->showDeadText = false;
				this->deadTimeElapsed = 0.f;
			}
			this->deadTextPosition = this->pos + vec2(-112, -32);
			this->deadTextPosition.x = constrain(this->deadTextPosition.x, 10.f, float(ScreenWidth - 300));
		}

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

			if (this->visual == PlayerVisual::Human) {
				this->humanSprite.SetFrame(currentFrame);
			}else if (this->visual == PlayerVisual::Fish) {
				this->fishSprite.SetFrame(currentFrame);
			}
		}
	}

	void Player::sprint(float dt) {
		if (!this->sprinting) {
			this->sprintElapsedTime -= dt;
			if (this->sprintElapsedTime <= 0.f) this->sprintElapsedTime = 0.f;
			this->speed = this->baseSpeed;
			return;
		}

		if (this->sprintElapsedTime < this->maxSprintTime) {
			this->sprintElapsedTime += dt;
			this->speed = this->state->getSprintSpeed();
		}
		else {
			this->speed = this->baseSpeed;
		}
	}

	void Player::move(float dt) {
		if (this->fishing)
			return;

		this->nextPos = this->pos;

		this->velocity = vec2(this->dir.x, this->dir.y);

		if (this->velocity.length() != 0)
			this->velocity.normalize();

		this->velocity.x *= speed * dt;
		this->velocity.y *= baseSpeed * dt;

		this->nextPos += velocity;


		if (this->currentMap == nullptr)
		{
			this->pos = this->nextPos;
			return;
		}

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
		else if (this->visual == PlayerVisual::Fish) {
			int yDrawPos = int(this->pos.y - this->size.y / 2.f  - cameraOffset.y);
			int xDrawPos = int(this->pos.x - 4.f - cameraOffset.x);
			this->fishSprite.Draw(screen, xDrawPos, yDrawPos);
		}

		//Text::drawString(std::to_string(this->coins), screen, vec2(64, 96));
		Text::drawString("Coins:", screen, vec2(32, 52));
		Text::printCoins(screen, vec2(33, 72), this->coins);
		Text::drawString("Fishes: " + std::to_string(this->fishInventory.size()), screen, vec2(96, 52));
		Text::drawString("Chests: " + std::to_string(this->chestInventory.size()), screen, vec2(96, 72));
		
		drawStamina(screen, vec2(32, 34));
		Text::drawString(std::to_string(int((this->maxSprintTime - this->sprintElapsedTime) / 1000)) + "s", screen, vec2(150, 32));

		if (showDeadText) {
			Text::drawString(this->deadText, screen,this->deadTextPosition - cameraOffset);
		}
	}

	void Player::clearFishInventory() {
		this->fishInventory.clear();
	}
	
	void Player::clearChestInventory() {
		this->chestInventory.clear();
	}

	void Player::loadCollisionMaps(std::array<Map, 2>* currentMap) {
		this->currentMap = currentMap;
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

	PlayerVisual Player::getPlayerVisual() {
		return this->visual;
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
	
	float Player::getMultiplier() {
		return this->coinsMultiplier;
	}
	
	float Player::getStamina() {
		return this->maxSprintTime;
	}

	std::vector<Fish> Player::getFishes() {
		return this->fishInventory;
	}
	
	std::vector<ChestObject> Player::getChests() {
		return this->chestInventory;
	}

	void Player::setInteracting(bool state) {
		this->interacting = state;
	}

	void Player::setSprinting(bool sprinting) {
		this->sprinting = sprinting;
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
			this->state->enter(*this);
		}
		else if (state == 1) {
			this->state = new FishState();
			this->visual = PlayerVisual::Fish;
			this->state->enter(*this);
		}

	}

	void Player::setCoins(long long coins) {
		this->coins = coins;
	}
	
	void Player::spendCoins(int coins) {
		this->coins -= coins;
	}

	void Player::stealCoins(int coins) {
		this->coins -= (long long) (coins * this->coinsMultiplier * 1.5f);
		if (this->coins <= 0) {
			this->coins = 0;
			this->chestInventory.clear();
			this->showDeadText = true;
		}
	}

	void Player::addCoins(int coins) {
		this->coins += (long long)(coins * this->coinsMultiplier);
	}

	void Player::addFish(Fish fish) {
		this->fishInventory.push_back(fish);
	}
	
	void Player::addChest(ChestObject chest) {
		this->chestInventory.push_back(chest);
	}

	void Player::setMultiplier(float multiplier) {
		this->coinsMultiplier = multiplier;
	}
	void Player::addStamina(float ms) {
		this->maxSprintTime += ms;
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

	void Player::drawStamina(Surface* screen, vec2 pos) {
		int maxSizeX = 110;
		vec2 size(0, 5);

		size.x = mapValue(this->sprintElapsedTime, 0, this->maxSprintTime, float(maxSizeX), 0);

		Pixel red = 0xFF0000; // formato: 0xRRGGBB

		Pixel* buffer = screen->GetBuffer();
		int pitch = screen->GetPitch(); // pixel per riga

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

	void Player::loadData(std::unordered_map<std::string, double>& gameSave) {
		this->coins = long long(gameSave["coins"]);
		this->fishInventory.clear();
		//printf("LKKKK; %d\n", gameSave["fish_legendary"]);
		for (int i = 0; i < int(gameSave["fish_common"]); i++) {
			this->fishInventory.push_back({ Rarity::COMMON, 80 });
		}
		for (int i = 0; i < int(gameSave["fish_rare"]); i++) {
			this->fishInventory.push_back({ Rarity::RARE, 150 });
		}
		for (int i = 0; i < int(gameSave["fish_epic"]); i++) {
			this->fishInventory.push_back({ Rarity::EPIC, 300 });
		}
		for (int i = 0; i < int(gameSave["fish_legendary"]); i++) {
			this->fishInventory.push_back({ Rarity::LEGENDARY, 500 });

		}

		this->chestInventory.clear();
		for (int i = 0; i < int(gameSave["chest0"]); i++) {
			this->chestInventory.push_back({ 0, mapValue(0.f, 0.f, 3.f, 50.f, 1000.f) });
		}
		for (int i = 0; i < int(gameSave["chest1"]); i++) {
			this->chestInventory.push_back({ 0, mapValue(1.f, 0.f, 3.f, 50.f, 1000.f) });
		}
		for (int i = 0; i < int(gameSave["chest2"]); i++) {
			this->chestInventory.push_back({ 0, mapValue(2.f, 0.f, 3.f, 50.f, 1000.f) });
		}
		for (int i = 0; i < int(gameSave["chest3"]); i++) {
			this->chestInventory.push_back({ 0, mapValue(3.f, 0.f, 3.f, 50.f, 1000.f) });
		}

		this->coinsMultiplier = double(gameSave["incomeMultiplier"]);
		this->maxSprintTime = float(gameSave["stamina"]);
	}
}