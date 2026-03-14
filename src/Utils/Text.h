#pragma once

#include <surface.h>

#include <string>
#include <vector>

namespace Tmpl8 {
	class Surface;
	class vec2;
	struct PrintableText;

	class Text
	{

	public: 
		//initialize the font surface
		Text(Surface* fontSource);

		void drawText(const PrintableText& text, Surface* screen);
		vec2 getFontSize() const;
	private:
		//split string into multiple lines based on '\n' character
		std::vector<std::string> splitLines(const std::string& text);
		void drawLine(const PrintableText& text, const vec2& fontSize, const vec2& clipValue, Surface* screen);
		void drawChar(const vec2& start, const vec2& end, int charScale, Pixel* source, Pixel* destination,const int& screenPitch);

		//font surface and its character dimensions
		Surface* font;
		int fontHeight;
		int fontWidth;

	};

}