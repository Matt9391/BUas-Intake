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
#include <Windows.h>

namespace Tmpl8
{
	//DATATYPES:

	//void DrawTile(int tx, int ty, Surface* screen, Surface* map, int x, int y);
	std::array<Map, 2> mapsTdw;
	Map mapTdw; //Map top down	
	Map mapTdwLayer2; //Map top down
	Surface mapTdwTileset("./assets/TopDown/map3.png");
	Surface fontSource("./assets/fontHorizontal2.png");
	Camera2D camera(vec2(0,0),vec2(ScreenWidth,ScreenHeight));
	Sprite humanSprite(new Surface("./assets/TopDown/player.tga"), 40);
	Sprite barSprite(new Surface("./assets/TopDown/fishingBar.png"), 1);
	Sprite indxSprite(new Surface("./assets/TopDown/fishingIndx.png"), 1);
	Sprite fishesSprite(new Surface("./assets/TopDown/fishes.tga"), 4);
	std::array<Sprite*, 3> fishingAreaSprites = { &barSprite, &indxSprite, &fishesSprite };
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------

	Player player(humanSprite, &mapsTdw);
	int tileSize = 32;
	vec2 player2(ScreenWidth / 2, ScreenHeight / 2);

	void Game::Init()
	{	

		mapsTdw[0] = MapHandler::loadMap("mapTopDown.txt");
		mapsTdw [1] = MapHandler::loadMap("mapTopDownLayer2.txt");
		MapHandler::loadInteractableObject("interactableObjectList.txt", 32, fishingAreaSprites);
		this->ROWS = mapsTdw[0].size();
		this->COLS = std::floor((mapsTdw[0][0].size() + 1) / 4);
		camera.setWorldSize(vec2(this->COLS, this->ROWS));
		MapHandler::setSize(this->ROWS, this->COLS);
		Text::init(&fontSource);

		printf("%d %d\n",ROWS,COLS);
		//for (int i = 0; i < ROWS; i++) {
		//	for (int j = 0; j < COLS; j++) {
		//		std::cout << mapTdw[i][j];
		//	}
		//	printf("\n");
		//}


		
		
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
		player.update(deltaTime);

		//printf("collide: %d interacting: %d \n", obj.intersectPlayer(player), player.isInteracting());
		
		
		camera.follow(player.getPos());

		//printf("%d\n", MapHandler::isSolid(mapsTdw[1], player.getPos(), 32));

		screen->Clear(0);
		
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				for (int iMap = 0; iMap < mapsTdw.size(); iMap++) {
					int tx = mapsTdw[iMap][i][j * 4] - 'a';
					int ty = mapsTdw[iMap][i][j * 4 + 1] - 'a';
					//printf("%c e %c\n", tx + 'a', ty + 'a');
					int x = j * tileSize - camera.getPos().x;
					int y = i * tileSize - camera.getPos().y;
					//printf("%d e %d\n", x, y);

					MapHandler::drawTile(tx, ty, screen, &mapTdwTileset, x, y, 32);
				}

			}

		}

		for (auto object : MapHandler::objects) {
			(*object).update(deltaTime);

			if ((*object).intersectPlayer(player)) {
				(*object).showText(screen, camera.getPos());
				if (player.isInteracting()) {
					(*object).interact(player);
				}

			}
			
			(*object).draw(screen, camera.getPos());
			//printf("stamppoo\n");
		}

		player.draw(screen, camera.getPos());

		Text::print(screen);
	}

};