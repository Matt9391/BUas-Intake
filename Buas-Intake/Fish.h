#pragma once

namespace Tmpl8 {
	enum FishRarity {
		COMMON,
		RARE,
		EPIC,
		LEGENDARY
	};

 
	struct Fish {
		FishRarity rarity;
		float value;
	};

}