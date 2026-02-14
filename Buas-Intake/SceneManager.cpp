#include "SceneManager.h"
#include "game.h"

namespace Tmpl8 {

	SceneManager::SceneManager(Game& game): 
		nextScene(SceneType::SceneHome),
		pendingScene(false)
	{
		this->humanScene = std::make_unique<HumanScene>(game);
		this->homeScene = std::make_unique<HomeScene>(game);
		this->fishScene = std::make_unique<FishScene>(game);

		this->currentScene = this->homeScene.get();
	}

	void SceneManager::changeScene(Player& player, Camera2D& camera) {
		
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
			default:
				break;
		}

		currentScene->onEnter(player, camera);
		this->pendingScene = false;

	}

	void SceneManager::setPendingScene(SceneType nextScene) {
		this->pendingScene = true;
		this->nextScene = nextScene;
	}

}