#include <vector>
#include "../../tmpl8/template.h"
#include "../../tmpl8/surface.h"
#include "../Utils/Text.h"
#include "../DataTypes/PrintableBox.h"
#include "../DataTypes/PrintableText.h"

#include "HUD.h"

namespace Tmpl8 {

	HUD::HUD(Text& textDrawer) :
		textDrawer(textDrawer)
	{}

	void HUD::clearTextsAndBoxes() {
		this->texts.clear();
		this->boxes.clear();
	}

	void HUD::addText(const PrintableText text) {
		this->texts.push_back(text);
	}

	void HUD::addTexts(std::vector <PrintableText> texts) {
		for (auto& text : texts) {
			this->texts.push_back(text);
		}
	}
	
	void HUD::addBox(PrintableBox box) {
		this->boxes.push_back(box);
	}
	
	void HUD::addBoxes(std::vector <PrintableBox> boxes) {
		for (auto& box : boxes) {
			this->boxes.push_back(box);
		}
	}

	void HUD::drawTexts(Surface* screen) {
		for (auto& text : this->texts) {
			this->textDrawer.drawString(text, screen);
		}

		//double clear to avoid problems
		this->texts.clear();
	}
	
	void HUD::drawBoxes(Surface* screen) {
		for (auto& box : this->boxes) {
			this->drawBox(box, screen);
		}

		//double clear to avoid problems
		this->boxes.clear();
	}

	void HUD::drawBox(PrintableBox box, Surface* screen) {
		Pixel* buffer = screen->GetBuffer(); //gets the screen buffer (array of pixels)
		int pitch = screen->GetPitch(); //pixels for each row
		//set position of drawing
		vec2 pos(box.pos.x, box.pos.y);

		for (int dy = 0; dy < box.size.y; dy++)
		{
			//py = pixel y
			int py = int(pos.y) + dy;
			//check if it's in the screen bounds
			if (py < 0 || py >= screen->GetHeight()) continue;

			for (int dx = 0; dx < box.size.x; dx++)
			{
				//px = pixel x
				int px = int(pos.x) + dx;
				//check if it's in the screen bounds
				if (px < 0 || px >= screen->GetWidth()) continue;

				//set the screen pixel (px+py*pitch) to the color
				buffer[px + py * pitch] = box.clr;
			}
		}
	}
}
