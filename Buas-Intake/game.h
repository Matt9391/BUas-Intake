#include "HumanScene.h"
#include "FishScene.h"
#include "HomeScene.h"
#include "SaveSystem.h"
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

		//change the current scene into the next scene
		static void changeScene(SceneType nextScene);

		//check and unlock achievements based on player coins
		static void checkAchievements(Player& player);

		//draw achievement alert
		void drawAchievement(long long coins);

		
		//check if in home scene
		static bool isHomeScene; 
	private:
		
		//scenes
		static HumanScene humanScene;
		static FishScene fishScene;
		static HomeScene homeScene;
		//pointer to the current scene
		static Scene* currentScene;

		//achievement variables
		static bool showAchievement;
		static long long achievedMoney;
		//achievement dictionary
		static std::unordered_map<long long, bool> achievements;

		float timeElapsedAchievement;
		float timerAchievement;

		Surface* screen;
		
		//variable to enable debug mode
		bool debug;

		SaveSystem saveSystem;
	};
	 
}; // namespace Tmpl8