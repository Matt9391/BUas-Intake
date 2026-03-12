#pragma once
#include "../../tmpl8/template.h"
#include "../DataTypes/PrintableText.h"
#include "../DataTypes/SceneType.h"

#include "Button.h"

namespace Tmpl8 {
	class Game;

	class ButtonSceneChanger : public Button {
	public:

		ButtonSceneChanger(const PrintableText& text, const vec2& fontSize, SceneType nextScene);

		void onClick(Game& game) override;

	private:
		SceneType nextScene;
	};


}