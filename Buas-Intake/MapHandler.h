#include <string> 
#include <vector>
#include <array>

#pragma once

namespace Tmpl8 {
	//map datatype
	using Map = std::vector<std::string>;
	 
	class InteractableObject;
	class vec2;
	class Surface;
	class Sprite;

	class MapHandler
	{
	public:
		MapHandler();

		//loads interactable objects from file, fishingSprites is only needed when loading fish areas so it's optional
		static void loadInteractableObject(std::string fileName, int tileSize, const std::array<Sprite*, 3>* fishingSprites = nullptr);
		//creates an interactable object based on its attributes, fishingSprites and chestsSprite are only needed when creating fish areas and chests respectively so they're optional
		static void createInteractableObject(int type, vec2 pos, vec2 size, const std::array<Sprite*, 3>* fishingSprites = nullptr, Sprite* chestsSprite = nullptr);

		//loads a map from file
		static Map loadMap(std::string fileName);

		//checks if player is colliding with solid tiles in the map
		static bool isSolid(const Map &map, vec2 pos, vec2 size, int tileSize);

		//draws a single tile from the tileset to the screen
		static void drawTile(int tx, int ty, Surface* screen, Surface *map, int x, int y, int tileSize);
		
		//all interactable objects in the scene
		static std::vector<InteractableObject*> objects;
		
		//maps and tiles info of top-down scene
		static std::array<Map, 2> mapsTdw;
		static vec2 tilesTdw;

		//maps and tiles info of 2D scene
		static std::array<Map, 2> maps2D;
		static vec2 tiles2D;
		
		//maps and tiles info of home scene
		static std::array<Map, 2> mapsHome;
		static vec2 tilesHome;

		//size of a single tile in pixels
		static const int tileSize;
		
		static Surface map2DTileset;
		static Surface mapTdwTileset;
		static Surface mapHomeTileset;

	private:
		//parse the file into a list of floats (attributes of the interactable object)
		static std::vector<float> parseFloatList(const std::string& s);
	};

}

