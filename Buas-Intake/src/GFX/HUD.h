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

		void clearTexts();

		void addText(PrintableText text);
		void addTexts(std::vector <PrintableText> texts);
		void addBox(PrintableBox box);

		void draw(Surface* screen);
	private:std::vector <PrintableText> texts;
		
		std::vector <PrintableBox>  boxes;

		Text& textDrawer;
	};

};
