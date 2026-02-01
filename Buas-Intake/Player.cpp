#include "Player.h"
#include "HumanState.h"
#include "FishState.h"
#include "Text.h"
#include "functions.h"
#include "ChestObject.h"
#include "Fish.h"
#include "PlayerVisual.h"
#include "tmpl8/surface.h"
#include "tmpl8/template.h"



namespace Tmpl8 {

	Player::Player(Sprite& humanSprite, Sprite& fishSprite) :
		debug(false),
		interacting(false),
		input(' '),
		firstFrame(0),
		lastFrame(1),
		currentFrame(0),
		timeBetweenFrames(70),
		timeElapsedBF(0),
		pos({ ScreenWidth / 2, ScreenHeight / 2 }), 
		nextPos(pos),
		size({ 32, 16 }), 
		velocity(0, 0),
		speed(0.15),
		baseSpeed(0.15),
		sprintSpeed(0.35),
		dir(0,0),
		humanSprite(humanSprite),
		fishSprite(fishSprite),
		state(nullptr),
		visual(PlayerVisual::Human),
		currentMap(nullptr),
		fishing(false),
		coins(100),
		coinsMultiplier(1),
		sprinting(false),
		maxSprintTime(2000.f),
		sprintElapsedTime(0.f),
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
		
		//call state input handler
		this->state->handleInput(*this);
		this->sprint(dt);
		this->move(dt);
		this->playAnimation(dt);

		//if dead text is showing, update its timer and position
		if (showDeadText) {
			this->deadTimeElapsed += dt;
			if (this->deadTimeElapsed > this->deadTimer) {
				this->showDeadText = false;
				this->deadTimeElapsed = 0.f;
			}
			this->deadTextPosition = this->pos + vec2(-112, -32);
			//constrain dead text position within screen bounds
			this->deadTextPosition.x = constrain(this->deadTextPosition.x, 10.f, float(ScreenWidth - 300));
		}


	}

	//set the animation range if changed
	void Player::setAnimRange(int first, int last) {
		if (first != firstFrame) {
			currentFrame = first;
		}
		this->firstFrame = first;
		this->lastFrame = last;
	}

	//play animation within the set frame range
	void Player::playAnimation(float dt) {
		//dont play animation if fishing
		if (this->fishing)
			return;
		timeElapsedBF += dt;
		if (timeElapsedBF > timeBetweenFrames) {
			timeElapsedBF = 0;
			currentFrame++;

			if (currentFrame > lastFrame) {
				currentFrame = firstFrame;
			}

			//set the frame to the related sprite
			if (this->visual == PlayerVisual::Human) {
				this->humanSprite.SetFrame(currentFrame);
			}else if (this->visual == PlayerVisual::Fish) {
				this->fishSprite.SetFrame(currentFrame);
			}
		}
	}

	void Player::sprint(float dt) {
		//if not sprinting, recover stamina and set speed to base speed
		if (!this->sprinting) {
			this->sprintElapsedTime -= dt;
			if (this->sprintElapsedTime <= 0.f) this->sprintElapsedTime = 0.f;
			this->speed = this->baseSpeed;
			return;
		}

		//if sprinting, increase elapsed sprint time and set speed to sprint speed if stamina is available
		if (this->sprintElapsedTime < this->maxSprintTime) {
			this->sprintElapsedTime += dt;
			this->speed = this->state->getSprintSpeed();
		}
		else {
			this->speed = this->baseSpeed;
		}
	}

	void Player::move(float dt) {
		//cant move while fishing
		if (this->fishing)
			return;

		//set next position based on direction and speed
		this->nextPos = this->pos;

		this->velocity = vec2(this->dir.x, this->dir.y);

		//normalize velocity to avoid faster diagonal movement
		if (this->velocity.length() != 0)
			this->velocity.normalize();

		//variable speed only on x axis for sideway sprinting (I thought it would be better)
		this->velocity.x *= speed * dt;
		this->velocity.y *= baseSpeed * dt;

		this->nextPos += velocity;
		
		//if no collision maps loaded, move freely
		if (this->currentMap == nullptr)
		{
			this->pos = this->nextPos;
			return;
		}

		//separate axis collision detection
		vec2 xNextPos(this->nextPos.x, this->pos.y);
		vec2 yNextPos(this->pos.x, this->nextPos.y);

		//check collisions on each axis separately and apply movement if no collision
		if (!MapHandler::isSolid((*this->currentMap)[1], xNextPos, this->size, 32)&&
			!MapHandler::isSolid((*this->currentMap)[0], xNextPos, this->size, 32)) {
			this->pos.x = xNextPos.x;
		}
		if (!MapHandler::isSolid((*this->currentMap)[1], yNextPos, this->size, 32) &&
			!MapHandler::isSolid((*this->currentMap)[0], yNextPos, this->size, 32)) {
			this->pos.y = yNextPos.y;
		}

	}

	void Player::draw(Surface* screen, vec2 cameraOffset) {
		if (this->debug) {
			this->showHitbox(screen, cameraOffset);
		}

		//draw the related sprite based on current visual
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

		//draw UI elements (should be done in a separate UI class but for simplicity done here)
		Text::drawString("Coins:", screen, vec2(32, 52));
		Text::drawCoins(screen, vec2(32, 72), this->coins);
		Text::drawString("Fishes: " + std::to_string(this->fishInventory.size()), screen, vec2(96, 52));
		Text::drawString("Chests: " + std::to_string(this->chestInventory.size()), screen, vec2(96, 72));
		
		drawStamina(screen, vec2(32, 34));
		Text::drawString(std::to_string(int((this->maxSprintTime - this->sprintElapsedTime) / 1000)) + "s", screen, vec2(150, 32));

		if (showDeadText) {
			Text::drawString(this->deadText, screen,this->deadTextPosition - cameraOffset);
		}
	}

	//clear inventories
	void Player::clearFishInventory() {
		this->fishInventory.clear();
	}
	
	void Player::clearChestInventory() {
		this->chestInventory.clear();
	}

	//load current active collision maps
	void Player::loadCollisionMaps(std::array<Map, 2>* currentMap) {
		this->currentMap = currentMap;
	}

	//getters
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

	//setters
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

	//stealCoins spends coins with a multiplier and triggers "death" if coins go below 0
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

	void Player::enableDebug(bool enable) {
		this->debug = enable;
	}

	//draw player hitbox for debugging
	void Player::showHitbox(Surface* screen, vec2 cameraOffset) {
		vec2 size = this->size;
		Pixel red = 0xFF0000; //format: 0xRRGGBB

		Pixel* buffer = screen->GetBuffer();
		int pitch = screen->GetPitch(); // pixel per row
		vec2 pos(this->pos.x - cameraOffset.x, this->pos.y - cameraOffset.y);

		//draw rectangle based on player size
		for (int dy = 0; dy < size.y; dy++)
		{
			//calculate y position
			int py = int(pos.y) + dy;
			//skip if outside screen
			if (py < 0 || py >= screen->GetHeight()) continue;

			for (int dx = 0; dx < size.x; dx++)
			{
				//calculate x position
				int px = int(pos.x) + dx;
				//skip if outside screen
				if (px < 0 || px >= screen->GetWidth()) continue;

				//set pixel to red
				buffer[px + py * pitch] = red;
			}
		}
	}

	void Player::drawStamina(Surface* screen, vec2 pos) {
		//x size of the stamina bar (could be a class constant)
		int maxSizeX = 110;
		//bar size
		vec2 size(0, 5);

		//map size.x based on sprint elapsed time
		size.x = mapValue(this->sprintElapsedTime, 0.f, this->maxSprintTime, float(maxSizeX), 0.f);

		Pixel red = 0xFF0000; //format: 0xRRGGBB

		Pixel* buffer = screen->GetBuffer();
		int pitch = screen->GetPitch(); // pixel per riga

		//draw stamina bar
		for (int dy = 0; dy < size.y; dy++)
		{
			//calculate y position
			int py = int(pos.y) + dy;
			//skip if outside screen
			if (py < 0 || py >= screen->GetHeight()) continue;

			for (int dx = 0; dx < size.x; dx++)
			{
				//calculate x position
				int px = int(pos.x) + dx;
				//skip if outside screen
				if (px < 0 || px >= screen->GetWidth()) continue;

				//set pixel to red
				buffer[px + py * pitch] = red;
			}
		}
	}

	//load data passed from gameSave
	void Player::loadData(std::unordered_map<std::string, double>& gameSave) {
		this->coins = long long(gameSave["coins"]);
		
		//clear current inventories and then load from save data
		this->fishInventory.clear();
		
		for (int i = 0; i < int(gameSave["fish_common"]); i++) {
			this->fishInventory.push_back({ FishRarity::COMMON, 80 });
		}
		for (int i = 0; i < int(gameSave["fish_rare"]); i++) {
			this->fishInventory.push_back({ FishRarity::RARE, 150 });
		}
		for (int i = 0; i < int(gameSave["fish_epic"]); i++) {
			this->fishInventory.push_back({ FishRarity::EPIC, 300 });
		}
		for (int i = 0; i < int(gameSave["fish_legendary"]); i++) {
			this->fishInventory.push_back({ FishRarity::LEGENDARY, 500 });
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

		this->coinsMultiplier = float(gameSave["incomeMultiplier"]);
		this->maxSprintTime = float(gameSave["stamina"]);
	}
}