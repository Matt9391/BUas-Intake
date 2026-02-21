#include <Windows.h>
#include "../../tmpl8/surface.h"
#include "../../tmpl8/template.h"
#include "../Utils/Text.h"
#include "../Utils/MapHandler.h"
#include "../Gameplay/Camera2D.h"
#include "../Gameplay/Player.h"
#include "../GFX/resources.h"
#include "../InteractableObjects/InteractableObject.h"
#include "../DataTypes/PlayerVisual.h"
#include "Scene.h"
#include "../game.h"

#include "HumanScene.h"
#include "../DataTypes/SceneType.h"
#include "../GFX/HUD.h"

namespace Tmpl8 {

	HumanScene::HumanScene(Game& game) :
		Scene(game)
	{
		this->type = SceneType::SceneHuman;
	}

	void HumanScene::onEnter(Player& player, Camera2D& camera) {
		MapHandler::loadInteractableObject("tdwInteractableObjectList.txt", 32, &fishingAreaSprites);
		camera.setWorldSize(MapHandler::tilesTdw);

		player.setState(int(PlayerVisual::Human));
		player.loadCollisionMaps(&MapHandler::mapsTdw); 
	}

	void HumanScene::onExit(Player& player) {
		MapHandler::objects.clear();
	}

	void HumanScene::update(float dt, Camera2D& camera, Player& player, HUD& hud) {
		hud.clearTexts();

		player.update(dt);

		camera.follow(player.getPos());
		player.setTexts(camera.getPos());


		//for each interactable object
		for (auto& object : MapHandler::objects) {
			object->update(dt, player);

			//check if it intersects with the player
			if (object->intersectPlayer(player)) {
				object->setTexts(camera.getPos());
				//check if the player is interacting
				if (player.isInteracting()) {
					object->interact(player, this->game);
				}

			}

			hud.addTexts(object->getTexts());
			object->clearTexts();
		}

		hud.addText({ "Fish", vec2(15.1f * MapHandler::tileSize, 3.8f * MapHandler::tileSize) - camera.getPos(), 1 });
		hud.addText({"Shop", vec2(15.1f * MapHandler::tileSize, 4.3f * MapHandler::tileSize) - camera.getPos(), 1});
		hud.addText({ "Press 'P' to pause", vec2(20.5f * MapHandler::tileSize, 0.5f * MapHandler::tileSize), 1 });


		hud.addTexts(player.getTexts());

		//check for pause key
		if (GetAsyncKeyState('P') & 0x8000) {
			this->game.setPendingScene(SceneType::SceneHome);
		}
	}

	void HumanScene::draw(Surface* screen, Camera2D& camera, Player& player, HUD& hud) {
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



		//if debug is enabled draw hitboxes
		if (this->debug) {
			for (auto& object : MapHandler::objects) {
				object->drawHitBox(screen, camera.getPos());
			}
		}

		for (auto& object : MapHandler::objects) {
			object->draw(screen, camera.getPos());
		}

		player.draw(screen, camera.getPos());
	
		hud.draw(screen);

	}
	 
}