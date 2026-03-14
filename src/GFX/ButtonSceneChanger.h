#pragma once
#include <DataTypes/PrintableText.h>
#include <DataTypes/SceneType.h>
#include <GFX/Button.h>

#include <template.h>

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