#include <DataTypes/PrintableText.h>
#include <DataTypes/SceneType.h>
#include <Gameplay/Camera2D.h>
#include <Gameplay/Player.h>
#include <GFX/resources.h>
#include <InteractableObjects/DebtHolder.h>
#include <InteractableObjects/IncomeMultiplier.h>
#include <InteractableObjects/StaminaShop.h>
#include <Scenes/Scene.h>
#include <Utils/AudioManager.h>
#include <Utils/MapHandler.h>
#include <Utils/SaveSystem.h>
#include <Utils/SceneManager.h>
#include <Utils/Text.h>
#include <Utils/functions.h>

#include <game.h>
#include <template.h>

#include <Windows.h>
#include <array>
#include <cmath>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	Game::Game() :
		running(true),
		showAchievement(false),
		achievedMoney(0),
		timeElapsedAchievement(0.f),
		timerAchievement(3000.f),
		debug(false),
		player(humanSprite, fishSprites, DebtHolder::paidDebt),
		camera(vec2(0, 0), vec2(ScreenWidth, ScreenHeight)),
		textDrawer(&fontSource),
		hud(textDrawer, *this),
		sceneManager(*this),
		screen(nullptr),
		mousePressed(false),
		mousePos(0)
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
			{20'000'000, false},
			{100'000'000, false},
			{250'000'000, false},
			{500'000'000, false},
			{750'000'000, false},
			{1'000'000'000, false}
		};

		//load game saves from file
		this->saveSystem.loadGameSaves(achievements);

		//set debug mode
		this->debug = false;

		//start in home scene
		this->sceneManager.setPendingScene(SceneType::SceneHome);
		this->sceneManager.changeScene(player, camera, hud);

		this->audioManager.init();
		
		//load datas
		player.loadData(this->saveSystem.getGameSaves());
		
		DebtHolder::loadPaidDebt(long long(this->saveSystem.getDataSave("paidDebt")));
		IncomeMultiplier::loadPrice(float(this->saveSystem.getDataSave("incomeMultiplierPrice")));
		StaminaShop::loadPrice(float(this->saveSystem.getDataSave("staminaPrice")));
		
		//set debug mode for scenes and player based on game debug variable
		this->setDebug(this->debug);
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
		Scene* currentScene = this->sceneManager.getCurrentScene();
		//update and draw current scene
		currentScene->update(deltaTime, camera, player, hud);
		currentScene->draw(screen, camera, player, hud);

		//if achievement is being shown update timer and draw it
		if (showAchievement) {
			this->timeElapsedAchievement += deltaTime;
			if (this->timeElapsedAchievement > this->timerAchievement) {
				this->timeElapsedAchievement = 0;
				showAchievement = false;
			}
		}

		//printf("x: %f, y: %f\n", this->mousePos.x, this->mousePos.y);

		if (this->sceneManager.hasPendingScene()) {
			this->sceneManager.changeScene(player, camera, hud);
		}
	
		//if ctrl + T is pressed reset game saves and reload data
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState('T')) {
			if (currentScene->getSceneType() == SceneType::SceneHome) {
				this->saveSystem.resetGameSaves(this->achievements);

				player.loadData(this->saveSystem.getGameSaves());
				IncomeMultiplier::loadPrice(float(this->saveSystem.getDataSave("incomeMultiplierPrice")));
				StaminaShop::loadPrice(float(this->saveSystem.getDataSave("staminaPrice")));
				DebtHolder::loadPaidDebt(long long(this->saveSystem.getDataSave("paidDebt")));
			}
		}
	}


	

	void Game::checkAchievements(Player& player) {
		//check if player coins exceed achievement thresholds and unlock them
		long long playerCoins = player.getCoins();
		long long achieved = 0;
		for (auto& [money, unlocked] : achievements)
		{
			if (unlocked) continue;

			if (playerCoins >= money)
			{
				unlocked = true;
				achieved = money;
			}
		}

		//if any achievement unlocked set variables to show achievement alert
		if (achieved > 0) {
			showAchievement = true;
			achievedMoney = achieved;
		}
			
	}

	PrintableText Game::getAchievementText() {
		 return PrintableText{ "You made your first "+ formatCoins(this->achievedMoney), vec2(ScreenWidth / 2.f - 200.f,MapHandler::tileSize * 5.5f),2, false};
	}

	void Game::setPendingScene(SceneType nextScene) {
		if (nextScene == SceneType::SceneQuit) {
			this->running = false;
			return;
		}
		this->sceneManager.setPendingScene(nextScene);
	}

	vec2 Game::getMousePos() const {
		return this->mousePos;
	}

	bool Game::isMousePressed() const {
		return this->mousePressed;
	}

	vec2 Game::getFontSize() const {
		return this->textDrawer.getFontSize();
	}

	bool Game::isRunning() {
		return this->running;
	}

	void Game::setDebug(bool debug){
		this->debug = debug; 
		Scene::enableDebug(this->debug);
		player.enableDebug(this->debug);
	};

	AudioManager& Game::getAudioManager() {
		return this->audioManager;
	}
};