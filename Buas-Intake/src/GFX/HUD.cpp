#include <vector>
#include "../../tmpl8/surface.h"
#include "../Utils/Text.h"
#include "../DataTypes/PrintableBox.h"
#include "../DataTypes/PrintableText.h"

#include "HUD.h"

namespace Tmpl8 {

	HUD::HUD(Text& textDrawer) :
		textDrawer(textDrawer)
	{}

	void HUD::clearTexts() {
		this->texts.clear();
	}

	void HUD::addText(const PrintableText text) {
		this->texts.push_back(text);
	}

	void HUD::addTexts(std::vector <PrintableText> texts) {
		for (auto& text : texts) {
			this->texts.push_back(text);
		}
	}

	void HUD::addBox(PrintableBox box) {
		this->boxes.push_back(box);
	}

	void HUD::draw(Surface* screen) {
		for (auto& text : this->texts) {
			this->textDrawer.drawString(text, screen);
		}

		//double clear to avoid problems
		this->texts.clear();
	}

}
