#include "HumanState.h"
#include "Player.h"
#include "surface.h"
#include <Windows.h>

namespace Tmpl8 {

	void HumanState::enter(Player& player) {
		//player.setState(0);
		printf("Sono umano\n");
		player.setSprinting(false);
		this->sprintSpeed = 0.25;
	}

	void HumanState::handleInput(Player& player) {
		player.setDir({ 0,0 });

		char lastInput = player.getInput();
		player.setInput(' ');

		

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
			if (player.getDir().x == 0)
				player.setAnimRange(24, 31);
			player.setInput('W');
		}
		else if (GetAsyncKeyState('S')) {
			player.setDir({ player.getDir().x,1 });
			if (player.getDir().x == 0)
				player.setAnimRange(16, 23);
			player.setInput('S');
		}

		player.setSprinting(false);
		if (GetAsyncKeyState(VK_SHIFT)) {
			player.setSprinting(true);
		}
		 
		if (player.getDir() == vec2(0, 0))
			player.setAnimRange(32, 38);

		if(GetAsyncKeyState('F'))
			player.setInput('F');

		player.setInteracting(false);
		if (player.getInput() == 'F')
			if (lastInput != player.getInput()) 
				player.setInteracting(true);
		
	}

	void HumanState::update(Player& player) {

	}

	//void HumanState::draw(Player& player, Surface* screen, vec2 cameraOffset) {
	//	vec2 pos = player.getPos();
	//	vec2 size = player.getSize();
	//	float yDrawPos = pos.y - size.y - size.y / 2.f - cameraOffset.y;
	//	float xDrawPos = pos.x - size.x / 2.f - cameraOffset.x;
	//	if (this->humanSprite == nullptr)
	//		return;
	//	(*this->humanSprite).Draw(screen, xDrawPos, yDrawPos);
	//}

}