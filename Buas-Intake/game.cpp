#include "game.h"
#include "surface.h"
#include "template.h"
#include <cstdio> //printf
#include <vector> 
#include <array> 
#include "MapHandler.h"
#include "Camera2D.h"
#include "Player.h"
#include <Windows.h>

namespace Tmpl8
{
	//DATATYPES:

	//void DrawTile(int tx, int ty, Surface* screen, Surface* map, int x, int y);
	std::array<Map, 2> mapsTdw;
	Map mapTdw; //Map top down	
	Map mapTdwLayer2; //Map top down	
	Surface mapTdwTileset("./assets/TopDown/map3.png");
	Camera2D camera(vec2(0,0),vec2(ScreenWidth,ScreenHeight));
	Sprite humanSprite(new Surface("./assets/TopDown/player.tga"), 40);
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
		this->ROWS = mapsTdw[0].size();
		this->COLS= std::floor((mapsTdw[0][0].size() + 1) / 4);
		MapHandler::setSize(this->ROWS, this->COLS);

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
		if (GetAsyncKeyState('A')) {
			player2.x -= 1;
		}
		if (GetAsyncKeyState('D')) {
			player2.x += 1;
		}
		if (GetAsyncKeyState('W')) {
			player2.y -= 1;
		}
		if (GetAsyncKeyState('S')) {
			player2.y += 1;
		}

		player.update(deltaTime);

		printf("Xplayer: %.2f, Xplayer2: %.2f\n", player.getPos().x, player2.x);

		camera.follow(player.getPos());

		printf("%d\n", MapHandler::isSolid(mapsTdw[1], player.getPos(), 32));

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

				//tx = mapTdwLayer2[i][j * 4] - 'a';
				//ty = mapTdwLayer2[i][j * 4 + 1] - 'a';

				//MapHandler::drawTile(tx, ty, screen, &mapTdwTileset, x, y, 32);
			}

		}

		player.draw(screen, camera.getPos());
		screen->Plot(player2.x - camera.getPos().x, player2.y - camera.getPos().y, 0xFF0000);
		screen->Plot(player2.x - camera.getPos().x -1, player2.y - camera.getPos().y, 0xFF0000);
		screen->Plot(player2.x - camera.getPos().x +1, player2.y - camera.getPos().y, 0xFF0000);
		screen->Plot(player2.x - camera.getPos().x, player2.y - camera.getPos().y - 1, 0xFF0000);
		screen->Plot(player2.x - camera.getPos().x, player2.y - camera.getPos().y + 1, 0xFF0000);
	}

	//void DrawTile(int tx, int ty, Surface* screen, Surface* map, int x, int y) {
	//	

	//	if (x >= screen->GetWidth() || y >= screen->GetHeight() || x + tileSize <= 0 || y + tileSize <= 0)
	//		return;

	//	int dx = 0, dy = 0;
	//	int maxX = tileSize, maxY = tileSize;

	//	if (x < 0) dx = -x;
	//	if (y < 0) dy = -y;
	//	if (x + tileSize > screen->GetWidth())  maxX = screen->GetWidth() - x;
	//	if (y + tileSize > screen->GetHeight()) maxY = screen->GetHeight() - y;

	//	Pixel* src = (*map).GetBuffer() + tx * tileSize + (ty * tileSize) * (*map).GetPitch();
	//	src += dy * (*map).GetPitch();
	//	Pixel* dst = screen->GetBuffer() + x + (y + dy) * screen->GetPitch();

	//	for (int i = dy; i < maxY; i++, src += (*map).GetPitch(), dst += screen->GetPitch()) {
	//		for (int j = dx; j < maxX; j++) {
	//			dst[j] = src[j];
	//		}
	//	}
	//}
};