#include "MapHandler.h"


namespace Tmpl8 {

	MapHandler::MapHandler(){}

	int MapHandler::rows = 0;
	int MapHandler::cols = 0;

	void MapHandler::setSize(int nRows, int nCols) {
		rows = nRows;
		cols = nCols;
	}

	Map MapHandler::loadMap(std::string fileName) {
		std::ifstream mapFile("assets/map/"+ fileName);
		std::string mapLine;

		Map newMap;

		while (std::getline(mapFile, mapLine)) {
			newMap.push_back(mapLine);
		}

		return newMap;
	}

	void MapHandler::drawTile(int tx, int ty, Surface* screen, Surface *map, int x, int y, int tileSize) {

		if (x + tileSize < 0 || y + tileSize < 0 || x > screen->GetWidth() || y > screen->GetHeight())
			return;

		int dx = 0, dy = 0;
		int maxX = tileSize, maxY = tileSize;

		if (x < 0) dx = -x;
		if (y < 0) dy = -y;
		if (x + tileSize > screen->GetWidth())  maxX = screen->GetWidth() - x;
		if (y + tileSize > screen->GetHeight()) maxY = screen->GetHeight() - y;

		Pixel* source = (*map).GetBuffer() + tx * tileSize + (ty * tileSize) * (*map).GetPitch();
		source += dy * (*map).GetPitch();
		Pixel* destination = screen->GetBuffer() + x + (y + dy) *screen->GetPitch();

		for (int i = dy; i < maxY; i++) {
			for (int j = dx; j < maxX; j++) {
				destination[j] = source[j];
			}
			source += (*map).GetPitch();
			destination += screen->GetPitch();
		}
	}

	
}