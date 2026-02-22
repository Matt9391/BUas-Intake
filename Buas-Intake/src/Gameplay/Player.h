#include <array>
#include <vector>
#include <string>
#include <unordered_map>
#include "../../tmpl8/template.h"
#include "../Utils/MapHandler.h"
#include "../DataTypes/PlayerVisual.h"
#include "../DataTypes/Fish.h"
#include "../DataTypes/ChestObject.h"
#include "../DataTypes/PrintableText.h"
#include "../DataTypes/PrintableBox.h"

#pragma once

namespace Tmpl8 {
	class Sprite;
	class vec2;
	class Surface;
	class PlayerState;

	class Player
	{
	public:

		Player(Sprite& humanSprite, std::array<Sprite*, 2>& fishSprites, long long& paidDebt);

		void update(float dt);
		
		//sprinting mechanic
		void sprint(float dt);

		//movement mechanic based on input and collision maps
		void move(float dt);
		 
		void draw(Surface* screen, vec2 cameraOffset);

		//clear inventories
		void clearFishInventory();
		void clearChestInventory();

		//load current active collision maps
		void loadCollisionMaps(std::array<Map, 2>* currentMap);


		//getters
		vec2 getPos();
		vec2 getDir();
		vec2 getSize();
		char getInput();
		PlayerVisual getPlayerVisual();
		bool isInteracting();
		bool isFishing();
		long long getCoins();
		float getMultiplier();
		float getStamina();
		std::vector<Fish> getFishes();
		std::vector<ChestObject> getChests();
		std::vector <PrintableText>getTexts();
		//function that return the hitbox of the entity;
		std::vector <PrintableBox> getBoxes();

		//setters
		void setInteracting(bool state);
		void setSprinting(bool sprinting);
		void setFishing(bool state);
		void setPos(const vec2& pos);
		void setDir(const vec2& dir);
		void setState(int state);
		void setDamaged(bool damaged);
		void setInput(const char& input);
		void setCoins(long long coins);
		//spendCoins just spends coins normally
		void spendCoins(int coins); 
		//stealCoins spends coins with a multiplier and triggers "death" if coins go below 0
		void stealCoins(int coins);
		void addCoins(int coins);
		void addFish(Fish fish);
		void addChest(ChestObject chest);
		void setMultiplier(float multiplier);
		void addStamina(float ms);
		void payDebt(int coins);
		void enableDebug(bool enable);
		void setTexts(vec2 cameraOffset);
		void setBoxes(vec2 cameraOffset);

		//set the animation range
		void setAnimRange(int first, int last);

		//load data passed from gameSave
		void loadData(const std::unordered_map<std::string, double>& gameSave);
		long long& paidDebt;

	private:
		//draw stamina bar
		void drawStamina(Surface* screen, vec2 pos);
		//draw box bar
		void drawBox(Surface* screen, vec2 pos, vec2 size);

		bool debug;

		//play animation within the set frame range
		void playAnimation(float dt);

		//current interaction state
		bool interacting;
		//last input received
		char input;
		//animation frames info
		int firstFrame;
		int lastFrame;
		int currentFrame;	
		//time required between frames 
		float timeBetweenFrames;
		//time elapsed since last frame change
		float timeElapsedBF;

		//position of the player
		vec2 pos;
		//next position after movement calculation, applied if no collision
		vec2 nextPos;
		vec2 size;
		vec2 velocity;

		//speed variables
		float speed;
		float baseSpeed;
		float sprintSpeed;

		//direction vector based on input
		vec2 dir;

		//sprites for different player visuals
		Sprite &humanSprite;
		std::array<Sprite*, 2>& fishSprites;

		//current state of the player
		PlayerState* state;
		//current visual representation, could be done with bool but this allows for future expansions
		PlayerVisual visual;

		//current collision maps
		std::array<Map, 2> *currentMap;

		//fishing state
		bool fishing;

		//coins of the player
		long long coins;
		//debt of the player

		//coins multiplier when selling fish/chests or getting stolen
		float coinsMultiplier;

		//inventories
		std::vector<Fish> fishInventory;
		std::vector<ChestObject> chestInventory;

		//sprinting variables
		bool sprinting;
		float maxSprintTime;
		float sprintElapsedTime;
		int staminaMaxXSize;

		//death text variables
		std::string deadText;
		vec2 deadTextPosition;
		bool showDeadText;
		//dead timer variables
		float deadTimeElapsed;
		float deadTimer;

		//whether to show the original sprite or the damaged one
		bool showDamaged;
		float damagedTimeElapsed;
		float damagedTimer;
		bool isGettingDamaged;

		std::vector<PrintableText> texts;
		std::vector <PrintableBox> boxes;
	};

}
