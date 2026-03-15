#include <DataTypes/PrintableBox.h>
#include <DataTypes/ChestObject.h>
#include <DataTypes/Fish.h>
#include <DataTypes/PlayerVisual.h>
#include <DataTypes/PrintableText.h>
#include <InteractableObjects/InteractableObject.h>
#include <PlayerStates/HumanState.h>
#include <PlayerStates/FishState.h>
#include <Utils/Text.h>
#include <Utils/functions.h>
#include <Utils/MapHandler.h>

#include "Player.h"

#include <surface.h>
#include <template.h>

#include <array>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace Tmpl8 {

	Player::Player(Sprite& humanSprite, std::array<Sprite*, 2>& fishSprites, long long& paidDebt) :
		debug(false),
		intersecting(false),
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
		fishSprites(fishSprites),
		state(nullptr),
		visual(PlayerVisual::Human),
		currentMap(nullptr),
		fishing(false),
		coins(100),
		paidDebt(paidDebt),
		coinsMultiplier(1),
		sprinting(false),
		maxSprintTime(2000.f),
		sprintElapsedTime(0.f),
		staminaMaxXSize(110),
		deadText("you got ate!! you've lost all your stuff"),
		deadTextPosition(pos),
		showDeadText(false),
		deadTimer(1000.f),
		deadTimeElapsed(0.f),
		showDamaged(false),
		damagedTimeElapsed(0.f),
		damagedTimer(200.f),
		isGettingDamaged(false),
		clr(0xFF0000)
	{
		this->setState(0);
		humanSprite.SetFrame(38);
	}
	 
	void Player::update(float dt) {
		
		//call state input handler
		this->state->handleInput(*this);
		this->handleSprint(dt);
		this->move(dt);
		this->playAnimation(dt);

		if (this->intersecting)
			this->setClr(0x00FF00);
		else
			this->setClr(0xFF0000);

		//if getting hitted by the enemies
		if (this->isGettingDamaged) {
			this->damagedTimeElapsed += dt;
			if (this->damagedTimeElapsed > this->damagedTimer) { //alternate original and damaged sprite
				this->showDamaged = !this->showDamaged;
				this->damagedTimeElapsed = 0.f;
			}
		}
		else {
			this->showDamaged = false;
		}


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
				this->fishSprites[0]->SetFrame(currentFrame);
				this->fishSprites[1]->SetFrame(currentFrame);
			}
		}
	}

	void Player::handleSprint(float dt) {
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

		//draw the related sprite based on current visual
		if (this->visual == PlayerVisual::Human) {
			int yDrawPos = int(this->pos.y - this->size.y * 2  - cameraOffset.y);
			int xDrawPos = int(this->pos.x + 1 - cameraOffset.x);
			this->humanSprite.Draw(screen, xDrawPos, yDrawPos);
		}
		else if (this->visual == PlayerVisual::Fish) {
			int yDrawPos = int(this->pos.y - this->size.y / 2.f  - cameraOffset.y);
			int xDrawPos = int(this->pos.x - 4.f - cameraOffset.x);
			if (this->showDamaged) {
				this->fishSprites[1]->Draw(screen, xDrawPos, yDrawPos);
			}
			else {
				this->fishSprites[0]->Draw(screen, xDrawPos, yDrawPos);
			}
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
	void Player::loadCollisionMaps(const std::array<Map, 2>& currentMap) {
		this->currentMap = &currentMap;
	}

	//getters
	vec2 Player::getPos() const {
		return this->pos;
	}
	vec2 Player::getDir() const {
		return this->dir;
	}
	vec2 Player::getSize() const {
		return this->size;
	}

	char Player::getInput() const {
		return this->input;
	}

	PlayerVisual Player::getPlayerVisual() const {
		return this->visual;
	}

	bool Player::isInteracting() const {
		return this->interacting;
	}

	bool Player::isFishing() const {
		return this->fishing;
	}

	long long Player::getCoins() const {
		return this->coins;
	}
	
	float Player::getMultiplier() const {
		return this->coinsMultiplier;
	}
	
	float Player::getStamina() const {
		return this->maxSprintTime;
	}


	const std::vector<Fish>& Player::getFishes() const {
		return this->fishInventory;
	}
	
	const std::vector<ChestObject>& Player::getChests() const {
		return this->chestInventory;
	}
	
	const std::vector <PrintableText>& Player::getTexts() const {
		return this->texts;
	}
	
	const std::vector<PrintableBox>& Player::getBoxes() const {
		return this->boxes;
	}


	//setters
	void Player::setIntersecting(bool intersecting) {
		this->intersecting = intersecting;
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
			this->state = std::make_unique<HumanState>();
			this->visual = PlayerVisual::Human;
			this->state->enter(*this);
		}
		else if (state == 1) {
			this->state = std::make_unique<FishState>();
			this->visual = PlayerVisual::Fish;
			this->state->enter(*this);
		}

	}
	
	void Player::setDamaged(bool damaged) {
		this->isGettingDamaged = damaged;
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

	void Player::addFish(const Fish& fish) {
		this->fishInventory.push_back(fish);
	}
	
	void Player::addChest(const ChestObject& chest) {
		this->chestInventory.push_back(chest);
	}

	void Player::setMultiplier(float multiplier) {
		this->coinsMultiplier = multiplier;
	}
	void Player::addStamina(float ms) {
		this->maxSprintTime += ms;
	}
	
	void Player::payDebt(int coins) {
		this->paidDebt += (long long)(coins * this->coinsMultiplier);
	}

	void Player::enableDebug(bool enable) {
		this->debug = enable;
	}


	void Player::setTexts(vec2 cameraOffset) {
		this->texts.clear();

		this->texts.push_back({ "Coins:", vec2(32, 52 - 16), 1, false});
		this->texts.push_back({ formatCoins(this->coins), vec2(32, 72 - 16), 1, false });
		this->texts.push_back({ "Fishes: " + std::to_string(this->fishInventory.size()), vec2(96, 52 - 16), 1, false });
		this->texts.push_back({ "Chests: " + std::to_string(this->chestInventory.size()), vec2(96, 72 - 16) , 1, false });
		this->texts.push_back({ std::to_string(int((this->maxSprintTime - this->sprintElapsedTime) / 1000)) + "s", vec2(150, 32 - 16), 1, false });
		
		if (showDeadText) {
			this->texts.push_back({ this->deadText, this->deadTextPosition - cameraOffset, 1, false });
		}
	}

	void Player::setBoxes(vec2 cameraOffset) {
		this->boxes.clear();

		this->boxes.push_back({ vec2(26, 13), vec2(148, 56), 0x604239, false });

		if(this->debug)
			this->boxes.push_back({ this->pos - cameraOffset, this->size, this->clr, false, false });

		this->boxes.push_back({ vec2(32, 18), vec2(mapValue(this->sprintElapsedTime, 0.f, this->maxSprintTime, float(this->staminaMaxXSize), 0.f),5), 0xFF0000, false });

		if (this->showDamaged) {
			this->boxes.push_back({ vec2(32, 72 - 16), vec2(getLength(formatCoins(this->coins)) * 7.f, 10.f), 0xFF0000, false });
		}



	}


	void Player::setClr(Pixel clr) {
		this->clr = clr;
	}

	//load data passed from gameSave
	void Player::loadData(const std::unordered_map<std::string, double>& gameSave) {
		this->coins = long long(gameSave.at("coins"));

		//clear current inventories and then load from save data
		this->fishInventory.clear();
		
		for (int i = 0; i < int(gameSave.at("fish_common")); i++) {
			this->fishInventory.push_back({ FishRarity::COMMON, 80 });
		}
		for (int i = 0; i < int(gameSave.at("fish_rare")); i++) {
			this->fishInventory.push_back({ FishRarity::RARE, 150 });
		}
		for (int i = 0; i < int(gameSave.at("fish_epic")); i++) {
			this->fishInventory.push_back({ FishRarity::EPIC, 300 });
		}
		for (int i = 0; i < int(gameSave.at("fish_legendary")); i++) {
			this->fishInventory.push_back({ FishRarity::LEGENDARY, 500 });
		}

		this->chestInventory.clear();
		for (int i = 0; i < int(gameSave.at("chest0")); i++) {
			this->chestInventory.push_back({ 0, mapValue(0.f, 0.f, 3.f, 50.f, 1000.f) });
		}
		for (int i = 0; i < int(gameSave.at("chest1")); i++) {
			this->chestInventory.push_back({ 0, mapValue(1.f, 0.f, 3.f, 50.f, 1000.f) });
		}
		for (int i = 0; i < int(gameSave.at("chest2")); i++) {
			this->chestInventory.push_back({ 0, mapValue(2.f, 0.f, 3.f, 50.f, 1000.f) });
		}
		for (int i = 0; i < int(gameSave.at("chest3")); i++) {
			this->chestInventory.push_back({ 0, mapValue(3.f, 0.f, 3.f, 50.f, 1000.f) });
		}

		this->coinsMultiplier = float(gameSave.at("incomeMultiplier"));
		this->maxSprintTime = float(gameSave.at("stamina"));
	}
}