#include "Scene.h"
#include <vector>
#include "../DataTypes/PrintableText.h"
#include "../DataTypes/PrintableBox.h"
#include <string>
#include "../DataTypes/SceneType.h"
#include "../GFX/Button.h"
#include "../game.h"
#include "../../tmpl8/surface.h"

namespace Tmpl8 {
	//set the debug variable to false by default
	bool Scene::debug = false;
	//set the debug variable
	void Scene::enableDebug(bool enable) {
		debug = enable;
	}

	Scene::Scene(Game& game, std::string mapName, Surface& tileset, std::string voidChar) :
		game(game),
		type(SceneType::SceneNull),
		mapHandler(mapName, tileset, voidChar)
	{}

	void Scene::clearDynamicObjects() {
		this->dynamicTexts.clear();
		this->dynamicBoxes.clear();
	}

	void Scene::clearAllObjects() {
		this->dynamicTexts.clear();
		this->staticTexts.clear();
		this->dynamicBoxes.clear();
		this->staticBoxes.clear();
	}

	void Scene::addText(const PrintableText text) {
		if (text.isStatic)
			this->staticTexts.push_back(text);
		else
			this->dynamicTexts.push_back(text);
	}

	void Scene::addBox(PrintableBox box) {
		if (box.isStatic)
			this->staticBoxes.push_back(box);
		else
			this->dynamicBoxes.push_back(box);
	}

	void Scene::addTexts(std::vector <PrintableText> texts) {
		for (auto& text : texts) {
			if (text.isStatic)
				this->staticTexts.push_back(text);
			else
				this->dynamicTexts.push_back(text);
		}
	}

	void Scene::addBoxes(std::vector <PrintableBox> boxes) {
		for (auto& box : boxes) {
			if (box.isStatic)
				this->staticBoxes.push_back(box);
			else
				this->dynamicBoxes.push_back(box);
		}
	}


	void Scene::updateButtons(float dt) {
		for (auto& b : this->buttons) {
			b->update(dt);
			if (!b) continue;
			if (!this->game.isMousePressed() || b->isDisabled())
				continue;
			if (b->mouseHover(this->game.getMousePos())) {
				b->onClick(this->game);
				b->setDisable(true);
			}
		}
	}


	SceneType Scene::getSceneType() const {
		return this->type;
	}
}