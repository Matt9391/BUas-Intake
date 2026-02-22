#include <vector>
#include "../../tmpl8/surface.h"
#include "../Utils/Text.h"
#include "../DataTypes/PrintableText.h"
#include "../DataTypes/PrintableBox.h"

#pragma once

namespace Tmpl8 {


	class HUD
	{
	public:
		HUD(Text& textDrawer);

		void clearTextsAndBoxes();

		void addText(PrintableText text);
		void addTexts(std::vector <PrintableText> texts);
		void addBox(PrintableBox box);
		void addBoxes(std::vector <PrintableBox> boxes);

		void drawTexts(Surface* screen);
		void drawBoxes(Surface* screen);
	private:
		void drawBox(PrintableBox box, Surface* screen);
		
		std::vector <PrintableText> texts;
		std::vector <PrintableBox>  boxes;

		Text& textDrawer;
	};

};
