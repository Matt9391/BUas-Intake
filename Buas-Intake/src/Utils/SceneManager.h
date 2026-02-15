#include "../Scenes/HumanScene.h"
#include "../Scenes/FishScene.h"
#include "../Scenes/HomeScene.h"
#include "../Scenes/Scene.h"
#include <memory>

#pragma once
namespace Tmpl8 {

	class Player;
	class Camera;
	class Game;

	class SceneManager
	{
	public:
		SceneManager(Game& game);

		//change the current scene into the next scene
		void changeScene(Player& player, Camera2D& camera);

		//set the next pending scene
		void setPendingScene(SceneType nextScene);
		
		Scene* currentScene;
		bool pendingScene;
	private:
		SceneType nextScene;

		//scenes
		std::unique_ptr<HumanScene> humanScene;
		std::unique_ptr<FishScene> fishScene;
		std::unique_ptr<HomeScene> homeScene;
		//pointer to the current scene
	};

}

