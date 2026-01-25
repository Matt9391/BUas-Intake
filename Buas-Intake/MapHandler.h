#include <string> 
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <array>
#include "./tmpl8/surface.h"
#include "./tmpl8/template.h"

#pragma once

namespace Tmpl8 {
	using Map = std::vector<std::string>;
	 
	class InteractableObject;

	class MapHandler
	{
	public:
		MapHandler();

		static void loadInteractableObject(std::string fileName, int tileSize, const std::array<Sprite*, 3>* fishingSprites = nullptr);
		static void createInteractableObject(int type, vec2 pos, vec2 size, const std::array<Sprite*, 3>* fishingSprites = nullptr, Sprite* chestsSprite = nullptr);

		static Map loadMap(std::string fileName);

		static bool isSolid(const Map &map, vec2 pos, vec2 size, int tileSize);

		static void drawTile(int tx, int ty, Surface* screen, Surface *map, int x, int y, int tileSize);
		
		static std::vector<InteractableObject*> objects;
		static std::array<Map, 2> mapsTdw;
		static vec2 tilesTdw;

		static std::array<Map, 2> maps2D;
		static vec2 tiles2D;
		
		static std::array<Map, 2> mapsHome;
		static vec2 tilesHome;

		static const int tileSize;

		
		static Surface map2DTileset;
		static Surface mapTdwTileset;
		static Surface mapHomeTileset;

	private:
		static std::vector<float> parseFloatList(const std::string& s);

		std::string delimiter;
	};

}

