#include "HumanScene.h"
#include "FishScene.h"
#include "HomeScene.h"
#include <unordered_map>
#include <utility>

#pragma once

namespace Tmpl8 {

	class Surface;
	class Game
	{
	public:
		void SetTarget( Surface* surface ) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick( float deltaTime );
		void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
		void KeyUp( int key ) { /* implement if you want to handle keys */ }
		void KeyDown( int key ) { /* implement if you want to handle keys */ }

		static void changeScene(SceneType nextScene);

		static void checkAchievements(Player& player);

		void drawAchievement(long long coins);



	private:
		void loadGameSaves();
		std::pair<std::string, double> Game::getMap(std::string& str);
		
		static HumanScene humanScene;
		static FishScene fishScene;
		static HomeScene homeScene;
		static Scene* currentScene;

		static bool showAchievement;
		static long long achievedMoney;
		static std::unordered_map<long long, bool> achievements;

		static std::unordered_map<std::string, double> gameSaves;

		float timeElapsedAchievement;
		float timerAchievement;

		Surface* screen;
	};
	 
}; // namespace Tmpl8