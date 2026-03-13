#include "../game.h"

#include "SceneManager.h"
#include <memory>
#include "../DataTypes/SceneType.h"
#include "../Gameplay/Camera2D.h"
#include "../Gameplay/Player.h"
#include "../Scenes/FishScene.h"
#include "../Scenes/HomeScene.h"
#include "../Scenes/HumanScene.h"
#include "../Scenes/WinScene.h"
#include "../Scenes/HowToScene.h"
#include "../Scenes/SettingsScene.h"
#include "../GFX/resources.h"
#include "../Scenes/Scene.h"
#include "../GFX/HUD.h"

namespace Tmpl8 {

	SceneManager::SceneManager(Game& game): 
		nextScene(SceneType::SceneHome),
		pendingScene(false)
	{
		this->humanScene = std::make_unique<HumanScene>(game, "mapTopDown", mapTdwTileset, "gg");
		this->homeScene = std::make_unique<HomeScene>(game, "mapHome", mapTdwTileset, "gg");
		this->fishScene = std::make_unique<FishScene>(game, "map2D", map2DTileset, "aj");
		this->winScene = std::make_unique<WinScene>(game, "mapWin", mapTdwTileset, "gg");
		this->howToScene = std::make_unique<HowToScene>(game, "mapHowTo", mapTdwTileset, "gg");
		this->settingsScene = std::make_unique<SettingsScene>(game, "mapSettings", mapTdwTileset, "gg");

		this->currentScene = this->homeScene.get();
	}

	void SceneManager::changeScene(Player& player, Camera2D& camera, HUD& hud) {
		
		currentScene->onExit(player);

		switch (this->nextScene)
		{
			case SceneType::SceneHome:
				currentScene = homeScene.get();
				break;
			case SceneType::SceneHuman:
				currentScene = humanScene.get();
				break;
			case SceneType::SceneFish:
				currentScene = fishScene.get();
				break;
			case SceneType::SceneWin:
				currentScene = winScene.get();
				break;
			case SceneType::SceneHowToPlay:
				currentScene = howToScene.get();
				break;
			case SceneType::SceneSettings:
				currentScene = settingsScene.get();
				break;
			default:
				break;
		}

		currentScene->onEnter(player, camera, hud);
		this->pendingScene = false;

	}

	void SceneManager::setPendingScene(SceneType nextScene) {
		this->pendingScene = true;
		this->nextScene = nextScene;
	}

	Scene* SceneManager::getCurrentScene() const { return currentScene; }
	bool SceneManager::hasPendingScene() const { return pendingScene; }
}