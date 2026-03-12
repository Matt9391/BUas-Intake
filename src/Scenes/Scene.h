#include "../DataTypes/SceneType.h"
#include "../Utils/MapHandler.h"
#include <string>
#include <vector>
#include "../DataTypes/PrintableBox.h"
#include "../DataTypes/PrintableText.h"
#include "../GFX/Button.h"
#include <memory>
#pragma once

namespace Tmpl8 {

	
	class Player;
	class Camera2D;
	class Surface;
	class Game;
	class HUD;

	//base class for scenes
	class Scene
	{
	public:
		Scene(Game& game, std::string mapName, Surface& tileset, std::string voidChar);
		virtual ~Scene() = default;

		virtual void onEnter(Player& player, Camera2D& camera, HUD& hud) = 0;
		virtual void onExit(Player& player) = 0;

		virtual void update(float dt, Camera2D& camera, Player& player, HUD& hud) = 0;

		virtual void draw(Surface* screen, Camera2D& camera, Player& player, HUD& hud) = 0;

		static void enableDebug(bool enable);

		void clearDynamicObjects();
		void clearAllObjects();

		void addText(PrintableText text);
		void addBox(PrintableBox box);
		void addTexts(std::vector <PrintableText> texts);
		void addBoxes(std::vector <PrintableBox> boxes);

		SceneType getSceneType() const;

	protected:

		void updateButtons(float dt);


		Game& game;

		SceneType type;
		static bool debug;

		MapHandler mapHandler;

		std::vector <PrintableText> staticTexts;
		std::vector <PrintableText> dynamicTexts;
		std::vector <PrintableBox> staticBoxes;
		std::vector <PrintableBox> dynamicBoxes;

		std::vector <std::unique_ptr<Button>> buttons;
	};

}
