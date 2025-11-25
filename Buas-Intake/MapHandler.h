#include <string> 
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "surface.h"
#include "template.h"

#pragma once

namespace Tmpl8 {
	using Map = std::vector<std::string>;

	class InteractableObject;

	class MapHandler
	{
	public:
		MapHandler();

		static void setSize(int nRows, int nCols);

		static void loadInteractableObject(std::string fileName, int tileSize, Sprite& barSprite);

		static Map loadMap(std::string fileName);

		static bool isSolid(const Map &map, vec2 pos, vec2 size, int tileSize);

		static void drawTile(int tx, int ty, Surface* screen, Surface *map, int x, int y, int tileSize);
		
		static std::vector<InteractableObject> objects;
	private:
		static std::vector<int> parseIntList(const std::string& s);

		std::string delimiter;
		static int rows;
		static int cols;
	};

}

