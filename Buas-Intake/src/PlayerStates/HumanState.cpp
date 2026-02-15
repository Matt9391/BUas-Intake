#include <Windows.h>
#include "../../tmpl8/template.h"
#include "../Gameplay/Player.h"

#include "HumanState.h"

namespace Tmpl8 {

	void HumanState::enter(Player& player) {
		player.setSprinting(false);
		this->sprintSpeed = 0.25;
	}

	void HumanState::handleInput(Player& player) {
		//reset player direction
		player.setDir({ 0,0 });

		//read user input
		char lastInput = player.getInput();
		player.setInput(' ');

		
		//set player direction and animation based on input
		if (GetAsyncKeyState('A')) {
			player.setDir({ -1,player.getDir().y });
			player.setAnimRange(8, 15);
			player.setInput('A');
		}
		else if (GetAsyncKeyState('D')) {
			player.setDir({ 1,player.getDir().y });
			player.setAnimRange(0, 7);
			player.setInput('D');
		}
		if (GetAsyncKeyState('W')) {
			player.setDir({ player.getDir().x,-1 });
			//if moving diagonally, keep the horizontal animation
			if (player.getDir().x == 0)
				player.setAnimRange(24, 31);
			player.setInput('W');
		}
		else if (GetAsyncKeyState('S')) {
			player.setDir({ player.getDir().x,1 });
			//if moving diagonally, keep the horizontal animation
			if (player.getDir().x == 0)
				player.setAnimRange(16, 23);
			player.setInput('S');
		}

		player.setSprinting(false);
		if (GetAsyncKeyState(VK_SHIFT)) {
			player.setSprinting(true);
		}
		 
		//if idle, set idle animation
		if (player.getDir() == vec2(0, 0)) 
			player.setAnimRange(32, 38);

		if(GetAsyncKeyState('F'))
			player.setInput('F');

		player.setInteracting(false);
		if (player.getInput() == 'F')
			//check for interaction only if the input changed (so the player can't hold it)
			if (lastInput != player.getInput()) 
				player.setInteracting(true);
		
	}
}