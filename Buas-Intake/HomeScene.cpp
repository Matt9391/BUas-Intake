#include "HomeScene.h"
#include "MapHandler.h"
#include "Windows.h"
#include "Game.h"
#include "Text.h"
 

namespace Tmpl8 {

	void HomeScene::onEnter(Player& player, Camera2D& camera){
		MapHandler::objects.clear();
		this->playText = "Press 'SPACE' to play";
		this->playTextPosition = vec2(ScreenWidth / 2, ScreenHeight / 2);
	}

	void HomeScene::onExit(){}

	void HomeScene::update(float dt, Camera2D& camera, Player& player){
		if (GetAsyncKeyState(VK_SPACE)) {
			Game::changeScene(SceneType::SceneHuman);
		}
	}

	void HomeScene::draw(Surface* screen, Camera2D& camera, Player& player){
		screen->Clear(0);
		 
		Text::drawString(this->playText, screen, this->playTextPosition);
	}
}