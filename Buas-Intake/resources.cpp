#include "resources.h"

namespace Tmpl8 {
	Surface fontSource("./assets/Font/fontHorizontal.png");
	Sprite humanSprite(new Surface("./assets/TopDown/player.tga"), 40);
	Sprite fishSprite(new Surface("./assets/2D/mainFish@0,5x.tga"), 14);
	Sprite barSprite(new Surface("./assets/TopDown/fishingBar.png"), 1);
	Sprite indxSprite(new Surface("./assets/TopDown/fishingIndx.png"), 1);
	Sprite fishesSprite(new Surface("./assets/TopDown/fishesv2.tga"), 4);
	Sprite chestsSprite(new Surface("./assets/2D/Chests2.tga"), 4);
	Sprite enemySprite(new Surface("./assets/2D/angryFish.tga"), 20);
	Sprite gameTitle(new Surface("./assets/title.png"), 1);

	std::array<Sprite*, 3> fishingAreaSprites = { &barSprite, &indxSprite, &fishesSprite };
	 
} 