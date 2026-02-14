#include "HomeScene.h"
#include "MapHandler.h"
#include "Windows.h"
#include "Game.h"
#include "Text.h"
#include "Player.h"
#include "Camera2D.h"
#include "resources.h"
#include "PlayerVisual.h"
#include "Scene.h"
#include "tmpl8/surface.h"
#include "Game.h"
 

namespace Tmpl8 {

	HomeScene::HomeScene(Game& game) :
		Scene(game)
	{}

	void HomeScene::onEnter(Player& player, Camera2D& camera){
		MapHandler::objects.clear();
		camera.setWorldSize(MapHandler::tilesHome);
		
		//just some texts to show in the home scene
		this->playText = "Press 'SPACE' to play";	
		this->playTextPosition = vec2((MapHandler::tilesHome.x / 2.f - 2.3f) * MapHandler::tileSize, 11.35f * MapHandler::tileSize);
		
		this->howToPlayText = "'WASD' to move around\n'Shift' to sprint sideway\n'F' to interact with:\n  - Shops\n  - Zones\n  - Chests";
		this->howToPlayTextPosition = vec2(0.3f * MapHandler::tileSize, 2.8f * MapHandler::tileSize);

		this->UIText = "<-- Seconds of sprint left\n\n<-- Fishes count in the fish inventory\n\n<-- Chests count in the chest inventory";
		this->UITextPosition = vec2(5.5f * MapHandler::tileSize, 1.f * MapHandler::tileSize);

		this->whatIsText = "It's finally your\nchance to get rich!!\nFish safely or swim\nthrough the dangers.\nThe choice is yours \nbut make sure to \nbecome the richest..";
		this->whatIsTextPosition = vec2(0.5f * MapHandler::tileSize, 11.f * MapHandler::tileSize);
		 
		this->resetText = "Press 'CTRL' + 'T' to reset all you game saves";
		this->resetTextPosition = vec2(14.f * MapHandler::tileSize, 15.3f * MapHandler::tileSize);

		this->gameTitlePos = vec2(17.5f * MapHandler::tileSize, -0.5f * MapHandler::tileSize);

		player.setPos(vec2(ScreenWidth / 2.f - 140.f, ScreenHeight / 2.f));
		player.setState(int(PlayerVisual::Human));
		player.loadCollisionMaps(&MapHandler::mapsHome);
	}

	void HomeScene::onExit(Player& player){
		player.setPos(vec2(MapHandler::tileSize * 15.f, MapHandler::tileSize * 6.f));
	}

	void HomeScene::update(float dt, Camera2D& camera, Player& player){
		if (GetAsyncKeyState(VK_SPACE)) {
			this->game.setPendingScene(SceneType::SceneHuman);
		}

		player.update(dt);

		camera.follow(player.getPos());
	}

	void HomeScene::draw(Surface* screen, Camera2D& camera, Player& player){
		screen->Clear(0);
		
		//draw the home map
		for (int i = 0; i < MapHandler::tilesHome.y; i++) {
			for (int j = 0; j < MapHandler::tilesHome.x; j++) {
				for (int iMap = 0; iMap < MapHandler::mapsHome.size(); iMap++) {
					//'-a' to get the tile index from the char map
					int tx = MapHandler::mapsHome[iMap][i][j * 4] - 'a';
					int ty = MapHandler::mapsHome[iMap][i][j * 4 + 1] - 'a';
					//calculate tile position based on camera position
					int x = j * MapHandler::tileSize - int(camera.getPos().x);
					int y = i * MapHandler::tileSize - int(camera.getPos().y);

					MapHandler::drawTile(tx, ty, screen, &MapHandler::mapTdwTileset, x, y, 32);
				}

			}

		}

		player.draw(screen, camera.getPos());

		Text::drawString(this->playText, screen, this->playTextPosition);
		Text::drawString(this->howToPlayText, screen, this->howToPlayTextPosition, 2);
		Text::drawString(this->UIText, screen, this->UITextPosition);
		Text::drawString(this->whatIsText, screen, this->whatIsTextPosition, 2);
		Text::drawString(this->resetText, screen, this->resetTextPosition);

		gameTitle.DrawScaled(int(this->gameTitlePos.x), int(this->gameTitlePos.y), 250, 250, screen);
	}
}