#include <DataTypes/SceneType.h>
#include <Utils/Text.h>
#include <Utils/functions.h>
#include <game.h>
#include <DataTypes/PrintableBox.h>
#include <DataTypes/PrintableText.h>
#include <GFX/Button.h>
#include <GFX/ButtonSceneChanger.h>
#include "HUD.h"

#include <template.h>
#include <surface.h>

#include <vector>
#include <iostream>
#include <memory>
#include <utility>

namespace Tmpl8 {

	HUD::HUD(Text& textDrawer, Game& game) :
		textDrawer(textDrawer),
		game(game)
	{}

	void HUD::drawTexts(Surface* screen, std::vector <PrintableText> texts) {
		for (auto& text : texts) {
			if (text.background) {
				
				PrintableBox b = {
					vec2(text.pos.x - 1.f * this->textDrawer.getFontSize().x * float(text.scale),
						text.pos.y - 1.f * this->textDrawer.getFontSize().y * float(text.scale)
					),
					vec2((2 + getMaxLengthLines(text.text)) * this->textDrawer.getFontSize().x * float(text.scale),
					(2 + countLines(text.text)) * this->textDrawer.getFontSize().y * float(text.scale)
					),
					0x604239
				};

				drawBox(b, screen);
			}
		}
		for (auto& text : texts) {
			this->textDrawer.drawText(text, screen);
		}
		
	}
	
	void HUD::drawBoxes(Surface* screen, std::vector <PrintableBox> boxes) {
		for (auto& box : boxes) {
			this->drawBox(box, screen);
		}
	}

	void HUD::drawButtons(Surface* screen, std::vector <std::unique_ptr<Button>>& buttons) {
		for (auto& b : buttons) {
			if (!b) continue;
			PrintableText text = b->getText();

			if (text.background) {

				PrintableBox b = {
					vec2(text.pos.x - 1.f * this->textDrawer.getFontSize().x * float(text.scale),
						text.pos.y - 1.f * this->textDrawer.getFontSize().y * float(text.scale)
					),
					vec2((2 + getMaxLengthLines(text.text)) * this->textDrawer.getFontSize().x * float(text.scale),
					(2 + countLines(text.text)) * this->textDrawer.getFontSize().y * float(text.scale)
					),
					0x805345
				};

				drawBox(b, screen);
			}
		}

		for (auto& b : buttons) {
			if (!b) continue;
			this->textDrawer.drawText(b->getText(), screen);
		}
	}

	void HUD::drawBox(PrintableBox box, Surface* screen) {
		Pixel* buffer = screen->GetBuffer(); //gets the screen buffer (array of pixels)
		int pitch = screen->GetPitch(); //pixels for each row

		vec2 pos(box.pos.x, box.pos.y);

		//whether to fill or to draw just the edge of the box
		if (box.filled) {

			for (int dy = 0; dy < box.size.y; dy++)
			{
		
				int py = int(pos.y) + dy;
				//check if it's in the screen bounds
				if (py < 0 || py >= screen->GetHeight()) continue;

				for (int dx = 0; dx < box.size.x; dx++)
				{
					int px = int(pos.x) + dx;
					//check if it's in the screen bounds
					if (px < 0 || px >= screen->GetWidth()) continue;

					buffer[px + py * pitch] = box.clr;
				}
			}

		}
		else {
			for (int dy = 0; dy < box.size.y; dy++)
			{
				int py = int(pos.y) + dy;
				//check if it's in the screen bounds
				if (py < 0 || py >= screen->GetHeight()) continue;

				if (dy == 0 || dy == box.size.y - 1) {
					for (int dx = 0; dx < box.size.x; dx++)
					{
						int px = int(pos.x) + dx;
						//check if it's in the screen bounds
						if (px < 0 || px >= screen->GetWidth()) continue;

						buffer[px + py * pitch] = box.clr;
					}
				}

				//left edge
				int px0 = int(pos.x);
				//right edge
				int px1 = int(pos.x + box.size.x - 1);

				//check if it's in the screen bounds
				if (!(px0 < 0 || px0 >= screen->GetWidth()))
					buffer[px0 + py * pitch] = box.clr;
				if (!(px1 < 0 || px1 >= screen->GetWidth()))
					buffer[px1 + py * pitch] = box.clr;
			}
		}
	}

}
