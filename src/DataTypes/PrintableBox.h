#pragma once

#include <surface.h>
#include <template.h>

#include <string>

namespace Tmpl8 {

	struct PrintableBox {
		vec2 pos;
		vec2 size;
		Pixel clr;
		bool isStatic = true;
		bool filled = true;
	};

}