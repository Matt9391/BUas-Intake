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

		static void init(Surface* fontSource);

		static void print(Surface* screen);
		static void drawCoins(Surface* screen, vec2 pos, long long coins);
		static void drawCoinsScaled(Surface* screen, vec2 pos, long long coins, int scale);

		static void drawString(std::string str, Surface* screen, vec2 pos);
		static void drawStringScaled(std::string str, Surface* screen, vec2 pos, int scale);

	private:
		static std::vector<std::string> splitLines(const std::string& text);

		static Surface* font;
		static int fontHeight;
		static int fontWidth;

	};

}