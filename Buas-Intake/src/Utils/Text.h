#include <string>
#include <vector>

#pragma once

namespace Tmpl8 {
	class Surface;
	class vec2;
	struct PrintableText;

	class Text
	{

	public: 
		//initialize the font surface
		Text(Surface* fontSource);

		

		//draw string, scale is optional
		//static void drawString(std::string str, Surface* screen, vec2 pos, int scale = 1);
		void drawString(PrintableText text, Surface* screen);


	private:
		//split string into multiple lines based on '\n' character
		static std::vector<std::string> splitLines(const std::string& text);

		//font surface and its character dimensions
		Surface* font;
		int fontHeight;
		int fontWidth;

	};

}