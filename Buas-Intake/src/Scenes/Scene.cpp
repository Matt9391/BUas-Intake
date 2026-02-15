#include "Scene.h"

namespace Tmpl8 {
	//set the debug variable to false by default
	bool Scene::debug = false;
	//set the debug variable
	void Scene::enableDebug(bool enable) {
		debug = enable;
	}

	Scene::Scene(Game& game):
		game(game),
		type(SceneType::SceneNull)
	{}

	SceneType Scene::getSceneType() {
		return this->type;
	}
}