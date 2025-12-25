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
	

	Surface map2DTileset("./assets/2D/seaMap.png");
	Surface mapTdwTileset("./assets/TopDown/map3.png");
	Surface fontSource("./assets/Font/fontHorizontal.png");
	Camera2D camera(vec2(0,0),vec2(ScreenWidth,ScreenHeight));
	Sprite humanSprite(new Surface("./assets/TopDown/player.tga"), 40);
	Sprite fishSprite(new Surface("./assets/2D/mainFish@0,5x.tga"), 14);
	Sprite barSprite(new Surface("./assets/TopDown/fishingBar.png"), 1);
	Sprite indxSprite(new Surface("./assets/TopDown/fishingIndx.png"), 1);
	Sprite fishesSprite(new Surface("./assets/TopDown/fishesv2.tga"), 4);
	std::array<Sprite*, 3> fishingAreaSprites = { &barSprite, &indxSprite, &fishesSprite };
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------

	Player player(humanSprite, fishSprite);
	int tileSize = 32;
	vec2 player2(ScreenWidth / 2, ScreenHeight / 2);

	bool Game::humanScene = true;

	void Game::Init()
	{	

		MapHandler::mapsTdw[0] = MapHandler::loadMap("mapTopDown.txt");
		MapHandler::mapsTdw[1] = MapHandler::loadMap("mapTopDownLayer2.txt");
		MapHandler::maps2D[0] = MapHandler::loadMap("map2D.txt");
		MapHandler::loadInteractableObject("interactableObjectList.txt", 32, fishingAreaSprites);
		this->ROWS = int(MapHandler::mapsTdw[0].size());
		this->COLS = int(std::floor((MapHandler::mapsTdw[0][0].size() + 1) / 4));
		this->ROWS2D = int(MapHandler::maps2D[0].size());
		this->COLS2D = int(std::floor((MapHandler::maps2D[0][0].size() + 1) / 4)); //div 4 perché ci sono 4 char nel txt
		camera.setWorldSize(vec2(float(this->COLS), float(this->ROWS)));
		MapHandler::setSize(this->ROWS, this->COLS);
		Text::init(&fontSource);

		printf("%d %d\n",ROWS,COLS);
		//for (int i = 0; i < ROWS; i++) {
		//	for (int j = 0; j < COLS; j++) {
		//		std::cout << mapTdw[i][j];
		//	}
		//	printf("\n");
		//}

		player.loadMap(&MapHandler::mapsTdw);
		

		
		
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
		
		if (Game::humanScene) {

			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					for (int iMap = 0; iMap < MapHandler::mapsTdw.size(); iMap++) {
						int tx = MapHandler::mapsTdw[iMap][i][j * 4] - 'a';
						int ty = MapHandler::mapsTdw[iMap][i][j * 4 + 1] - 'a';
						//printf("%c e %c\n", tx + 'a', ty + 'a');
						int x = j * tileSize - int(camera.getPos().x);
						int y = i * tileSize - int(camera.getPos().y);
						//printf("%d e %d\n", x, y);

						MapHandler::drawTile(tx, ty, screen, &mapTdwTileset, x, y, 32);
					}

				}

			}
			//for (auto object : MapHandler::objects) {
			//	(*object).drawHitBox(screen, camera.getPos());
			//}
			
			for (auto object : MapHandler::objects) {
				(*object).update(deltaTime, player);

				(*object).draw(screen, camera.getPos());

				if ((*object).intersectPlayer(player)) {
					(*object).showText(screen, camera.getPos());
					if (player.isInteracting()) {
						(*object).interact(player);
					}

				}

				//printf("stamppoo\n");
			}
		}
		else {
			for (int i = 0; i < ROWS2D; i++) {
				for (int j = 0; j < COLS2D; j++) {
					for (int iMap = 0; iMap < MapHandler::maps2D.size() -1; iMap++) {
						int tx = MapHandler::maps2D[iMap][i][j * 4] - 'a';
						int ty = MapHandler::maps2D[iMap][i][j * 4 + 1] - 'a';
						//printf("%c e %c\n", tx + 'a', ty + 'a');
						int x = j * tileSize - int(camera.getPos().x);
						int y = i * tileSize - int(camera.getPos().y);
						//printf("%d e %d\n", x, y);

						MapHandler::drawTile(tx, ty, screen, &map2DTileset, x, y, 32);
					}

				}

			}
		}

		

		player.draw(screen, camera.getPos());

		
		

		Text::print(screen);
	}

};