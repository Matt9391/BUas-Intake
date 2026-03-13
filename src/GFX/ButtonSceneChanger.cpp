#pragma once
#include <iostream>
#include "../../tmpl8/template.h"
#include "../DataTypes/PrintableText.h"
#include "../DataTypes/SceneType.h"
#include "../Utils/functions.h"
#include "ButtonSceneChanger.h"
#include "../game.h"
#include "Button.h"

namespace Tmpl8 {

	ButtonSceneChanger::ButtonSceneChanger(const PrintableText& text, const vec2& fontSize, SceneType nextScene) :
		Button(text, fontSize),
		nextScene(nextScene)
	{}

	void ButtonSceneChanger::onClick(Game& game) {
		game.setPendingScene(this->nextScene);
	}
}