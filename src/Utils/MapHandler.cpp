#include <DataTypes/PrintableBox.h>
#include <InteractableObjects/Chest.h>
#include <InteractableObjects/DebtHolder.h>
#include <InteractableObjects/FishArea.h>
#include <InteractableObjects/Gate.h>
#include <InteractableObjects/IncomeMultiplier.h>
#include <InteractableObjects/InteractableObject.h>
#include <InteractableObjects/Seller.h>
#include <InteractableObjects/StaminaShop.h>
#include <Utils/Randomize.h>
#include <Utils/MapHandler.h>

#include <surface.h>
#include <template.h>

#include <array>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace Tmpl8 {

	const int MapHandler::tileSize = 32;

	MapHandler::MapHandler(const std::string& mapName, Surface& tileset, const std::string& voidChar) :
		tileset(tileset),
		voidChar(voidChar)
	{
		this->maps[0] = loadMap(mapName + ".txt");
		this->maps[1] = loadMap(mapName + "Layer2.txt");
		//calulate number of tiles -- divide by 4 because there are 4 chars in the txt per tile
		this->tiles = vec2(
			float(std::floor((this->maps[0][0].size() + 1) / 4)),
			float(this->maps[0].size())
		);

		
	}

	void MapHandler::setBoxes(vec2 cameraOffset) {
		this->boxes.clear();
		//draw map tiles
		for (int i = 0; i < tiles.y; i++) {
			for (int j = 0; j < tiles.x; j++) {
				//just the 2 layer
				char tx = maps[1][i][j * 4];
				char ty = maps[1][i][j * 4 + 1];

				if ((tx == 'g' && ty == 'g') || (tx == 'a' && ty == 'j'))
					continue;
				//calculate tile position based on camera position
				int x = j * MapHandler::tileSize - int(cameraOffset.x);
				int y = i * MapHandler::tileSize - int(cameraOffset.y);

				this->boxes.emplace_back(PrintableBox{ vec2(float(x),float(y)), vec2(tileSize), 0xFF0000, false, false });

			}

		}
	}

	const std::vector <PrintableBox>& MapHandler::getBoxes() const {
		return this->boxes;
	}

	//loads interactable objects from file.
	//fishingSprites is only needed when loading fish areas so it's optional
	void MapHandler::loadInteractableObject(std::string fileName, const std::array<Sprite*, 3>* fishingSprites) {
		std::ifstream objFile("assets/map/" + fileName);
		std::string objLine;

		if (!objFile.is_open())
		{
			printf("Cannot open objects file\n");
			return;
		}

		std::getline(objFile, objLine);

		this->objects.clear();
		
		//read each line of the file
		while (std::getline(objFile, objLine)) {
			//for each line get the data
			std::vector<float> data = parseFloatList(objLine);
			//datas: type - nCol - nRow - nTileWidth - nTileHeight
			
			vec2 pos(float(data[1] * tileSize),float(data[2] * tileSize));
			vec2 size(float(data[3] * tileSize), float(data[4] * tileSize));
			
			createInteractableObject(int(data[0]), pos, size, fishingSprites);
		}

		
	}

	//chestsSprite is only needed when creating a chest so it's optional
	void MapHandler::createInteractableObject(int type, vec2 pos, vec2 size, const std::array<Sprite*, 3>* fishingSprites, Sprite* chestsSprite) {
		//create the interactable object based on its type
		switch (type)
		{
		case 1:
			objects.push_back(std::make_unique <FishArea>(type, pos, size, *fishingSprites));
			break;
		case 2:
			objects.push_back(std::make_unique <IncomeMultiplier>(type, pos, size));
			break;
		case 3:
			objects.push_back(std::make_unique <StaminaShop>(type, pos, size));
			break;
		case 4:
			objects.push_back(std::make_unique <Seller>(type, pos, size));
			break;
		case 5:
			objects.push_back(std::make_unique <Gate>(type, pos, size));
			break;
		case 6:
			if (chestsSprite == nullptr)
				break;
			objects.push_back(std::make_unique <Chest>(type, pos, size, chestsSprite, Randomize::randomInt(0, 3)));
			break;
		case 7:
			objects.push_back(std::make_unique <DebtHolder>(type, pos, size));
			break;
		default:
			objects.push_back(std::make_unique <InteractableObject>(type, pos, size));
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
	Map MapHandler::loadMap(const std::string& fileName) {
		std::ifstream mapFile("assets/map/"+ fileName);
		std::string mapLine;

		Map newMap;

		if (!mapFile.is_open())
		{
			printf("Cannot open map file\n");
			return newMap;
		}


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


	void MapHandler::drawTile(int tx, int ty, Surface* screen, int x, int y) {
		 
		//check if the tile is outside the screen
		if (x + tileSize < 0 || y + tileSize < 0 || x > screen->GetWidth() || y > screen->GetHeight())
			return; 

		//check for void pixel, I chose 'gg' and 'aj' as void pixel based on the tilesetGuide
		if ((tx + 'a' == this->voidChar[0]) && (ty + 'a' == this->voidChar[1]))
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
		Pixel* source = tileset.GetBuffer() + tx * tileSize + (ty * tileSize) * tileset.GetPitch();
		//add the clipping offsets
		source += dy * tileset.GetPitch();
		//set destination on screen with clipping offsets
		Pixel* destination = screen->GetBuffer() + x + (y + dy) * screen->GetPitch();

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
			source += tileset.GetPitch();
			destination += screen->GetPitch();
		}
	}

	vec2 MapHandler::getTiles() const {
		return this->tiles;
	}
	
	const std::vector<std::unique_ptr<InteractableObject>>& MapHandler::getObjects() const {
		return this->objects;
	}

	const std::array<Map, 2>& MapHandler::getMaps() const {
		return this->maps;
	}

	void MapHandler::clearObjects() {
		this->objects.clear();
	}
}