#include "../../tmpl8/surface.h"
#include "../../tmpl8/template.h"
#include "../Utils/Randomize.h"
#include "../Utils/MapHandler.h"
#include "../Gameplay/Camera2D.h"
#include "../Gameplay/Player.h"
#include "../InteractableObjects/InteractableObject.h"
#include "../GFX/resources.h"
#include "../DataTypes/PlayerVisual.h"
#include "../Entities/Enemy.h"
#include "../game.h"

#include "FishScene.h"

namespace Tmpl8 { 
	FishScene::FishScene(Game& game) :
		Scene(game)
	{
		this->type = SceneType::SceneFish;
	}

	void FishScene::onEnter(Player& player, Camera2D& camera) {
		//load the interactable objects of the current scene
		MapHandler::loadInteractableObject("2DInteractableObjectList.txt", 32);	
		 
		int type = 6; //chest type

		for (int i = 0; i < 10; i++) {
			//randomize chest position
			vec2 pos(
				float(Randomize::randomInt(3 * MapHandler::tileSize, 22 * MapHandler::tileSize)),
				float(Randomize::randomInt(5 * MapHandler::tileSize, 33 * MapHandler::tileSize))
			);

			vec2 size(46);

			//create chest interactable object, fistsSprite is not needed here so it's set to nullptr
			MapHandler::createInteractableObject(type, pos, size, nullptr, &chestsSprite);

		}
		 
		for (int i = 0; i < 10; i++) {
			//randomize enemy position
			vec2 pos(
				float( - 5 * MapHandler::tileSize),
				float(Randomize::randomInt(5 * MapHandler::tileSize, 33 * MapHandler::tileSize))
			);

			vec2 size(124,46);
			//randomize enemy end position based on start position
			vec2 endPos(
				float(26 * MapHandler::tileSize),
				float(Randomize::randomInt(int(pos.y) - 5 * MapHandler::tileSize, int(pos.y) + 5 * MapHandler::tileSize))
			);

			//limit enemy end position within map bounds
			if (endPos.y >= 35.f * MapHandler::tileSize) endPos.y = 34.f * MapHandler::tileSize;
			if (endPos.y < 5.f * MapHandler::tileSize) endPos.y = 5.f * MapHandler::tileSize;

			//add random start offset to enemy movement
			float startOffset = Randomize::randomFloat(100, 1000);

			enemies.push_back(std::make_unique<Enemy>(pos, size, endPos, startOffset, enemySprite));

		}

		
		camera.setWorldSize(MapHandler::tiles2D);
		
		player.setState(int(PlayerVisual::Fish));
		player.loadCollisionMaps(&MapHandler::maps2D);
		player.setPos({ 32,32 });
	}

	void FishScene::onExit(Player& player) {
		MapHandler::objects.clear();
		enemies.clear();
		//set player position to the exit point of the scene
		player.setPos(vec2(MapHandler::tileSize * 29.f, MapHandler::tileSize * 3.f));
	}

	void FishScene::update(float dt, Camera2D& camera, Player& player) {

		player.update(dt);

		camera.follow(player.getPos());

		//for each interactable object
		for (auto& object : MapHandler::objects) {
			object->update(dt, player);

			//check if it intersects with the player
			if (object->intersectPlayer(player)) {
				//check if the player is interacting
				if (player.isInteracting()) {
					object->interact(player, this->game);
				}

			}
		}

		for (auto& e : enemies) {
			e->update(dt, player);

			//check if it intersects with the player
			if (e->intersectPlayer(player)) {
				e->attack(player);
			}
		}
	}

	void FishScene::draw(Surface* screen, Camera2D& camera, Player& player) {
		screen->Clear(0);

		//draw the 2D map
		for (int i = 0; i < MapHandler::tiles2D.y; i++) {
			for (int j = 0; j < MapHandler::tiles2D.x; j++) {
				for (int iMap = 0; iMap < MapHandler::maps2D.size(); iMap++) {
					//'-a' to get the tile index from the char map
					int tx = MapHandler::maps2D[iMap][i][j * 4] - 'a';
					int ty = MapHandler::maps2D[iMap][i][j * 4 + 1] - 'a';
					//calculate tile start draw position
					int x = j * MapHandler::tileSize - int(camera.getPos().x);
					int y = i * MapHandler::tileSize - int(camera.getPos().y);
					
					//draw the tile
					MapHandler::drawTile(tx, ty, screen, &MapHandler::map2DTileset, x, y, 32);
				}

			}

		}
		
		//if debug is enabled draw hitboxes
		if (this->debug) {
			for (auto& object : MapHandler::objects) {
				object->drawHitBox(screen, camera.getPos());
			}
			for (auto& e : enemies) {
				e->drawHitBox(screen, camera.getPos());
			}
		}

		for (auto& object : MapHandler::objects) {
			object->draw(screen, camera.getPos());

			//if the player intersects with the object show its text
			if (object->intersectPlayer(player)) {
				object->showText(screen, camera.getPos());
			}
		}

		for (auto& e : enemies) {
			e->draw(screen, camera.getPos());
		}

		player.draw(screen, camera.getPos());
	}

}