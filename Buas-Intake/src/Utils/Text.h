#include <string>
#include <vector>

#pragma once

namespace Tmpl8 {
	class Surface;
	class vec2;

	class Text
	{

	public: 
		Text();

		//initialize the font surface
		static void init(Surface* fontSource);

		//draw coins, scale is optional
		static void drawCoins(Surface* screen, vec2 pos, long long coins, int scale = 1);
		//draw string, scale is optional
		static void drawString(std::string str, Surface* screen, vec2 pos, int scale = 1);

	private:
		//split string into multiple lines based on '\n' character
		static std::vector<std::string> splitLines(const std::string& text);

		//font surface and its character dimensions
		static Surface* font;
		static int fontHeight;
		static int fontWidth;

	};

}