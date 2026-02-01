#include "MapHandler.h"
#include "InteractableObject.h"
#include "IncomeMultiplier.h"
#include "StaminaShop.h"
#include "FishArea.h"
#include "Seller.h"
#include "Gate.h"
#include "Chest.h"
#include "Randomize.h"
#include <array>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include "tmpl8/surface.h"
#include "tmpl8/template.h"


namespace Tmpl8 {

	MapHandler::MapHandler(){}

	//set default number tiles of each map
	vec2 MapHandler::tilesTdw = vec2(0, 0);
	vec2 MapHandler::tiles2D = vec2(0, 0);
	vec2 MapHandler::tilesHome = vec2(0, 0);
	
	//set default tile size in pixels
	const int MapHandler::tileSize = 32;

	//initialize vector and arrays
	std::vector<InteractableObject*> MapHandler::objects;

	std::array<Map, 2> MapHandler::mapsTdw;
	std::array<Map, 2> MapHandler::maps2D;
	std::array<Map, 2> MapHandler::mapsHome;
	
	//load assets
	Surface MapHandler::map2DTileset("./assets/2D/seaMap.png");
	//they share the same tileset
	Surface MapHandler::mapTdwTileset("./assets/TopDown/mapV4.png");
	Surface MapHandler::mapHomeTileset("./assets/TopDown/mapV4.png");

	//loads interactable objects from file.
	//fishingSprites is only needed when loading fish areas so it's optional
	void MapHandler::loadInteractableObject(std::string fileName, int tileSize, const std::array<Sprite*, 3>* fishingSprites) {
		std::ifstream objFile("assets/map/" + fileName);
		std::string objLine;

		std::getline(objFile, objLine);

		MapHandler::objects.clear();
		
		//read each line of the file
		while (std::getline(objFile, objLine)) {
			//for each line get the data
			std::vector<float> data = parseFloatList(objLine);
			//datas: type - nCol - nRow - nTileWidth - nTileHeight
			
			vec2 pos(float(data[1] * tileSize),float(data[2] * tileSize));
			vec2 size(float(data[3] * tileSize), float(data[4] * tileSize));
			
			MapHandler::createInteractableObject(int(data[0]), pos, size, fishingSprites);
		}

		
	}

	void MapHandler::createInteractableObject(int type, vec2 pos, vec2 size, const std::array<Sprite*, 3>* fishingSprites, Sprite* chestsSprite) {
		//create the interactable object based on its type
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

		//scroll through the string and saves values as floats
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

		//since the last value is not followed by a comma, we need to add it manually
		if (!str.empty())
			out.push_back(std::stof(str));

		return out;
	}


	//load char map from file
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
		//get the tile coordinates of the 4 corners of the player hitbox
		//top-left
		int tx  = int(pos.x / tileSize);
		int ty  = int(pos.y / tileSize);
		//top-right
		int tx2 = int((pos.x + size.x - 1) / tileSize);
		int ty2 = int(pos.y / tileSize);
		//bottom-left
		int lx  = int(pos.x / tileSize);
		int ly  = int((pos.y + size.y - 1) / tileSize);
		//bottom-right
		int lx2 = int((pos.x + size.x -1) / tileSize);
		int ly2 = int((pos.y + size.y - 1) / tileSize);
		
		//check if the tile coordinates are valid, if not it cannot be solid
		if (ty < 0 || ty >= map.size()) return false;
		if (tx < 0 || tx > map[ty].size() / 4) return false;
		if (ly < 0 || ly >= map.size()) return false;
		if (lx < 0 || lx > map[ty].size() / 4) return false;
		if (ty2 < 0 || ty2 >= map.size()) return false;
		if (tx2 < 0 || tx2 > map[ty].size() / 4) return false;
		if (ly2 < 0 || ly2 >= map.size()) return false;
		if (lx2 < 0 || lx2 > map[ty].size() / 4) return false;

		//check whether any of the 4 tiles is solid
		return map[ty][tx * 4 + 2]   == 'X' ||
			   map[ty2][tx2 * 4 + 2] == 'X' ||
			   map[ly][lx * 4 + 2]   == 'X' ||
			   map[ly2][lx2 * 4 + 2] == 'X';
	}


	void MapHandler::drawTile(int tx, int ty, Surface* screen, Surface *map, int x, int y, int tileSize) {
		 
		//check if the tile is outside the screen
		if (x + tileSize < 0 || y + tileSize < 0 || x > screen->GetWidth() || y > screen->GetHeight())
			return; 

		//check for void pixel, I choose 'gg' as void pixel
		if ((tx + 'a' == 'g') && (ty + 'a' == 'g'))
			return;

		//clip position and size if the tile is partially outside the screen
		int dx = 0, dy = 0;
		int maxX = tileSize, maxY = tileSize;

		//set clipping values
		if (x < 0) dx = -x;
		if (y < 0) dy = -y;
		if (x + tileSize > screen->GetWidth())  maxX = screen->GetWidth() - x;
		if (y + tileSize > screen->GetHeight()) maxY = screen->GetHeight() - y;

		//get pointers to the source tile and destination on screen
		//we get the buffer of the map then we add x and y offsets times the tilesize and pitch
		Pixel* source = (*map).GetBuffer() + tx * tileSize + (ty * tileSize) * (*map).GetPitch();
		//then we add the clipping offsets
		source += dy * (*map).GetPitch();
		//set destination on screen with clipping offsets
		Pixel* destination = screen->GetBuffer() + x + (y + dy) *screen->GetPitch();

		//"transparent" pixel value, actually its magenta because it's easy to visualize in photoshop
		const Pixel transparent = 0xFFFF00FF;

		//for each pixel in the tile area
		for (int i = dy; i < maxY; i++) {
			for (int j = dx; j < maxX; j++) {
				//if the pixel is not "transparent" copy it to the screen
				if(source[j] != transparent)
					destination[j] = source[j];
			}
			//then move to the next row
			source += (*map).GetPitch();
			destination += screen->GetPitch();
		}
	}

	
}