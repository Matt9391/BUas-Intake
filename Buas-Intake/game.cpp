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
#include "SaveSystem.h"

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


	bool Game::showAchievement = false;
	long long Game::achievedMoney = 0;
	std::unordered_map<long long, bool> Game::achievements;

	bool Game::isHomeScene = true;

	Game::Game() :
		humanScene(*this),
		fishScene(*this),
		homeScene(*this),
		currentScene(nullptr),
		pendingScene(false),
		nextScene(SceneType::SceneHome),
		timeElapsedAchievement(0.f),
		timerAchievement(0.f),
		debug(false)
	{}

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
		this->saveSystem.loadGameSaves(achievements);

		
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
		this->changeScene(SceneType::SceneHome);

		//initialize text system
		Text::init(&fontSource);
		
		//load datas
		player.loadData(this->saveSystem.getGameSaves());
		
		IncomeMultiplier::loadPrice(float(this->saveSystem.getDataSave("incomeMultiplierPrice")));
		StaminaShop::loadPrice(float(this->saveSystem.getDataSave("staminaPrice")));

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
		this->saveSystem.saveGame(player, this->achievements);
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

		if (this->pendingScene) {
			this->changeScene(this->nextScene);
		}
	
		//if ctrl + T is pressed reset game saves and reload data
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('T')) {
			if (Game::isHomeScene) {
				this->saveSystem.resetGameSaves(this->achievements);

				player.loadData(this->saveSystem.getGameSaves());
				IncomeMultiplier::loadPrice(float(this->saveSystem.getDataSave("incomeMultiplierPrice")));
				StaminaShop::loadPrice(float(this->saveSystem.getDataSave("staminaPrice")));
			}
		}
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
			this->pendingScene = false;
			isHomeScene = true;
		}else if (nextScene == SceneType::SceneHuman) {
			currentScene->onExit(player);
			currentScene = &humanScene;
			currentScene->onEnter(player,camera);
			this->pendingScene = false;
			isHomeScene = false;
		}else if (nextScene == SceneType::SceneFish) {
			currentScene->onExit(player);
			currentScene = &fishScene;
			currentScene->onEnter(player, camera);
			this->pendingScene = false;
			isHomeScene = false;
		}
	}

	void Game::setPendingScene(SceneType nextScene) {
		this->pendingScene = true;
		this->nextScene = nextScene;
	}

};