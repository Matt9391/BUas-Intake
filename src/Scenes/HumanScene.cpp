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
#include <memory>
#include <string>
#include "../DataTypes/PrintableText.h"
#include "../GFX/ButtonSceneChanger.h"
#include <utility>

namespace Tmpl8 {

	HumanScene::HumanScene(Game& game, std::string mapName, Surface& tileset, std::string voidChar) :
		Scene(game, mapName, tileset, voidChar)
	{
		this->type = SceneType::SceneHuman;
		this->buttons.emplace_back(std::make_unique<ButtonSceneChanger>(PrintableText{ "Pause", vec2(23.5f * MapHandler::tileSize, 0.5f * MapHandler::tileSize), 1, true, true }, game.getFontSize(), SceneType::SceneHome));
	}

	void HumanScene::onEnter(Player& player, Camera2D& camera, HUD& hud) {
		this->mapHandler.loadInteractableObject("tdwInteractableObjectList.txt", &fishingAreaSprites);
		camera.setWorldSize(this->mapHandler.getTiles());

		player.setState(int(PlayerVisual::Human));
		player.loadCollisionMaps(this->mapHandler.getMaps());
	}

	void HumanScene::onExit(Player& player) {
		this->mapHandler.clearObjects();
	}

	void HumanScene::update(float dt, Camera2D& camera, Player& player, HUD& hud) {
		this->clearDynamicObjects();

		player.update(dt);

		camera.follow(player.getPos());


		if (player.isInteracting()) {
			this->game.getAudioManager().playTapSound();
		}

		this->updateButtons(dt);


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

		player.setIntersecting(playerIntesercting);
		
		this->addText({ "Fish", vec2(15.1f * MapHandler::tileSize, 3.8f * MapHandler::tileSize) - camera.getPos(), 1, false });
		this->addText({ "Shop", vec2(15.1f * MapHandler::tileSize, 4.3f * MapHandler::tileSize) - camera.getPos(), 1, false });


		player.setTexts(camera.getPos());
		player.setBoxes(camera.getPos());


		if (this->game.showAchievement) {
			this->addText(this->game.getAchievementText());
		}

		this->addBoxes(player.getBoxes());
		this->addTexts(player.getTexts());

		if (this->debug) {
			this->mapHandler.setBoxes(camera.getPos());
			this->addBoxes(this->mapHandler.getBoxes());
		}

		//check for pause key
		if (GetAsyncKeyState('P') & 0x8000) {
			this->game.setPendingScene(SceneType::SceneHome);
		}
	}

	void HumanScene::draw(Surface* screen, Camera2D& camera, Player& player, HUD& hud) {
		screen->Clear(0);

		//draw map tiles
		for (int i = 0; i < this->mapHandler.getTiles().y; i++) {
			for (int j = 0; j < this->mapHandler.getTiles().x; j++) {
				for (int iMap = 0; iMap < this->mapHandler.getMaps().size(); iMap++) {
					//'-a' to get the tile index from the char map
					int tx = this->mapHandler.getMaps()[iMap][i][j * 4] - 'a';
					int ty = this->mapHandler.getMaps()[iMap][i][j * 4 + 1] - 'a';

					//calculate tile position based on camera position
					int x = j * MapHandler::tileSize - int(camera.getPos().x);
					int y = i * MapHandler::tileSize - int(camera.getPos().y);

					this->mapHandler.drawTile(tx, ty, screen, x, y);
				}

			}

		}

		hud.drawBoxes(screen, this->staticBoxes);
		hud.drawBoxes(screen, this->dynamicBoxes);

		for (auto& object : this->mapHandler.getObjects()) {
			object->draw(screen, camera.getPos());
		}


		hud.drawTexts(screen, this->staticTexts);
		hud.drawTexts(screen, this->dynamicTexts);
		hud.drawButtons(screen, this->buttons);


		player.draw(screen, camera.getPos());
	

	}
	 
}