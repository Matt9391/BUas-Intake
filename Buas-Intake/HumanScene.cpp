#include "HumanScene.h"
#include "Camera2D.h"
#include "Player.h"
#include "InteractableObject.h"
#include "resources.h"
#include "Text.h"
#include "Game.h"
#include <Windows.h>
#include "MapHandler.h"
#include "PlayerVisual.h"
#include "Scene.h"
#include "tmpl8/surface.h"
#include "tmpl8/template.h"

namespace Tmpl8 {

	void HumanScene::onEnter(Player& player, Camera2D& camera) {
		MapHandler::loadInteractableObject("tdwInteractableObjectList.txt", 32, &fishingAreaSprites);
		camera.setWorldSize(MapHandler::tilesTdw);

		player.setState(int(PlayerVisual::Human));
		player.loadCollisionMaps(&MapHandler::mapsTdw); 
	}

	void HumanScene::onExit(Player& player) {
		MapHandler::objects.clear();
	}

	void HumanScene::update(float dt, Camera2D& camera, Player& player) {

		player.update(dt);

		camera.follow(player.getPos());

		//for each interactable object
		for (auto object : MapHandler::objects) {
			(*object).update(dt, player);

			//check if it intersects with the player
			if ((*object).intersectPlayer(player)) {
				//check if the player is interacting
				if (player.isInteracting()) {
					(*object).interact(player);
				}

			}
		}

		//check for pause key
		if (GetAsyncKeyState('P') & 0x8000) {
			Game::changeScene(SceneType::SceneHome);
		}
	}

	void HumanScene::draw(Surface* screen, Camera2D& camera, Player& player) {
		screen->Clear(0);

		//draw map tiles
		for (int i = 0; i < MapHandler::tilesTdw.y; i++) {
			for (int j = 0; j < MapHandler::tilesTdw.x; j++) {
				for (int iMap = 0; iMap < MapHandler::mapsTdw.size(); iMap++) {
					//'-a' to get the tile index from the char map
					int tx = MapHandler::mapsTdw[iMap][i][j * 4] - 'a';
					int ty = MapHandler::mapsTdw[iMap][i][j * 4 + 1] - 'a';

					//calculate tile position based on camera position
					int x = j * MapHandler::tileSize - int(camera.getPos().x);
					int y = i * MapHandler::tileSize - int(camera.getPos().y);

					MapHandler::drawTile(tx, ty, screen, &MapHandler::mapTdwTileset, x, y, 32);
				}

			}

		}

		Text::drawString("Fish", screen, vec2(15.1f * MapHandler::tileSize, 3.8f * MapHandler::tileSize) - camera.getPos());
		Text::drawString("Shop", screen, vec2(15.1f * MapHandler::tileSize, 4.3f * MapHandler::tileSize) - camera.getPos());

		//if debug is enabled draw hitboxes
		if (this->debug) {
			for (auto object : MapHandler::objects) {
				(*object).drawHitBox(screen, camera.getPos());
			}
		}

		for (auto object : MapHandler::objects) {
			(*object).draw(screen, camera.getPos());
			//if the player intersects with the object show its text
			if ((*object).intersectPlayer(player)) {
				(*object).showText(screen, camera.getPos());
			}
		}

		player.draw(screen, camera.getPos());
		
		Text::drawString("Press 'P' to pause", screen, vec2(20.5f * MapHandler::tileSize, 0.5f * MapHandler::tileSize));
	}
	 
}