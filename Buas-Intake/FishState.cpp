#include "FishState.h"
#include "Player.h"
#include <Windows.h>

namespace Tmpl8 {

	void FishState::enter(Player& player) {
		//player.setState(0);
		printf("Sono un Pesce\n");
		player.setSprinting(false);
		this->sprintSpeed = 0.35;
	}

	void FishState::handleInput(Player& player) { 
		player.setDir({ 0,0 });

		char lastInput = player.getInput();
		player.setInput(' ');

		if (GetAsyncKeyState('A')) {
			player.setDir({ -1,1 });
			player.setAnimRange(7, 13);
			player.setInput('A');
		}
		else if (GetAsyncKeyState('D')) {
			player.setDir({ 1,1 });
			player.setAnimRange(0, 6);
			player.setInput('D');
		}
		if (GetAsyncKeyState('W')) {
			player.setDir({ player.getDir().x,-1 });
			if (player.getDir().x == 0)
				player.setAnimRange(0, 6);
			player.setInput('W');
		}
		else if (GetAsyncKeyState('S')) {
			player.setDir({ player.getDir().x,1 });
			if (player.getDir().x == 0)
				player.setAnimRange(0, 6);
			player.setInput('S');
		}
		 
		player.setSprinting(false);
		if (GetAsyncKeyState(VK_SHIFT)) {
			player.setSprinting(true);
		}

		if (player.getDir() == vec2(0, 0))
			player.setAnimRange(0, 6);

		if (GetAsyncKeyState('F'))
			player.setInput('F');

		player.setInteracting(false);
		if (player.getInput() == 'F')
			if (lastInput != player.getInput())
				player.setInteracting(true);

	}

	void FishState::update(Player& player) {

	}

}