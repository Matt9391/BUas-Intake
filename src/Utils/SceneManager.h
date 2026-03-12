#include "../DataTypes/SceneType.h"
#include "../Scenes/FishScene.h"
#include "../Scenes/HomeScene.h"
#include "../Scenes/HumanScene.h"
#include "../Scenes/WinScene.h"
#include "../Scenes/HowToScene.h"
#include "../Scenes/SettingsScene.h"
#include "../Scenes/Scene.h"
#include <memory>

#pragma once
namespace Tmpl8 {

	class Player;
	class Camera2D;
	class Game;
	class HUD;

	class SceneManager
	{
	public:
		SceneManager(Game& game);

		//change the current scene into the next scene
		void changeScene(Player& player, Camera2D& camera, HUD& hud);

		//set the next pending scene
		void setPendingScene(SceneType nextScene);
		
		Scene* getCurrentScene() const;
		bool hasPendingScene() const;
		
	private:

		//pointer to the current scene
		Scene* currentScene;
		bool pendingScene;

		SceneType nextScene;

		//scenes
		std::unique_ptr<HumanScene> humanScene;
		std::unique_ptr<FishScene> fishScene;
		std::unique_ptr<HomeScene> homeScene;
		std::unique_ptr<WinScene> winScene;
		std::unique_ptr<HowToScene> howToScene;
		std::unique_ptr<SettingsScene> settingsScene;
	};

}

