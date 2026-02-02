#include "game.h"
#include "./tmpl8/template.h"
#include <cstdio> //printf
#include <vector> 
#include <string> 
#include <iostream>
#include <fstream>
#include <array> 
#include "MapHandler.h"
#include "Camera2D.h"
#include "Player.h"
#include "Text.h"
#include "resources.h"
#include "IncomeMultiplier.h"
#include "StaminaShop.h"

#include <Windows.h>
#include <cmath>
#include <unordered_map>
#include <utility>
#include "Fish.h"
#include "FishScene.h"
#include "HomeScene.h"
#include "HumanScene.h"
#include "Scene.h"

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------

	
	Camera2D camera(vec2(0, 0), vec2(ScreenWidth, ScreenHeight));

	Player player(humanSprite, fishSprite);

	//scenes
	HumanScene Game::humanScene;
	FishScene Game::fishScene;
	HomeScene Game::homeScene;

	Scene* Game::currentScene = nullptr;

	bool Game::showAchievement = false;
	long long Game::achievedMoney = 0;
	std::unordered_map<long long, bool> Game::achievements;
	std::unordered_map<std::string, double> Game::gameSaves;

	bool Game::isHomeScene = true;

	void Game::Init()
	{
		//initialize achievements
		this->achievements = {
			{1'000, false},
			{10'000, false},
			{50'000, false},
			{100'000, false},
			{200'000, false},
			{500'000, false},
			{1'000'000, false},
			{1'500'000, false},
			{2'000'000, false},
			{5'000'000, false},
		};

		//load game saves from file
		Game::loadGameSaves();

		
		//set achievement timer variables
		this->timerAchievement = 3000.f;
		this->timeElapsedAchievement = 0.f;

		//set debug mode
		this->debug = false;

		//load maps from files
		MapHandler::mapsTdw[0] = MapHandler::loadMap("mapTopDown.txt");
		MapHandler::mapsTdw[1] = MapHandler::loadMap("mapTopDownLayer2.txt");
		MapHandler::maps2D[0] = MapHandler::loadMap("map2D.txt");
		MapHandler::maps2D[1] = MapHandler::loadMap("map2DLayer2.txt");
		MapHandler::mapsHome[0] = MapHandler::loadMap("mapHome.txt");
		MapHandler::mapsHome[1] = MapHandler::loadMap("mapHomeLayer2.txt");

		//calulate number of tiles in each map
		//divide by 4 because there are 4 chars in the txt
		MapHandler::tilesTdw = vec2(
			float(std::floor((MapHandler::mapsTdw[0][0].size() + 1) / 4)),
			float(MapHandler::mapsTdw[0].size())
		);

		MapHandler::tiles2D = vec2(
			float(std::floor((MapHandler::maps2D[0][0].size() + 1) / 4)), 
			float(MapHandler::maps2D[0].size())
		);

		MapHandler::tilesHome = vec2(
			float(std::floor((MapHandler::mapsHome[0][0].size() + 1) / 4)),
			float(MapHandler::mapsHome[0].size())
		);

		this->currentScene = nullptr;
		this->currentScene = &this->homeScene;

		//start in home scene
		Game::changeScene(SceneType::SceneHome);

		//initialize text system
		Text::init(&fontSource);
		
		//load datas
		player.loadData(Game::gameSaves);
		
		IncomeMultiplier::loadPrice(float(Game::getDataSave("incomeMultiplierPrice")));
		StaminaShop::loadPrice(float(Game::getDataSave("staminaPrice")));

		//set debug mode for scenes and player based on game debug variable
		Scene::enableDebug(this->debug);
		player.enableDebug(this->debug);
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------

	void Game::Shutdown()
	{
		//save game on exit
		this->saveGame();
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		//update and draw current scene
		this->currentScene->update(deltaTime, camera, player);
		this->currentScene->draw(screen, camera, player);
		
		//if achievement is being shown update timer and draw it
		if (showAchievement) {
			this->timeElapsedAchievement += deltaTime;
			drawAchievement(achievedMoney);
			if (this->timeElapsedAchievement > this->timerAchievement) {
				this->timeElapsedAchievement = 0;
				showAchievement = false;
			}
		}

	
		//if ctrl + T is pressed reset game saves and reload data
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('T')) {
			if (Game::isHomeScene) {
				this->resetGameSaves();

				player.loadData(Game::gameSaves);
				IncomeMultiplier::loadPrice(float(Game::getDataSave("incomeMultiplierPrice")));
				StaminaShop::loadPrice(float(Game::getDataSave("staminaPrice")));
			}
		}
	}


	void Game::saveGame() {
		//update game data into game saves dictionary
		gameSaves["coins"] = double(player.getCoins());

		//clean fish counts
		gameSaves["fish_common"] = 0;
		gameSaves["fish_rare"] = 0;
		gameSaves["fish_epic"] = 0;
		gameSaves["fish_legendary"] = 0;

		//set fish counts
		for (auto& fish : player.getFishes()) {
			if(fish.rarity == FishRarity::COMMON)
				gameSaves["fish_common"] += 1;
			if(fish.rarity == FishRarity::RARE)
				gameSaves["fish_rare"] += 1;
			if(fish.rarity == FishRarity::EPIC)
				gameSaves["fish_epic"] += 1;
			if(fish.rarity == FishRarity::LEGENDARY)
				gameSaves["fish_legendary"] += 1;
		}
		
		//clean chest counts
		gameSaves["chest0"] = 0;
		gameSaves["chest1"] = 0;
		gameSaves["chest2"] = 0;
		gameSaves["chest3"] = 0;

		//set chest counts
		for (auto& chest : player.getChests()) {
			if (chest.type == 0)
				gameSaves["chest0"] += 1;
			if (chest.type == 1)
				gameSaves["chest1"] += 1;
			if (chest.type == 2)
				gameSaves["chest2"] += 1;
			if (chest.type == 3)
				gameSaves["chest3"] += 1;
		}

		gameSaves["incomeMultiplier"] = player.getMultiplier();
		gameSaves["incomeMultiplierPrice"] = IncomeMultiplier::getPrice();
		gameSaves["stamina"] = player.getStamina();
		gameSaves["staminaPrice"] = StaminaShop::getPrice();
		
		//check last achievement achieved
		long long coinsAchieved = 0;
		for (auto& pair : this->achievements) {
			if (pair.second)
				coinsAchieved = pair.first;
		}

		gameSaves["lastAchievement"] = double(coinsAchieved);

		//write game saves to file
		std::ofstream outFile("assets/gameSaves/gameSave.txt");

		for (auto &pair : gameSaves) {
			outFile << pair.first << ":" << pair.second << "\n";
		}


		outFile.close();
	}

	double Game::getDataSave(const std::string& key) {
		return gameSaves[key];
	}

	void Game::resetGameSaves() {
		//load default game saves from file
		std::ifstream objFile("assets/gameSaves/defaultGameSave.txt");
		std::string line;
		std::unordered_map<std::string, double> defaultGameSaves;
		//coins
		//fish common - rare - epic - legendary -> chest 0-1-2-3 -> stamina
		//income multiplier price - income multiplier - stamina price
		while (std::getline(objFile, line)) {
			std::pair<std::string, std::string> data = getMap(line);
			defaultGameSaves[data.first] = std::stod(data.second);
		}

		objFile.close();

		//overwrite current game saves with default ones
		gameSaves = defaultGameSaves;

		//reset achievements
		for (auto& pair : this->achievements) {
			pair.second = false;
		}
	}

	void Game::loadGameSaves() {
		std::ifstream objFile("assets/gameSaves/gameSave.txt");
		std::string line;
		
		//coins
		//fish common - rare - epic - legendary -> chest 0-1-2-3 -> stamina
		//income multiplier price - income multiplier - stamina price
		
		//load game saves from reading file
		while (std::getline(objFile, line)) {
			std::pair<std::string, std::string> data = getMap(line);
			gameSaves[data.first] = std::stod(data.second);
		}

		//set achievements based on last achievement saved
		for (auto& pair : this->achievements) {
			if (gameSaves["lastAchievement"] >= pair.first) {
				pair.second = true;
			}
		}

		objFile.close();
		
	}

	//key:value dictionary parser
	std::pair<std::string, std::string> Game::getMap(const std::string& str) {
		std::string key = "";
		bool keyDone = false;
		std::string value = "";

		//split string into key and value based on ':'
		for (int i = 0; i < str.length(); i++) {
			if (str[i] != ':' && !keyDone) {
				key += str[i];
			}
			else if (str[i] == ':') {
				keyDone = true;
			}else if(keyDone) {
				value += str[i];
			}

		}

		return {key,value};
	}

	void Game::checkAchievements(Player& player) {
		//check if player coins exceed achievement thresholds and unlock them
		long long playerCoins = player.getCoins();
		long long achieved = 0;
		for (auto& achieve : achievements) {
			if (achieve.second)
				continue;
			if (playerCoins > achieve.first){
				achieve.second = true;
				achieved = achieve.first;
			}
		}

		//if any achievement unlocked set variables to show achievement alert
		if (achieved > 0) {
			showAchievement = true;
			achievedMoney = achieved;
		}
			
	}

	void Game::drawAchievement(long long coins) {
		Text::drawString("You made your first ", this->screen, vec2(ScreenWidth / 2.f - 200.f,MapHandler::tileSize * 5.5f),2);
		Text::drawCoins(this->screen, vec2(ScreenWidth / 2.f + 70.f, MapHandler::tileSize * 5.5f), coins,2);
	}

	void Game::changeScene(SceneType nextScene) {
		if (nextScene == SceneType::SceneHome) {
			currentScene->onExit(player);
			currentScene = &homeScene;
			currentScene->onEnter(player, camera);
			isHomeScene = true;
		}else if (nextScene == SceneType::SceneHuman) {
			currentScene->onExit(player);
			currentScene = &humanScene;
			currentScene->onEnter(player,camera);
			isHomeScene = false;
		}else if (nextScene == SceneType::SceneFish) {
			currentScene->onExit(player);
			currentScene = &fishScene;
			currentScene->onEnter(player, camera);
			isHomeScene = false;
		}
	}

};