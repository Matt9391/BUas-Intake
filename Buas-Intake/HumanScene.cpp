#include "HumanScene.h"

namespace Tmpl8 {
	
	void HumanScene::onEnter() {
		this->currentMap = MapHandler::mapsTdw;
	}

	void HumanScene::onExit() {}

	void HumanScene::update(float dt, Player& player) {
		
	}

	void HumanScene::draw(Surface* screen) {}

}