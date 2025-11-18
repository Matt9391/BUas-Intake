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

	bool MapHandler::isSolid(const Map& map, vec2 pos, vec2 size, int tileSize) {

		int tx = pos.x / tileSize;
		int ty = pos.y / tileSize;
		int tx2 = (pos.x + size.x - 1) / tileSize;
		int ty2 = pos.y / tileSize;
		int lx = pos.x / tileSize; //it shouldnt be hardcoded, it's the size of the player hitbox
		int ly = (pos.y + size.y - 1) / tileSize;
		int lx2 = (pos.x + size.x -1) / tileSize;
		int ly2 = (pos.y + size.y -1) / tileSize;

		if (ty < 0 || ty >= map.size()) return false;
		if (tx < 0 || tx >= map[ty].size() / 4) return false;
		if (ly < 0 || ly >= map.size()) return false;
		if (lx < 0 || lx >= map[ty].size() / 4) return false;
		if (ty2 < 0 || ty2 >= map.size()) return false;
		if (tx2 < 0 || tx2 >= map[ty].size() / 4) return false;
		if (ly2 < 0 || ly2 >= map.size()) return false;
		if (lx2 < 0 || lx2 >= map[ty].size() / 4) return false;

		//printf("x: %d, y: %d | %c%c%c \n", tx,ty,map[ty][tx * 4], map[ty][tx * 4 + 1], map[ty][tx * 4 + 2]);
		return map[ty][tx * 4 + 2]   == 'X' ||
			   map[ty2][tx2 * 4 + 2] == 'X' ||
			   map[ly][lx * 4 + 2]   == 'X' ||
			   map[ly2][lx2 * 4 + 2] == 'X';
	}


	void MapHandler::drawTile(int tx, int ty, Surface* screen, Surface *map, int x, int y, int tileSize) {

		if (x + tileSize < 0 || y + tileSize < 0 || x > screen->GetWidth() || y > screen->GetHeight())
			return;

		if ((tx + 'a' == 'g') && (ty + 'a' == 'g')) //gg is a void pixel
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

		const Pixel transparent = 0xFFFF00FF; //its magenta for a reason

		for (int i = dy; i < maxY; i++) {
			for (int j = dx; j < maxX; j++) {
				if(source[j] != transparent)
					destination[j] = source[j];
			}
			source += (*map).GetPitch();
			destination += screen->GetPitch();
		}
	}

	
}