#include <DataTypes/PlayerVisual.h>
#include <DataTypes/PrintableText.h>
#include <DataTypes/SceneType.h>
#include <Gameplay/Camera2D.h>
#include <Gameplay/Player.h>
#include <GFX/ButtonDebug.h>
#include <GFX/ButtonMusic.h>
#include <GFX/ButtonSceneChanger.h>
#include <GFX/ButtonSounds.h>
#include <GFX/HUD.h>
#include <Scenes/SettingsScene.h>
#include <Scenes/Scene.h>
#include <Utils/MapHandler.h>
#include <Utils/Text.h>

#include <game.h>
#include <surface.h>
#include <template.h>


#include <memory>
#include <string>


namespace Tmpl8 {

	SettingsScene::SettingsScene(Game& game, std::string mapName, Surface& tileset, std::string voidChar) :
		Scene(game, mapName, tileset, voidChar)
	{
		this->type = SceneType::SceneSettings;
		this->buttons.emplace_back(std::make_unique<ButtonSceneChanger>(PrintableText{ "Back", vec2(ScreenWidth / 2.f - 32.f, 13.f * MapHandler::tileSize), 2, true, true }, game.getFontSize(), SceneType::SceneHome));
		this->buttons.emplace_back(std::make_unique<ButtonDebug>(PrintableText{ "Enable debug", vec2(ScreenWidth / 2.f - 81.f, 10.f * MapHandler::tileSize), 2, true, true }, game.getFontSize()));
		this->buttons.emplace_back(std::make_unique<ButtonMusic>(PrintableText{ "Disable music", vec2(ScreenWidth / 2.f - 81.f, 7.f * MapHandler::tileSize), 2, true, true }, game.getFontSize()));
		this->buttons.emplace_back(std::make_unique<ButtonSounds>(PrintableText{ "Disable sounds", vec2(ScreenWidth / 2.f - 81.f, 4.f * MapHandler::tileSize), 2, true, true }, game.getFontSize()));
	}

	void SettingsScene::onEnter(Player& player, Camera2D& camera, HUD& hud){
		this->mapHandler.clearObjects();
		camera.setWorldSize(this->mapHandler.getTiles());
	}

	void SettingsScene::onExit(Player& player){
		
	}

	void SettingsScene::update(float dt, Camera2D& camera, Player& player, HUD& hud){	
		this->clearDynamicObjects();

		this->updateButtons(dt);
	}

	void SettingsScene::draw(Surface* screen, Camera2D& camera, Player& player, HUD& hud){
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
	}
}