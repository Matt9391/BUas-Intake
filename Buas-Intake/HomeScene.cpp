#include "HomeScene.h"
#include "MapHandler.h"
#include "Windows.h"
#include "Game.h"
#include "Text.h"
#include "Player.h"
#include "Camera2D.h"
#include "resources.h"
 

namespace Tmpl8 {

	void HomeScene::onEnter(Player& player, Camera2D& camera){
		MapHandler::objects.clear();
		camera.setWorldSize(MapHandler::tilesHome);

		this->playText = "Press 'SPACE' to play";	
		this->playTextPosition = vec2((MapHandler::tilesHome.x / 2.f - 2.3) * MapHandler::tileSize, 11.35 * MapHandler::tileSize);
		
		this->howToPlayText = "'WASD' to move around\n'Shift' to sprint (only X-axe)\n'F' to interact with:\n    - Shops\n    - Zones\n    - Chests";
		this->howToPlayTextPosition = vec2(1 * MapHandler::tileSize, 3 * MapHandler::tileSize);

		this->UIText = "<-- Seconds of sprint left\n\n<-- Fishes count in the fish inventory\n\n<-- Chests count in the chest inventory";
		this->UITextPosition = vec2(5.5 * MapHandler::tileSize, 1 * MapHandler::tileSize);

		this->gameTitlePos = vec2(17.5 * MapHandler::tileSize, -0.5 * MapHandler::tileSize);

		player.setPos(vec2(ScreenWidth / 2 - 140.f, ScreenHeight / 2));
		player.setState(int(PlayerVisual::Human));
		player.loadCollisionMaps(&MapHandler::mapsHome);
	}

	void HomeScene::onExit(){}

	void HomeScene::update(float dt, Camera2D& camera, Player& player){
		if (GetAsyncKeyState(VK_SPACE)) {
			Game::changeScene(SceneType::SceneHuman);
		}
		player.update(dt);
	}

	void HomeScene::draw(Surface* screen, Camera2D& camera, Player& player){
		screen->Clear(0);
		

		for (int i = 0; i < MapHandler::tilesHome.y; i++) {
			for (int j = 0; j < MapHandler::tilesHome.x; j++) {
				for (int iMap = 0; iMap < MapHandler::mapsHome.size(); iMap++) {
					int tx = MapHandler::mapsHome[iMap][i][j * 4] - 'a';
					int ty = MapHandler::mapsHome[iMap][i][j * 4 + 1] - 'a';
					//printf("%c e %c\n", tx + 'a', ty + 'a');
					int x = j * MapHandler::tileSize - int(camera.getPos().x);
					int y = i * MapHandler::tileSize - int(camera.getPos().y);
					//printf("%d e %d\n", x, y);

					MapHandler::drawTile(tx, ty, screen, &MapHandler::mapTdwTileset, x, y, 32);
				}

			}

		}

		player.draw(screen, camera.getPos());

		Text::drawString(this->playText, screen, this->playTextPosition);
		Text::drawString(this->howToPlayText, screen, this->howToPlayTextPosition);
		Text::drawString(this->UIText, screen, this->UITextPosition);

		gameTitle.DrawScaled(this->gameTitlePos.x, this->gameTitlePos.y, 250, 250, screen);
	}
}