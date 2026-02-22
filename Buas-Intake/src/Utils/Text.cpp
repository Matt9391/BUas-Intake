#include <sstream>
#include <cstdio>
#include <string>
#include <vector>
#include "../../tmpl8/surface.h"
#include "../../tmpl8/template.h"
#include "../DataTypes/PrintableText.h"

#include "Text.h"

namespace Tmpl8 {

	Text::Text(Surface* fontSource) :
		font(fontSource),
		//counted manually from the font source image (not ideal)
		fontHeight(10),
		fontWidth(7)
	{}

	void Text::drawString(PrintableText text, Surface* screen) {
		if (font == nullptr) {
			printf("Font not initialized yet! Initialize it before using");
			return;
		}

		std::vector<std::string> lines = splitLines(text.text);


		//check if the text is outside the screen bounds
		if (text.pos.x + fontWidth * text.scale < 0 || text.pos.y + fontHeight * text.scale < 0 || text.pos.x > screen->GetWidth() || text.pos.y > screen->GetHeight())
			return;

		//clipping variables
		int dx = 0, dy = 0;
		int maxX = fontWidth, maxY = fontHeight;

		//clip position and size if the text is partially outside the screen
		if (text.pos.x < 0) dx = int(-text.pos.x);
		if (text.pos.x < 0) dy = int(-text.pos.y);
		if (text.pos.x + fontWidth > screen->GetWidth())  maxX = int(screen->GetWidth() - text.pos.x);
		if (text.pos.y + fontHeight > screen->GetHeight()) maxY = int(screen->GetHeight() - text.pos.y);

		//black pixel used for transparent/void pixels
		const Pixel black = 0xFF000000; //its black
		int lineCounter = 0;

		//for each line
		for (auto& line : lines) {
			int count = 0;
			//for each character in the line
			for (char character : line) {

				//get character index in the font surface
				int index = int(character) - 32;
				//get source based on character index
				Pixel* source = (*font).GetBuffer() + index * fontWidth;
				//add clipping offset
				source += dy * (*font).GetPitch();

				//set destination on screen with clipping offsets and line offset
				//get the buffer off the screen and the calculate the position based on character count and line counter
				Pixel* destination = screen->GetBuffer() + int(text.pos.x + fontWidth * text.scale * count) + (int(text.pos.y) + dy + fontHeight * text.scale * lineCounter) * screen->GetPitch();

				//draw character pixel by pixel with scaling
				//si/sj are scale iterators
				//iterate through original rows
				for (int i = dy; i < maxY; i++) {
					//for each row it iterates scale times the same row
					for (int si = 0; si < text.scale; si++) {
						//jIndex is the index of the pixel needed to be drawn
						int jIndex = 0;
						//iterate through original columns
						for (int j = dx; j < maxX * text.scale; j += text.scale) {
							//for each column it iterates scale times the same column
							for (int sj = 0; sj < text.scale; sj++) {
								//if the source pixel is not black (transparent) copy it to the screen
								if (source[jIndex] != black)
									destination[j + sj] = source[jIndex];
							}
							jIndex++;
						}
						destination += screen->GetPitch();
					}
					source += (*font).GetPitch();
				}
				count++;
			}
			lineCounter++;
		}
	}

	//split string into multiple lines based on '\n' character
	std::vector<std::string>  Text::splitLines(const std::string& text) {
		std::vector<std::string> lines;
		std::istringstream stream(text);
		std::string line;

		while (std::getline(stream, line)) {
			lines.push_back(line);
		}

		return lines;
	}

}