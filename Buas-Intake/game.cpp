#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <vector> 
#include "MapHandler.h"

namespace Tmpl8
{
	//DATATYPES:

	//void DrawTile(int tx, int ty, Surface* screen, Surface* map, int x, int y);

	Map mapTdw; //Map top down
	Surface mapTdwTileset("./assets/TopDown/map.png");
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------


	void Game::Init()
	{
		mapTdw = MapHandler::loadMap("mapTopDown.txt");

		this->ROWS = mapTdw.size();         
		this->COLS= mapTdw[0].size() / 3 - 1;
		printf("%d\n", COLS);
		//for (int i = 0; i < ROWS; i++) {
		//	for (int j = 0; j < COLS; j++) {
		//		std::cout << mapTdw[i][j];
		//	}
		//	printf("\n");
		//}

		int tileSize = 32;

		screen->Clear(0);
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				int tx = mapTdw[i][j * 4] - 'a';
				int ty = mapTdw[i][j * 4 + 1] - 'a';
				printf("%c e %c\n", tx + 'a', ty + 'a');
				int x = j * tileSize;
				int y = i * tileSize;
				printf("%d e %d\n", x , y );

				MapHandler::drawTile(tx, ty, screen, mapTdwTileset, x, y, 32);
			}

		}
		
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