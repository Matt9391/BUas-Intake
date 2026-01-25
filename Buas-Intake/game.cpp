#include "game.h"
#include "./tmpl8/surface.h"
#include "./tmpl8/template.h"
#include <cstdio> //printf
#include <vector> 
#include <string> 
#include <iostream>
#include <fstream>
#include <cstring> 
#include <array> 
#include "MapHandler.h"
#include "Camera2D.h"
#include "Player.h"
#include "Text.h"
#include "InteractableObject.h"
#include "resources.h"
#include "IncomeMultiplier.h"
#include "StaminaShop.h"

#include <Windows.h>

namespace Tmpl8
{
	//DATATYPES:

	//void DrawTile(int tx, int ty, Surface* screen, Surface* map, int x, int y);




	Camera2D camera(vec2(0, 0), vec2(ScreenWidth, ScreenHeight));

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------

	Player player(humanSprite, fishSprite);
	int tileSize = 32;
	vec2 player2(ScreenWidth / 2, ScreenHeight / 2);

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


		Game::loadGameSaves();

		for (const auto& pair : Game::gameSaves) {
			std::cout << pair.first << ": " << pair.second << "\n";
		} 

		this->timerAchievement = 3000.f;
		this->timeElapsedAchievement = 0.f;
		this->debug = false;

		

		for (auto& pair : this->achievements) {
			std::cout << pair.first << ": " << pair.second << "\n";
		}

		MapHandler::mapsTdw[0] = MapHandler::loadMap("mapTopDown.txt");
		MapHandler::mapsTdw[1] = MapHandler::loadMap("mapTopDownLayer2.txt");
		MapHandler::maps2D[0] = MapHandler::loadMap("map2D.txt");
		MapHandler::maps2D[1] = MapHandler::loadMap("map2DLayer2.txt");
		MapHandler::mapsHome[0] = MapHandler::loadMap("mapHome.txt");
		MapHandler::mapsHome[1] = MapHandler::loadMap("mapHomeLayer2.txt");

		MapHandler::tilesTdw = vec2(
			float(std::floor((MapHandler::mapsTdw[0][0].size() + 1) / 4)),
			float(MapHandler::mapsTdw[0].size())
		);

		MapHandler::tiles2D = vec2(
			float(std::floor((MapHandler::maps2D[0][0].size() + 1) / 4)), //div 4 perché ci sono 4 char nel txt
			float(MapHandler::maps2D[0].size())
		);

		MapHandler::tilesHome = vec2(
			float(std::floor((MapHandler::mapsHome[0][0].size() + 1) / 4)), //div 4 perché ci sono 4 char nel txt
			float(MapHandler::mapsHome[0].size())
		);

		this->currentScene = nullptr;
		this->currentScene = &this->homeScene;

		Game::changeScene(SceneType::SceneHome);

		Text::init(&fontSource);
		
		player.loadData(Game::gameSaves);
		
		IncomeMultiplier::loadPrice(float(Game::getDataSave("incomeMultiplierPrice")));
		StaminaShop::loadPrice(float(Game::getDataSave("staminaPrice")));
		//printf("DDDDDDDDDDD %f ADDDNN %f\n", Game::getDataSave("incomeMultiplierPrice"), Game::gameSaves["incomeMultiplierPrice"]);

		Scene::enableDebug(this->debug);
		player.enableDebug(this->debug);
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------

	void Game::Shutdown()
	{
		this->saveGame();
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		this->currentScene->update(deltaTime, camera, player);
		this->currentScene->draw(screen, camera, player);
		
		if (showAchievement) {
			this->timeElapsedAchievement += deltaTime;
			drawAchievement(achievedMoney);
			if (this->timeElapsedAchievement > this->timerAchievement) {
				this->timeElapsedAchievement = 0;
				showAchievement = false;
			}
		}

	

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
		gameSaves["coins"] = double(player.getCoins());

		gameSaves["fish_common"] = 0;
		gameSaves["fish_rare"] = 0;
		gameSaves["fish_epic"] = 0;
		gameSaves["fish_legendary"] = 0;

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
		
		gameSaves["chest0"] = 0;
		gameSaves["chest1"] = 0;
		gameSaves["chest2"] = 0;
		gameSaves["chest3"] = 0;

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
		
		long long coinsAchieved = 0;
		for (auto& pair : this->achievements) {
			if (pair.second)
				coinsAchieved = pair.first;
		}

		gameSaves["lastAchievement"] = double(coinsAchieved);

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

		gameSaves = defaultGameSaves;

		for (auto& pair : this->achievements) {
			pair.second = false;
		}

		/*std::ofstream outFile("assets/gameSaves/gameSave.txt");

		for (auto& pair : defaultGameSaves) {
			outFile << pair.first << ":" << pair.second << "\n";
		}

		outFile.close();*/

	}

	void Game::loadGameSaves() {
		std::ifstream objFile("assets/gameSaves/gameSave.txt");
		std::string line;
		
		//coins
		//fish common - rare - epic - legendary -> chest 0-1-2-3 -> stamina
		//income multiplier price - income multiplier - stamina price
		while (std::getline(objFile, line)) {
			std::pair<std::string, std::string> data = getMap(line);
			gameSaves[data.first] = std::stod(data.second);
		}

		for (auto& pair : this->achievements) {
			if (gameSaves["lastAchievement"] >= pair.first) {
				pair.second = true;
			}
		}

		objFile.close();
		
	}

	std::pair<std::string, std::string> Game::getMap(const std::string& str) {
		std::string key = "";
		bool keyDone = false;
		std::string value = "";

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
		return { key,value};
	}

	void Game::checkAchievements(Player& player) {
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
		if (achieved > 0) {
			showAchievement = true;
			achievedMoney = achieved;
		}
			
	}

	void Game::drawAchievement(long long coins) {
		Text::drawStringScaled("You made your first ", this->screen, vec2(ScreenWidth / 2.f - 200.f,MapHandler::tileSize * 2.f),2);
		Text::drawCoinsScaled(this->screen, vec2(ScreenWidth / 2.f + 70.f, MapHandler::tileSize * 2.f), coins,2);
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