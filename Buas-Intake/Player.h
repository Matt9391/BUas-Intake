#include "./tmpl8/surface.h"
#include "./tmpl8/template.h"
#include <array>
#include <vector>
#include "MapHandler.h"
#include "PlayerState.h"
#include "PlayerVisual.h"
#include "Fish.h"
#include "ChestObject.h"
#include <string>
#include <unordered_map>

#pragma once

namespace Tmpl8 {

	class Player
	{
	public:

		Player(Sprite& humanSprite, Sprite& fishSprite);

		void update(float dt);
		
		void sprint(float dt);
		void move(float dt);
		
		//void handleInput();
 
		void draw(Surface* screen, vec2 cameraOffset);

		void clearFishInventory();
		void clearChestInventory();

		void loadCollisionMaps(std::array<Map, 2>* currentMap);

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

		void setInteracting(bool state);
		void setSprinting(bool sprinting);
		void setFishing(bool state);
		void setPos(const vec2& pos);
		void setDir(const vec2& dir);
		void setState(int state);
		void setInput(const char& input);
		void setCoins(long long coins);
		void spendCoins(int coins); 
		void stealCoins(int coins);
		void addCoins(int coins);
		void addFish(Fish fish);
		void addChest(ChestObject chest);
		void setMultiplier(float multiplier);
		void addStamina(float ms);
		void enableDebug(bool enable);

		void setAnimRange(int first, int last);

		void loadData(std::unordered_map<std::string, double>& gameSave);

	private:
		void showHitbox(Surface* screen, vec2 cameraOffset);
		void drawStamina(Surface* screen, vec2 pos);

		bool debug;

		void playAnimation(float dt);

		bool interacting;

		char input;

		int firstFrame;
		int lastFrame;
		int currentFrame;	
		float timeBetweenFrames;
		float timeElapsedBF;

		vec2 pos;
		vec2 nextPos;
		vec2 size;
		vec2 velocity;

		float speed;
		float baseSpeed;
		float sprintSpeed;

		vec2 dir;
		Sprite &humanSprite;
		Sprite &fishSprite;

		PlayerState* state;
		PlayerVisual visual;

		std::array<Map, 2> *currentMap;
		//Sprite &fishSprite;

		bool fishing;

		long long coins;
		float coinsMultiplier;

		std::vector<Fish> fishInventory;
		std::vector<ChestObject> chestInventory;

		bool sprinting;
		float maxSprintTime;
		float sprintElapsedTime;

		std::string deadText;
		vec2 deadTextPosition;
		bool showDeadText;
		float deadTimeElapsed;
		float deadTimer;

	};

}
