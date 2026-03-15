#include <DataTypes/PlayerVisual.h>
#include <DataTypes/SceneType.h>
#include <DataTypes/PrintableText.h>
#include <Gameplay/Camera2D.h>
#include <Gameplay/Player.h>
#include <GFX/ButtonSceneChanger.h>
#include <GFX/HUD.h>
#include <Scenes/WinScene.h>
#include <Scenes/Scene.h>
#include <Utils/MapHandler.h>
#include <Utils/Text.h>

#include <game.h>
#include <surface.h>
#include <template.h>

#include <memory>
#include <string>

namespace Tmpl8 {

	WinScene::WinScene(Game& game, std::string mapName, Surface& tileset, std::string voidChar) :
		Scene(game, mapName, tileset, voidChar)
	{
		this->type = SceneType::SceneWin;
		int tileSize = MapHandler::tileSize;

		this->addText({ "YOU HAVE\nCOMPLETED\nTHE GAME", vec2(10.55f * tileSize, (this->mapHandler.getTiles().y / 8.f) * tileSize), 2, true, true });
		this->buttons.emplace_back(std::make_unique<ButtonSceneChanger>(PrintableText{ "Home", vec2(19.f * MapHandler::tileSize, 8.f * MapHandler::tileSize), 2, true, true }, game.getFontSize(), SceneType::SceneHome));
		this->buttons.emplace_back(std::make_unique<ButtonSceneChanger>(PrintableText{ "Quit", vec2(19.f * MapHandler::tileSize, 10.f * MapHandler::tileSize), 2, true, true }, game.getFontSize(), SceneType::SceneQuit));
	}

	void WinScene::onEnter(Player& player, Camera2D& camera, HUD& hud){
		this->mapHandler.clearObjects();
		camera.setWorldSize(this->mapHandler.getTiles());

		player.setPos(vec2(ScreenWidth / 2.f - 190.f, ScreenHeight / 2.f + 32.f));
		player.setState(int(PlayerVisual::Human));
		player.loadCollisionMaps(this->mapHandler.getMaps());
		
		
	}

	void WinScene::onExit(Player& player){
		player.setPos(vec2(MapHandler::tileSize * 15.f, MapHandler::tileSize * 6.f));
	}

	void WinScene::update(float dt, Camera2D& camera, Player& player, HUD& hud){
		this->clearDynamicObjects();

		this->updateButtons(dt);

		player.update(dt);

		camera.follow(player.getPos());

		if (player.isInteracting()) {
			this->game.getAudioManager().playTapSound();
		}

		player.setTexts(camera.getPos());
		player.setBoxes(camera.getPos());

		this->addTexts(player.getTexts());
		this->addBoxes(player.getBoxes());

		if (this->debug) {
			this->mapHandler.setBoxes(camera.getPos());
			this->addBoxes(this->mapHandler.getBoxes());
		}

	}

	void WinScene::draw(Surface* screen, Camera2D& camera, Player& player, HUD& hud){
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