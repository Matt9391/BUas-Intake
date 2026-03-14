#pragma once
#include <DataTypes/PrintableText.h>
#include <DataTypes/SceneType.h>
#include <GFX/Button.h>

#include <template.h>

namespace Tmpl8 {
	class Game;

	class ButtonDebug : public Button {
	public:
		ButtonDebug(const PrintableText& text, const vec2& fontSize);

		void onClick(Game& game) override;

	private:
		bool debugState;
	};


}