#include "MapHandler.h"
#include "InteractableObject.h"
#include "IncomeMultiplier.h"
#include "StaminaShop.h"
#include "FishArea.h"
#include "Seller.h"
#include "Gate.h"
#include "Chest.h"
#include "Randomize.h"


namespace Tmpl8 {

	MapHandler::MapHandler(){}

	vec2 MapHandler::tilesTdw = vec2(0, 0);
	vec2 MapHandler::tiles2D = vec2(0, 0);
	
	const int MapHandler::tileSize = 32;

	std::vector<InteractableObject*> MapHandler::objects;

	std::array<Map, 2> MapHandler::mapsTdw;
	std::array<Map, 2> MapHandler::maps2D;
	
	Surface MapHandler::map2DTileset("./assets/2D/seaMap.png");
	Surface MapHandler::mapTdwTileset("./assets/TopDown/map3.png");

	void MapHandler::loadInteractableObject(std::string fileName, int tileSize, const std::array<Sprite*, 3>* fishingSprites) {
		std::ifstream objFile("assets/map/" + fileName);
		std::string objLine;

		std::getline(objFile, objLine);

		MapHandler::objects.clear();

		while (std::getline(objFile, objLine)) {
			std::vector<float> data = parseFloatList(objLine);
			//datas:
			//type
			//nCol
			//nRow
			//nTileWidth
			//nTileHeight
			//printf("%d %d %d %d %d\n", data[0], data[1], data[2], data[3], data[4]);
			vec2 pos(float(data[1] * tileSize),float(data[2] * tileSize));
			vec2 size(float(data[3] * tileSize), float(data[4] * tileSize));
			printf("   %.2f %.2f %.2f %.2f\n", pos.x, pos.y, size.x, size.y);

			MapHandler::createInteractableObject(int(data[0]), pos, size, fishingSprites);
		}

		
	}

	void MapHandler::createInteractableObject(int type, vec2 pos, vec2 size, const std::array<Sprite*, 3>* fishingSprites, Sprite* chestsSprite) {
		switch (type)
		{
		case 1:
			objects.push_back(new FishArea(type, pos, size, *fishingSprites));
			break;
		case 2:
			objects.push_back(new IncomeMultiplier(type, pos, size));
			break;
		case 3:
			objects.push_back(new StaminaShop(type, pos, size));
			break;
		case 4:
			objects.push_back(new Seller(type, pos, size));
			break;
		case 5:
			objects.push_back(new Gate(type, pos, size));
			break;
		case 6:
			objects.push_back(new Chest(type, pos, size, chestsSprite, Randomize::randomInt(0, 3)));
			break;
		default:
			objects.push_back(new InteractableObject(type, pos, size));
			break;
		}
	}

	std::vector<float> MapHandler::parseFloatList(const std::string& s)
	{
		std::vector<float> out;
		std::string str;

		for (char c : s)
		{
			if (c == ',')
			{
				out.push_back(std::stof(str));
				str.clear();
			}
			else
			{
				str += c;
			}
		}

		// ultimo numero
		if (!str.empty())
			out.push_back(std::stof(str));

		return out;
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
		int tx  = int(pos.x / tileSize);
		int ty  = int(pos.y / tileSize);
		int tx2 = int((pos.x + size.x - 1) / tileSize);
		int ty2 = int(pos.y / tileSize);
		int lx  = int(pos.x / tileSize); //it shouldnt be hardcoded, it's the size of the player hitbox
		int ly  = int((pos.y + size.y - 1) / tileSize);
		int lx2 = int((pos.x + size.x -1) / tileSize);
		int ly2 = int((pos.y + size.y - 1) / tileSize);
		

		if (ty < 0 || ty >= map.size()) return false;
		if (tx < 0 || tx > map[ty].size() / 4) return false;
		if (ly < 0 || ly >= map.size()) return false;
		if (lx < 0 || lx > map[ty].size() / 4) return false;
		if (ty2 < 0 || ty2 >= map.size()) return false;
		if (tx2 < 0 || tx2 > map[ty].size() / 4) return false;
		if (ly2 < 0 || ly2 >= map.size()) return false;
		if (lx2 < 0 || lx2 > map[ty].size() / 4) return false;

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