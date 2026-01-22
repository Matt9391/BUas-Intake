#include "Text.h"
#include "Surface.h"
#include "template.h"
#include "MapHandler.h"
#include <sstream>

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

	void Text::printCoins(Surface* screen, vec2 pos, long long coins) {
		if (font == nullptr) {
			printf("BRO SONO NULL ANCORA EHEHEH");
			return;
		}

		std::string text;

		if (coins >= 1'000'000'000) {
			double value = coins / 1'000'000'000.0;
			char buf[32];
			snprintf(buf, sizeof(buf), "%.1fB", value);
			text = buf;
		}else if (coins >= 1'000'000) {
			double value = coins / 1'000'000.0;
			char buf[32];
			snprintf(buf, sizeof(buf), "%.1fM", value);
			text = buf;
		}else if (coins >= 1000) {
			double value = coins / 1'000.0;
			char buf[32];
			snprintf(buf, sizeof(buf), "%.1fK", value);
			text = buf;
		}
		else {
			text = std::to_string(coins);
		}

		drawString(text, screen, pos);

	}

	std::vector<std::string>  Text::splitLines(const std::string& text) {
		std::vector<std::string> lines;
		std::istringstream stream(text);
		std::string line;

		while (std::getline(stream, line)) {
			lines.push_back(line);
		}

		return lines;
	}

	void Text::drawString(std::string str, Surface* screen, vec2 pos) {
		if (font == nullptr) {
			printf("BRO SONO NULL ANCORA EHEHEH");
			return;
		} 

		std::vector<std::string> lines = splitLines(str);


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
		int lineCounter = 0;
		for (auto line : lines) {
			int count = 0;
			for (char character : line) {
				Pixel* destination = screen->GetBuffer() + int(pos.x + fontWidth * count) + (int(pos.y) + dy + fontHeight * lineCounter) * screen->GetPitch();
			
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

			lineCounter++;
		}
	}

}