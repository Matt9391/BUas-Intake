#include <vector>
#include "../../tmpl8/surface.h"
#include "../Utils/Text.h"
#include "../DataTypes/PrintableText.h"
#include "../DataTypes/PrintableBox.h"
#include "../GFX/Button.h"
#include "../GFX/ButtonSceneChanger.h"
#include <memory>
#include "../DataTypes/SceneType.h"

#pragma once

namespace Tmpl8 {

	class Game;

	class HUD
	{
	public:
		HUD(Text& textDrawer, Game& game);

		void drawTexts(Surface* screen, std::vector <PrintableText> texts);
		void drawBoxes(Surface* screen, std::vector <PrintableBox> boxes);
		void drawButtons(Surface* screen, std::vector <std::unique_ptr<Button>>& buttons);

	private:
		void drawBox(PrintableBox box, Surface* screen);

		Text& textDrawer;
		Game& game;
	};

};
