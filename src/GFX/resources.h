#pragma once

#include <surface.h>

#include <array>

namespace Tmpl8 {
	//assets declaration
	extern Surface fontSource;
	extern Sprite humanSprite;
	extern Sprite fishSprite;
	extern Sprite fishSpriteDamaged;
	extern std::array<Sprite*, 2> fishSprites;
	extern Sprite barSprite;
	extern Sprite indxSprite;
	extern Sprite fishesSprite;
	extern Sprite chestsSprite;
	extern Sprite enemySprite;
	extern Sprite gameTitle;
	extern std::array<Sprite*, 3> fishingAreaSprites;

	extern Surface map2DTileset;
	extern Surface mapTdwTileset;
} 