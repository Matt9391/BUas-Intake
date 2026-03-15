#pragma once

#include <DataTypes/PlayerVisual.h>
#include <DataTypes/Fish.h>
#include <DataTypes/ChestObject.h>
#include <DataTypes/PrintableText.h>
#include <DataTypes/PrintableBox.h>
#include <PlayerStates/PlayerState.h>
#include <Utils/MapHandler.h>

#include <memory>
#include <array>
#include <vector>
#include <string>
#include <unordered_map>


namespace Tmpl8 {
	class Sprite;
	class vec2;
	class Surface;

	class Player
	{
	public:

		Player(Sprite& humanSprite, std::array<Sprite*, 2>& fishSprites, long long& paidDebt);

		void update(float dt);
		
		void handleSprint(float dt);

		void move(float dt);
		 
		void draw(Surface* screen, vec2 cameraOffset);

		void clearFishInventory();
		void clearChestInventory();

		//load current active collision maps
		void loadCollisionMaps(const std::array<Map, 2>& currentMap);

		//getters
		vec2 getPos() const;
		vec2 getDir() const;
		vec2 getSize() const;
		char getInput() const;
		PlayerVisual getPlayerVisual() const;
		bool isInteracting() const;
		bool isFishing() const;
		long long getCoins() const;
		float getMultiplier() const;
		float getStamina() const;
		const std::vector<Fish>& getFishes() const;
		const std::vector<ChestObject>& getChests() const;
		const std::vector <PrintableText>& getTexts() const;
		const std::vector <PrintableBox>& getBoxes() const;

		//setters
		void setIntersecting(bool intersecting);
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
		void addFish(const Fish& fish);
		void addChest(const ChestObject& chest);
		void setMultiplier(float multiplier);
		void addStamina(float ms);
		void payDebt(int coins);
		void enableDebug(bool enable);
		void setTexts(vec2 cameraOffset);
		void setBoxes(vec2 cameraOffset);
		void setClr(Pixel crl);
		void setAnimRange(int first, int last);

		//load data from gameSave
		void loadData(const std::unordered_map<std::string, double>& gameSave);

	private:

		bool debug;

		//play animation within the set frame range
		void playAnimation(float dt);

		bool intersecting;
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

		vec2 dir;

		//sprites for different player visuals
		Sprite &humanSprite;
		std::array<Sprite*, 2>& fishSprites;

		//current state of the player
		std::unique_ptr<PlayerState> state;
		//current visual representation
		PlayerVisual visual;

		//current collision maps
		const std::array<Map, 2> *currentMap;

		//fishing state
		bool fishing;

		long long coins;
		//reference of the DebtHolder variable
		long long& paidDebt;

		//coins multiplier when selling fish/chests or getting stolen
		float coinsMultiplier;

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

		//hitbox color
		Pixel clr;
	};

}
