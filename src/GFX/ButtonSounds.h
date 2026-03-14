#pragma once
#include <DataTypes/PrintableText.h>
#include <DataTypes/SceneType.h>
#include <GFX/Button.h>

#include <template.h>

namespace Tmpl8 {
	class Game;

	class ButtonSounds : public Button {
	public:

		ButtonSounds(const PrintableText& text, const vec2& fontSize);

		void onClick(Game& game) override;

	private:
		bool soundsState;
	};


}