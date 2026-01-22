#include "game.h"
#include "surface.h"
#include "template.h"
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
	long long Game::achievedMoney = 0.f;
	std::unordered_map<long long, bool> Game::achievements;
	std::unordered_map<std::string, double> Game::gameSaves;

	bool Game::isHomeScene = true;

	void Game::Init()
	{
		Game::loadGameSaves();

		for (const auto& pair : Game::gameSaves) {
			std::cout << pair.first << ": " << pair.second << "\n";
		}

		this->timerAchievement = 3000.f;
		this->timeElapsedAchievement = 0.f;

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
		
		IncomeMultiplier::loadPrice(Game::getDataSave("incomeMultiplierPrice"));
		StaminaShop::loadPrice(Game::getDataSave("staminaPrice"));
		printf("DDDDDDDDDDD %f ADDDNN %f\n", Game::getDataSave("incomeMultiplierPrice"), Game::gameSaves["incomeMultiplierPrice"]);

	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------

	void Game::Shutdown()
	{
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

		if (GetAsyncKeyState('P')) {
			Game::changeScene(SceneType::SceneHome);
		}
	}


	//void Game::loadGameSaves() {
	//	std::ifstream objFile("assets/gameSaves/gameSave.txt");
	//	std::string line;

	//	std::getline(objFile, line); //coins
	//	std::pair<std::string, std::string> data = getMap(line);
	//	
	//	gameSaves[data.first] = std::stoll(data.second);

	//	for (int i = 0; i < 9; i++) {
	//		std::getline(objFile, line); //fish common - rare - epic - legendary -> chest 0-1-2-3 -> stamina
	//		data = getMap(line);

	//		gameSaves[data.first] = std::stoi(data.second);
	//	}

	//	for (int i = 0; i < 3; i++) {
	//		std::getline(objFile, line); //income multiplier price - income multiplier - stamina price
	//		data = getMap(line);

	//		gameSaves[data.first] = std::stof(data.second);
	//	}
	//	
	//}

	double Game::getDataSave(const std::string& key) {
		return gameSaves[key];
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
		Text::drawString("You made your first ", this->screen, vec2(ScreenWidth / 2.f - 96,MapHandler::tileSize * 2));
		Text::printCoins(this->screen, vec2(ScreenWidth / 2.f + 40, MapHandler::tileSize * 2), coins);
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