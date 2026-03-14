#include <DataTypes/PrintableText.h>
#include <Utils/Text.h>

#include <surface.h>
#include <template.h>

#include <cstdio>
#include <sstream>
#include <string>
#include <vector>

namespace Tmpl8 {

	Text::Text(Surface* fontSource) :
		font(fontSource),
		//counted manually from the font source image (not ideal)
		fontHeight(10),
		fontWidth(7)
	{}

	void Text::drawText(const PrintableText& text, Surface* screen) {
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
		vec2 fontSize = vec2(float(fontWidth), float(fontHeight));
		//clip position and size if the text is partially outside the screen
		if (text.pos.x < 0) dx = int(-text.pos.x);
		if (text.pos.y < 0) dy = int(-text.pos.y);
		if (text.pos.x + fontWidth > screen->GetWidth())  fontSize.x = float(screen->GetWidth() - text.pos.x);
		if (text.pos.y + fontHeight > screen->GetHeight()) fontSize.y = float(screen->GetHeight() - text.pos.y);

		
		int lineCounter = 0;

		//for each line
		for (auto& line : lines) {
			drawLine(
				{ //the printableText object of each line
					line, 
					text.pos + vec2(0, float(this->fontHeight * lineCounter * text.scale)),
					text.scale
				},
				fontSize,
				vec2(float(dx),float(dy)),
				screen
			);
			
			lineCounter++;
		}
	}

	void Text::drawLine(const PrintableText& text, const vec2& fontSize,const vec2& clipValue, Surface* screen) {
		int count = 0;
		//for each character in the line
		for (char character : text.text) {
			//get character index in the font surface
			int index = int(character) - 32;
			//get source based on character index
			Pixel* source = (*font).GetBuffer() + index * fontWidth;
			//add clipping offset
			source += int(clipValue.y) * (*font).GetPitch();

			//set destination on screen with clipping offsets and line offset
			//get the buffer off the screen and the calculate the position based on character count and line counter
			Pixel* destination = screen->GetBuffer() + int(text.pos.x + fontWidth * text.scale * count) + 
								 int(text.pos.y + clipValue.y) * screen->GetPitch();

			drawChar(clipValue, fontSize, text.scale, source, destination, screen->GetPitch());

			count++;
		}
	
	}

	void Text::drawChar(const vec2& start, const vec2& end, int charScale, Pixel* source, Pixel* destination,const int& screenPitch) {
		//draw character pixel by pixel with scaling
		//si/sj are scale iterators
		//iterate through original rows
		for (int i = int(start.y); i < end.y; i++) {
			//for each row it iterates scale times the same row
			for (int si = 0; si < charScale; si++) {
				//jIndex is the index of the pixel needed to be drawn
				int jIndex = 0;
				//iterate through original columns
				for (int j = int(start.x); j < end.x * charScale; j += charScale) {
					//for each column it iterates scale times the same column
					for (int sj = 0; sj < charScale; sj++) {
						//if the source pixel is not black (transparent) copy it to the screen
						//black pixel used for transparent/void pixels
						if (source[jIndex] != 0xFF000000)
							destination[j + sj] = source[jIndex];
					}
					jIndex++;
				}
				destination += screenPitch;
			}
			source += (*font).GetPitch();
		}
	}

	vec2 Text::getFontSize() const {
		return vec2(float(fontWidth), float(fontHeight));
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