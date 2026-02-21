#include "InteractableObject.h"
#include <string>
#include "../../tmpl8/template.h"

namespace Tmpl8 {

	class Player;
	class HUD;
	class Game;

	class DebtHolder : public InteractableObject {
	public:

		DebtHolder(int type, vec2 pos, vec2 size);

		void update(float dt, Player& player) override;

		void interact(Player& player, Game& game) override;

		void setTexts(vec2 cameraOffset) override;

		static void loadPaidDebt(long long loadedDebt);

		static long long getPaidDebt();
		
		static long long paidDebt;

	private:
		//price needed to repay the debt;
		static long long totalDebt;

		long long firstFine;
		long long lastFine;

		//text to show when not enough coins
		std::string alertText;

		vec2 priceTextPosition;
		vec2 alertTextPosition;

		//alert variables
		bool showAlert;
		float alertTime;
		float alertElapsedTime;
	};

}