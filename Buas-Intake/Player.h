#include "template.h"
#include "surface.h"
#include <array>
#include <vector>
#include "MapHandler.h"
#include "PlayerState.h"
#include "PlayerVisual.h"
#include "Fish.h"
#pragma once

namespace Tmpl8 {

	class Player
	{
	public:

		Player(Sprite& humanSprite, std::array<Map, 2>* currentMap);

		void update(float dt);
		
		void move(float dt);
		
		void handleInput();

		void draw(Surface* screen, vec2 cameraOffset);

		void clearFishes();

		vec2 getPos();
		vec2 getDir();
		vec2 getSize();
		char getInput();
		bool isInteracting();
		bool isFishing();
		long long getCoins();
		std::vector<Fish> getFishes();

		void setInteracting(bool state);
		void setFishing(bool state);
		void setPos(const vec2& pos);
		void setDir(const vec2& dir);
		void setState(int state);
		void setInput(const char& input);
		void setCoins(long long coins);
		void addCoins(int coins); //I belive that a reduce coins is useless
		void addFish(Fish fish);

		void setAnimRange(int first, int last);

	private:
		void showHitbox(Surface* screen, vec2 cameraOffset);

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

		vec2 dir;
		Sprite &humanSprite;

		PlayerState* state;
		PlayerVisual visual;

		std::array<Map, 2> *currentMap;
		//Sprite &fishSprite;

		bool fishing;

		long long coins;

		std::vector<Fish> fishInventory;

	};

}
