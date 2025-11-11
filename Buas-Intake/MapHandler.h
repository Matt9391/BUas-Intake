#include <string> 
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "surface.h"

#pragma once

namespace Tmpl8 {
	using Map = std::vector<std::string>;

	class MapHandler
	{
	public:
		MapHandler();

		static void setSize(int nRows, int nCols);

		static Map loadMap(std::string fileName);

		static void drawTile(int tx, int ty, Surface* screen, Surface *map, int x, int y, int tileSize);

	private:
		std::string delimiter;
		static int rows;
		static int cols;
	};

}

