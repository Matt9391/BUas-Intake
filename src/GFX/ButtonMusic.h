#pragma once
#include "../../tmpl8/template.h"
#include "../DataTypes/PrintableText.h"
#include "../DataTypes/SceneType.h"

#include "Button.h"

namespace Tmpl8 {
	class Game;

	class ButtonMusic : public Button {
	public:

		ButtonMusic(const PrintableText& text, const vec2& fontSize);

		void onClick(Game& game) override;

	private:
		bool musicState;
	};


}