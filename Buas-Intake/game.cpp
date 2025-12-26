#include "game.h"
#include "surface.h"
#include "template.h"
#include <cstdio> //printf
#include <vector> 
#include <array> 
#include "MapHandler.h"
#include "Camera2D.h"
#include "Player.h"
#include "Text.h"
#include "InteractableObject.h"
#include "resources.h"

#include <Windows.h>

namespace Tmpl8
{
	//DATATYPES:

	//void DrawTile(int tx, int ty, Surface* screen, Surface* map, int x, int y);
	

	
	
	Camera2D camera(vec2(0,0),vec2(ScreenWidth,ScreenHeight));
	
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------

	Player player(humanSprite, fishSprite);
	int tileSize = 32;
	vec2 player2(ScreenWidth / 2, ScreenHeight / 2);

	HumanScene Game::humanScene;
	FishScene Game::fishScene;
	Scene* Game::currentScene = nullptr;

	void Game::Init()
	{	
		MapHandler::mapsTdw[0] = MapHandler::loadMap("mapTopDown.txt");
		MapHandler::mapsTdw[1] = MapHandler::loadMap("mapTopDownLayer2.txt");
		MapHandler::maps2D[0] = MapHandler::loadMap("map2D.txt");

		MapHandler::tilesTdw = vec2(
								int(std::floor((MapHandler::mapsTdw[0][0].size() + 1) / 4)),
							    int(MapHandler::mapsTdw[0].size())
								);

		MapHandler::tiles2D = vec2(
								int(std::floor((MapHandler::maps2D[0][0].size() + 1) / 4)), //div 4 perché ci sono 4 char nel txt
								int(MapHandler::maps2D[0].size())
								);

		this->currentScene = nullptr;
		this->currentScene = &this->humanScene;

		Game::changeScene(0);

		Text::init(&fontSource);
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
		this->currentScene->update(deltaTime, camera, player);
		this->currentScene->draw(screen, camera, player);
		

		Text::print(screen);
	}

	void Game::changeScene(int nScene) {
		if (nScene == 0) {
			currentScene->onExit();
			currentScene = &humanScene;
			currentScene->onEnter(player,camera);
		}else if (nScene == 1) {
			currentScene->onExit();
			currentScene = &fishScene;
			currentScene->onEnter(player, camera);
		}
	}

};