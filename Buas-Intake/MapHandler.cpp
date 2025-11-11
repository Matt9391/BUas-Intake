#include "MapHandler.h"


namespace Tmpl8 {

	MapHandler::MapHandler():
		delimiter(" ")
		{ }
	Map MapHandler::loadMap(std::string fileName) {
		std::ifstream mapFile("assets/map/"+ fileName);
		std::string mapLine;

		Map newMap;

		while (std::getline(mapFile, mapLine)) {
			newMap.push_back(mapLine);
		}

		return newMap;
	}

	void MapHandler::drawTile(int tx, int ty, Surface* screen, Surface map, int x, int y, int tileSize) {

		//Pixel* source = map.GetBuffer() + x + y * map.GetPitch();
		//Pixel* destination = screen->GetBuffer() + x + y * screen->GetPitch();

		//for (int i = 0; i < tileSize; i++) {
			//for (int j = 0; j < tileSize; j++) {
				//destination[j] = source[j];
			//}
			//source += map.GetPitch();
			//destination += screen->GetPitch();
		//}
	}

	
};