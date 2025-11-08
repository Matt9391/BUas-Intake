#include "game.h"
#include "surface.h"
#include <cstdio> //printf

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------

	Sprite fish(new Surface("assets/2D/angryFish.tga"), 10);
	int frame = 0;
	int timer = 100;
	int te = 0;
	void Game::Init()
	{
		fish.SetFrame(0);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------

	void Game::Shutdown()
	{
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		te += deltaTime;
		if (te > timer) {
			frame++;
			te = 0;
		}
		frame = frame % 10;
		fish.SetFrame(frame);
		screen->Clear(0);
		fish.Draw(screen, 10, 10);
	}
};