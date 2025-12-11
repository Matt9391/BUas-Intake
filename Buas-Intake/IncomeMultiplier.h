#include "InteractableObject.h"

#pragma once
namespace Tmpl8 {


	class IncomeMultiplier : public InteractableObject
	{
	public:
		IncomeMultiplier(int type, vec2 pos, vec2 size);

		//void showText(Surface* screen, vec2 cameraOffset) override;

		void draw(Surface* screen, vec2 cameraOffset) override;
	private:


		float price;
		int multiplier;

	};


};