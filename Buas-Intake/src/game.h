#include "./Scenes/HumanScene.h"
#include "./Scenes/FishScene.h"
#include "./Scenes/HomeScene.h"
#include "./Utils/SaveSystem.h"
#include "./Utils/SceneManager.h"
#include "./Utils/Text.h"
#include "./Gameplay/Player.h"
#include "./Gameplay/Camera2D.h"
#include "./GFX/HUD.h"
#include <unordered_map>
#include <utility>

#pragma once

namespace Tmpl8 {

	class Surface;

	class Game
	{
	public:
		Game();
		void SetTarget( Surface* surface ) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick( float deltaTime );
		void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
		void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
		void KeyUp( int key ) { /* implement if you want to handle keys */ }
		void KeyDown( int key ) { /* implement if you want to handle keys */ }

	
		//check and unlock achievements based on player coins
		void checkAchievements(Player& player);

		//draw achievement alert
		void drawAchievement(long long coins);

		//set the next pending scene
		void setPendingScene(SceneType nextScene);
		
	private:

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
		SceneManager sceneManager;

		Player player;
		Camera2D camera;

		HUD hud;
		Text textDrawer;
	};
	 
}; // namespace Tmpl8