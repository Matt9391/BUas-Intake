#include <string> 
#include <vector>
#include <array>
#include <memory>

#include "../InteractableObjects/InteractableObject.h"
#include "../DataTypes/PrintableBox.h"

#pragma once

namespace Tmpl8 {
	//map datatype
	using Map = std::vector<std::string>;
	 
	class vec2;
	class Surface;
	class Sprite;

	class MapHandler
	{
	public:
		MapHandler(const std::string& mapName, Surface& tileset, const std::string& voidChar);

		//loads interactable objects from file, fishingSprites is only needed when loading fish areas so it's optional
		void loadInteractableObject(std::string fileName, const std::array<Sprite*, 3>* fishingSprites = nullptr);
		//creates an interactable object based on its attributes, fishingSprites and chestsSprite are only needed when creating fish areas and chests respectively so they're optional
		void createInteractableObject(int type, vec2 pos, vec2 size, const std::array<Sprite*, 3>* fishingSprites = nullptr, Sprite* chestsSprite = nullptr);

		//loads a map from file
		Map loadMap(const std::string& fileName);

		//checks if player is colliding with solid tiles in the map
		static bool isSolid(const Map &map, vec2 pos, vec2 size, int tileSize);

		//draws a single tile from the tileset to the screen
		void drawTile(int tx, int ty, Surface* screen, int x, int y);

		vec2 getTiles() const;
		const std::vector<std::unique_ptr<InteractableObject>>& getObjects() const;
		const std::array<Map, 2>& getMaps() const;
		void clearObjects();

		static const int tileSize;

		void setBoxes(vec2 cameraOffset);
		const std::vector <PrintableBox>& getBoxes() const;

	private:

		std::array<Map, 2> maps;
		vec2 tiles;
		Surface& tileset;

		std::string voidChar;

		//all interactable objects in the scene
		std::vector<std::unique_ptr<InteractableObject>> objects;
		std::vector<PrintableBox> boxes;
		//parse the file into a list of floats (attributes of the interactable object)
		static std::vector<float> parseFloatList(const std::string& s);
	};

}

