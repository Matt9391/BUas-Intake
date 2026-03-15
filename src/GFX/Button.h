#pragma once
#include <DataTypes/PrintableText.h>

#include <template.h>

namespace Tmpl8 {
	class Game;

	class Button {
	public:

		Button(PrintableText text, const vec2& fontSize);
		virtual ~Button() = default;

		void update(float dt);

		bool mouseHover(vec2 mousePos) const;
		
		void setDisable(bool disable);

		virtual void onClick(Game& game);

		bool isDisabled() const;
		PrintableText getText() const;

	protected:
		PrintableText text;
		vec2 fontSize;

		float elapsedTime;
		float timer;

		bool disabled;
	};


}