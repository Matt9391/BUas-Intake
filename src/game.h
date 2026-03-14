#pragma once

#include <DataTypes/SceneType.h>
#include <DataTypes/PrintableText.h>
#include <Gameplay/Player.h>
#include <Gameplay/Camera2D.h>
#include <GFX/HUD.h>
#include <Scenes/HumanScene.h>
#include <Scenes/FishScene.h>
#include <Scenes/HomeScene.h>
#include <Utils/SaveSystem.h>
#include <Utils/SceneManager.h>
#include <Utils/Text.h>
#include <Utils/AudioManager.h>

#include <template.h>

#include <unordered_map>
#include <utility>

namespace Tmpl8 {

	class Surface;

	class Game
	{
	public:
		Game();
		void SetTarget( Surface* surface ) { screen = surface; }
		void Init();
		void Shutdown();
		bool isRunning();
		void Tick( float deltaTime );
		void MouseUp( int button ) { if (button == 1) this->mousePressed = false; }
		void MouseDown(int button) { if (button == 1) this->mousePressed = true; }
		void MouseMove(int x, int y) { this->mousePos = vec2(float(x), float(y)); }
		void KeyUp( int key ) { /* implement if you want to handle keys */ }
		void KeyDown( int key ) { /* implement if you want to handle keys */ }
		void setDebug(bool debug);

		vec2 getMousePos() const;
		bool isMousePressed() const;

		vec2 getFontSize() const;
		
		AudioManager& getAudioManager();

		//check and unlock achievements based on player coins
		void checkAchievements(Player& player);

		//draw achievement alert
		PrintableText getAchievementText();

		//set the next pending scene
		void setPendingScene(SceneType nextScene);
		
		bool showAchievement;

	private:
		bool running;

		//achievement variables
		long long achievedMoney;
		//achievement dictionary
		std::unordered_map<long long, bool> achievements;

		float timeElapsedAchievement;
		float timerAchievement;

		Surface* screen;
		
		//variable to enable debug mode
		bool debug;

		SaveSystem saveSystem;

		Player player;
		Camera2D camera;

		HUD hud;
		Text textDrawer;

		SceneManager sceneManager;

		AudioManager audioManager;

		bool mousePressed;
		vec2 mousePos;
	};
	 
}; // namespace Tmpl8