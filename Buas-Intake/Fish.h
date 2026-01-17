#pragma once

namespace Tmpl8 {
	enum Rarity {
		COMMON,
		RARE,
		EPIC,
		LEGENDARY
	};

 
	struct Fish {
		Rarity rarity;
		float value;
	};

}