#include <string>
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

		static void drawCharacter(std::string str, Surface* screen, vec2 pos);

	private:
		static Surface* font;
		static int fontHeight;
		static int fontWidth;

	};

}