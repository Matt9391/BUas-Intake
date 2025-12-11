#include "Text.h"
#include "Surface.h"
#include "template.h"
#include "MapHandler.h"

namespace Tmpl8 {

	Surface* Text::font = nullptr;
	int Text::fontHeight = 10;
	int Text::fontWidth = 7;

	Text::Text() {};

	void Text::init(Surface* fontSource) {
		font = fontSource;
	}

	void Text::print(Surface* screen) {
		if (font == nullptr) {
			printf("BRO SONO NULL ANCORA EHEHEH");
			return;
		}
		
	}

	void Text::drawString(std::string str, Surface* screen, vec2 pos) {
		if (font == nullptr) {
			printf("BRO SONO NULL ANCORA EHEHEH");
			return;
		}

		//printf("char: %c, c_index: %d, index: %d\n", character, character, index);

		if (pos.x + fontWidth < 0 || pos.y + fontHeight < 0 || pos.x > screen->GetWidth() || pos.y > screen->GetHeight())
			return;

		int dx = 0, dy = 0;
		int maxX = fontWidth, maxY = fontHeight;

		if (pos.x < 0) dx = int(-pos.x);
		if (pos.x < 0) dy = int(-pos.y);
		if (pos.x + fontWidth > screen->GetWidth())  maxX = int(screen->GetWidth() - pos.x);
		if (pos.y + fontHeight> screen->GetHeight()) maxY = int(screen->GetHeight() - pos.y);

		const Pixel black = 0xFF000000; //its black
		int count = 0;
		for (char character : str) {
			Pixel* destination = screen->GetBuffer() + int(pos.x + fontWidth * count) + (int(pos.y) + dy) * screen->GetPitch();
			
			int index = int(character) - 32;
	
			Pixel* source = (*font).GetBuffer() + index * fontWidth;
			source += dy * (*font).GetPitch();
			
			for (int i = dy; i < maxY; i++) {
				for (int j = dx; j < maxX; j++) {
					if (source[j] != black)
						destination[j] = source[j];
				}
				source += (*font).GetPitch();
				destination += screen->GetPitch();
			}
			
			count++;
		}
	}

}