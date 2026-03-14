#pragma once

#include <template.h>

#include <string>

namespace Tmpl8 {
	
	struct PrintableText {
		std::string text;
		vec2 pos;
		int scale;
		bool isStatic = true;
		bool background = false;
	};
}