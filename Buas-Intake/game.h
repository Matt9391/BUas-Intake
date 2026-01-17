#include "HumanScene.h"
#include "FishScene.h"
#include "HomeScene.h"

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

	private:
		static HumanScene humanScene;
		static FishScene fishScene;
		static HomeScene homeScene;
		static Scene* currentScene;

		Surface* screen;
	};
	 
}; // namespace Tmpl8