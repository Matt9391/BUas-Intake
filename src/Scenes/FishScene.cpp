#include <DataTypes/PlayerVisual.h>
#include <DataTypes/SceneType.h>
#include <Entities/Enemy.h>
#include <Gameplay/Camera2D.h>
#include <Gameplay/Player.h>
#include <GFX/HUD.h>
#include <GFX/resources.h>
#include <InteractableObjects/InteractableObject.h>
#include <Scenes/FishScene.h>
#include <Scenes/Scene.h>
#include <Utils/MapHandler.h>
#include <Utils/Randomize.h>

#include <game.h>
#include <template.h>

#include <memory>
namespace Tmpl8 { 
	FishScene::FishScene(Game& game, std::string mapName, Surface& tileset, std::string voidChar) :
		Scene(game, mapName, tileset, voidChar)
	{
		this->type = SceneType::SceneFish;
	}

	void FishScene::onEnter(Player& player, Camera2D& camera, HUD& hud) {
		//load the interactable objects of the current scene
		this->mapHandler.loadInteractableObject("2DInteractableObjectList.txt");
		 
		int type = 6; //chest type
		int tileSize = MapHandler::tileSize;

		for (int i = 0; i < 10; i++) {
			//randomize chest position
			vec2 pos(
				float(Randomize::randomInt(3 * tileSize, 22 * tileSize)),
				float(Randomize::randomInt(5 * tileSize, 33 * tileSize))
			);

			vec2 size(46);

			//create chest interactable object, fistsSprite is not needed here so it's set to nullptr
			this->mapHandler.createInteractableObject(type, pos, size, nullptr, &chestsSprite);

		}
		 
		for (int i = 0; i < 10; i++) {
			//randomize enemy position
			vec2 pos(
				float( - 5 * tileSize),
				float(Randomize::randomInt(5 * tileSize, 33 * tileSize))
			);

			vec2 size(124,46);
			//randomize enemy end position based on start position
			vec2 endPos(
				float(26 * tileSize),
				float(Randomize::randomInt(int(pos.y) - 5 * tileSize, int(pos.y) + 5 * tileSize))
			);

			//limit enemy end position within map bounds
			if (endPos.y >= 35.f * tileSize) endPos.y = 34.f * tileSize;
			if (endPos.y < 5.f * tileSize) endPos.y = 5.f * tileSize;

			//add random start offset to enemy movement
			float startOffset = Randomize::randomFloat(100, 1000);

			enemies.push_back(std::make_unique<Enemy>(pos, size, endPos, startOffset, enemySprite));

		}

		
		camera.setWorldSize(this->mapHandler.getTiles());
		
		player.setState(int(PlayerVisual::Fish));
		player.loadCollisionMaps(this->mapHandler.getMaps());
		player.setPos({ 32,32 });
	}

	void FishScene::onExit(Player& player) {
		this->mapHandler.clearObjects();
		enemies.clear();
		//set player position to the exit point of the scene
		player.setPos(vec2(MapHandler::tileSize * 29.f, MapHandler::tileSize * 3.f));
	}

	void FishScene::update(float dt, Camera2D& camera, Player& player, HUD& hud) {
		this->clearDynamicObjects();

		player.update(dt);
		camera.follow(player.getPos());

		if (player.isInteracting()) {
			this->game.getAudioManager().playTapSound();
		}

		bool playerIntesercting = false;
		//for each interactable object
		for (auto& object : this->mapHandler.getObjects()) {
			object->update(dt, player);

			//check if it intersects with the player
			if (object->intersectPlayer(player)) {
				playerIntesercting = true;
				object->setTexts(camera.getPos());
				//check if the player is interacting
				if (player.isInteracting()) {
					object->interact(player, this->game);
				}

			}

			this->addTexts(object->getTexts());
			object->clearTexts();

			if (this->debug) {
				this->addBox(object->getBox(camera.getPos()));
			}

		}

		bool playerDamaged = false;
		for (auto& e : enemies) {
			e->update(dt, player);

			//check if it intersects with the player
			if (e->intersectPlayer(player)) {
				playerIntesercting = true;
				e->attack(player);
				playerDamaged = true;
			}

			if (this->debug) {
				this->addBox(e->getBox(camera.getPos()));
			}
		}

		player.setIntersecting(playerIntesercting);


		if (playerDamaged) {
			player.setDamaged(true);
			this->game.getAudioManager().playHurtSound();
		}
		else {
			player.setDamaged(false);
		}

		player.setTexts(camera.getPos());
		player.setBoxes(camera.getPos());

		this->addBoxes(player.getBoxes());
		this->addTexts(player.getTexts());

		if (this->debug) {
			this->mapHandler.setBoxes(camera.getPos());
			this->addBoxes(this->mapHandler.getBoxes());
		}
	}

	void FishScene::draw(Surface* screen, Camera2D& camera, Player& player, HUD& hud) {
		screen->Clear(0);

		//draw the 2D map
		for (int i = 0; i < this->mapHandler.getTiles().y; i++) {
			for (int j = 0; j < this->mapHandler.getTiles().x; j++) {
				for (int iMap = 0; iMap < this->mapHandler.getMaps().size(); iMap++) {
					//'-a' to get the tile index from the char map
					int tx = this->mapHandler.getMaps()[iMap][i][j * 4] - 'a';
					int ty = this->mapHandler.getMaps()[iMap][i][j * 4 + 1] - 'a';
					//calculate tile start draw position
					int x = j * MapHandler::tileSize - int(camera.getPos().x);
					int y = i * MapHandler::tileSize - int(camera.getPos().y);
					
					//draw the tile
					this->mapHandler.drawTile(tx, ty, screen, x, y);
				}

			}

		}

		hud.drawBoxes(screen, this->staticBoxes);
		hud.drawBoxes(screen, this->dynamicBoxes);
		
		for (auto& object : this->mapHandler.getObjects()) {
			object->draw(screen, camera.getPos());
		}

		for (auto& e : enemies) {
			e->draw(screen, camera.getPos());
		}


		hud.drawTexts(screen, this->staticTexts);
		hud.drawTexts(screen, this->dynamicTexts);
		hud.drawButtons(screen, this->buttons);


		player.draw(screen, camera.getPos());

	}

}