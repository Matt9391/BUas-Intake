#include <Windows.h>
#include "../../tmpl8/surface.h"
#include "../Utils/MapHandler.h"
#include "../Utils/Text.h"
#include "../Gameplay/Player.h"
#include "../Gameplay/Camera2D.h"
#include "../GFX/resources.h"
#include "../DataTypes/PlayerVisual.h"
#include "Scene.h"
#include "../game.h"
 
#include "HomeScene.h"
#include "../DataTypes/SceneType.h"
#include "../GFX/HUD.h"
#include "../../tmpl8/template.h"
#include <string>
#include "../GFX/ButtonSceneChanger.h"
#include <memory>
#include "../DataTypes/PrintableText.h"
#include <utility>

namespace Tmpl8 {

	HomeScene::HomeScene(Game& game, std::string mapName, Surface& tileset, std::string voidChar) :
		Scene(game, mapName, tileset, voidChar)
	{
		this->type = SceneType::SceneHome;
		this->buttons.emplace_back(std::make_unique<ButtonSceneChanger>(PrintableText{ "Play", vec2(2.f * MapHandler::tileSize, 5.f * MapHandler::tileSize), 2, true, true }, game.getFontSize(), SceneType::SceneHuman));
		this->buttons.emplace_back(std::make_unique<ButtonSceneChanger>(PrintableText{ "How to play", vec2(0.5f * MapHandler::tileSize, 7.f * MapHandler::tileSize), 2, true, true }, game.getFontSize(), SceneType::SceneHowToPlay));
		this->buttons.emplace_back(std::make_unique<ButtonSceneChanger>(PrintableText{ "Settings", vec2(1.f * MapHandler::tileSize, 9.f * MapHandler::tileSize), 2, true, true }, game.getFontSize(), SceneType::SceneSettings));
		this->buttons.emplace_back(std::make_unique<ButtonSceneChanger>(PrintableText{ "Quit", vec2(2.1f * MapHandler::tileSize, 11.f * MapHandler::tileSize), 2, true, true }, game.getFontSize(), SceneType::SceneQuit));

		this->addText(PrintableText{ "Press 'SPACE' to play", vec2((this->mapHandler.getTiles().x / 2.f - 2.3f) * MapHandler::tileSize, 11.35f * MapHandler::tileSize),1, true});
		this->addText(PrintableText{ "Press 'CTRL' + 'T' to reset all you game saves", vec2(14.f * MapHandler::tileSize, 15.3f * MapHandler::tileSize),1, true });

		this->gameTitlePos = vec2(17.5f * MapHandler::tileSize, -0.5f * MapHandler::tileSize);
	}

	void HomeScene::onEnter(Player& player, Camera2D& camera, HUD& hud){
		this->mapHandler.clearObjects();
		camera.setWorldSize(this->mapHandler.getTiles());

		player.setPos(vec2(ScreenWidth / 2.f - 140.f, ScreenHeight / 2.f));
		player.setState(int(PlayerVisual::Human));
		player.loadCollisionMaps(this->mapHandler.getMaps());
	}

	void HomeScene::onExit(Player& player){
		player.setPos(vec2(MapHandler::tileSize * 15.f, MapHandler::tileSize * 6.f));
	}

	void HomeScene::update(float dt, Camera2D& camera, Player& player, HUD& hud){
		if (GetAsyncKeyState(VK_SPACE)) {
			this->game.setPendingScene(SceneType::SceneHuman);
		}

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

		if(!this->game.getAudioManager().isLoaded())
			this->addText(PrintableText{ "Music loading in background...", vec2(0.5f * MapHandler::tileSize, 15.3f * MapHandler::tileSize),1, false, false});

		if (this->debug) {
			this->mapHandler.setBoxes(camera.getPos());
			this->addBoxes(this->mapHandler.getBoxes());
		}
	}

	void HomeScene::draw(Surface* screen, Camera2D& camera, Player& player, HUD& hud){
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


		gameTitle.DrawScaled(int(this->gameTitlePos.x), int(this->gameTitlePos.y), 250, 250, screen);
	}
}