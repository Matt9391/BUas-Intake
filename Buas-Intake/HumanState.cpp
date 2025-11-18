#include "HumanState.h"
#include "Player.h"
#include "surface.h"
#include <Windows.h>

namespace Tmpl8 {

	void HumanState::enter(Player& player) {
		player.setState(0);
	}

	void HumanState::handleInput(Player& player) {
		player.setDir({ 0,0 });

		if (GetAsyncKeyState('A')) {
			player.setDir({ -1,player.getDir().y });
			player.setAnimRange(8, 15);
		}
		else if (GetAsyncKeyState('D')) {
			player.setDir({ 1,player.getDir().y });
			player.setAnimRange(0, 7);
		}
		if (GetAsyncKeyState('W')) {
			player.setDir({ player.getDir().x,-1 });
			if (player.getDir().x == 0)
				player.setAnimRange(24, 31);
		}
		else if (GetAsyncKeyState('S')) {
			player.setDir({ player.getDir().x,1 });
			if (player.getDir().x == 0)
				player.setAnimRange(16, 23);
		}

		if (player.getDir() == vec2(0, 0))
			player.setAnimRange(32, 38);
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