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
	HomeScene Game::homeScene;

	Scene* Game::currentScene = nullptr;

	void Game::Init()
	{	
		MapHandler::mapsTdw[0] = MapHandler::loadMap("mapTopDown.txt");
		MapHandler::mapsTdw[1] = MapHandler::loadMap("mapTopDownLayer2.txt");
		MapHandler::maps2D[0] = MapHandler::loadMap("map2D.txt");
		MapHandler::maps2D[1] = MapHandler::loadMap("map2DLayer2.txt");
		MapHandler::mapsHome[0] = MapHandler::loadMap("mapHome.txt");
		MapHandler::mapsHome[1] = MapHandler::loadMap("mapHomeLayer2.txt");

		MapHandler::tilesTdw = vec2(
								float(std::floor((MapHandler::mapsTdw[0][0].size() + 1) / 4)),
							    float(MapHandler::mapsTdw[0].size())
								);

		MapHandler::tiles2D = vec2(
								float(std::floor((MapHandler::maps2D[0][0].size() + 1) / 4)), //div 4 perché ci sono 4 char nel txt
								float(MapHandler::maps2D[0].size())
								);
		
		MapHandler::tilesHome = vec2(
								float(std::floor((MapHandler::mapsHome[0][0].size() + 1) / 4)), //div 4 perché ci sono 4 char nel txt
								float(MapHandler::mapsHome[0].size())
								);

		this->currentScene = nullptr;
		this->currentScene = &this->homeScene;
		 
		Game::changeScene(SceneType::SceneHome);

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
	}

	void Game::changeScene(SceneType nextScene) {
		if (nextScene == SceneType::SceneHome) {
			currentScene->onExit();
			currentScene = &homeScene;
			currentScene->onEnter(player, camera);
		}else if (nextScene == SceneType::SceneHuman) {
			currentScene->onExit();
			currentScene = &humanScene;
			currentScene->onEnter(player,camera);
		}else if (nextScene == SceneType::SceneFish) {
			currentScene->onExit();
			currentScene = &fishScene;
			currentScene->onEnter(player, camera);
		}
	}

};