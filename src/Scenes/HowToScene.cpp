#include <DataTypes/PlayerVisual.h>
#include <DataTypes/PrintableText.h>
#include <DataTypes/SceneType.h>
#include <Gameplay/Camera2D.h>
#include <Gameplay/Player.h>
#include <GFX/ButtonSceneChanger.h>
#include <GFX/HUD.h>
#include <GFX/resources.h>
#include <Scenes/HowToScene.h>
#include <Scenes/Scene.h>
#include <Utils/MapHandler.h>
#include <Utils/Text.h>

#include <game.h>
#include <surface.h>
#include <template.h>

#include <Windows.h>
#include <memory>
#include <string>
#include <utility>

namespace Tmpl8 {

	HowToScene::HowToScene(Game& game, std::string mapName, Surface& tileset, std::string voidChar) :
		Scene(game, mapName, tileset, voidChar)
	{
		this->type = SceneType::SceneHowToPlay;
		this->buttons.emplace_back(std::make_unique<ButtonSceneChanger>(PrintableText{ "Back", vec2(ScreenWidth / 2.f - 32.f, 13.f * MapHandler::tileSize), 2, true, true }, game.getFontSize(), SceneType::SceneHome));

		int tileSize = MapHandler::tileSize;

		this->addText({ "Collect coins by\nfishing and exploring\nthe ocean as\nboth human and fish,\nfinding treasures and\navoiding dangers.\nEarn enough money\nto repay the\nChurch's debt and\nreach 1,000,000,000\ncoins to win your\nfreedom.", vec2(0.5f * tileSize, 4.5f * tileSize), 2, true, true });
		this->addText({ "'WASD' to move around\n'Shift' to sprint sideway\n'F' to interact with:\n  - Shops\n  - Zones\n  - Chests\n'Esc' to quit\n'P' to pause", vec2(14.f * tileSize, 5.f * tileSize), 2, true});
		this->addBox({ vec2(14.f * tileSize, 5.f * tileSize) - vec2(0,5), vec2(350, 168), 0x604239 });
		this->addText({ "<-- Seconds of sprint left\n\n<-- Fishes count in the fish inventory\n\n<-- Chests count in the chest inventory", vec2(5.5f * tileSize, 0.5f * tileSize), 1, true, true });

	}

	void HowToScene::onEnter(Player& player, Camera2D& camera, HUD& hud){
		this->mapHandler.clearObjects();
		camera.setWorldSize(this->mapHandler.getTiles());

		player.setPos(vec2(ScreenWidth / 2.f - MapHandler::tileSize, ScreenHeight / 2.f - MapHandler::tileSize / 2.f));
		player.setState(int(PlayerVisual::Human));
		player.loadCollisionMaps(this->mapHandler.getMaps());
	}

	void HowToScene::onExit(Player& player){
		player.setPos(vec2(MapHandler::tileSize * 15.f, MapHandler::tileSize * 6.f));
	}

	void HowToScene::update(float dt, Camera2D& camera, Player& player, HUD& hud){
		this->clearDynamicObjects();
		
		player.update(dt);
		camera.follow(player.getPos());

		if (player.isInteracting()) {
			this->game.getAudioManager().playTapSound();
		}

		this->updateButtons(dt);

		player.setTexts(camera.getPos());
		player.setBoxes(camera.getPos());

		this->addTexts(player.getTexts());
		this->addBoxes(player.getBoxes());
	}

	void HowToScene::draw(Surface* screen, Camera2D& camera, Player& player, HUD& hud){
		screen->Clear(0);
		
		//draw the home map
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
		hud.drawTexts(screen, this->staticTexts);
		hud.drawTexts(screen, this->dynamicTexts);
		hud.drawButtons(screen, this->buttons);



		player.draw(screen, camera.getPos());


	}
}