#include <PlayerStates/PlayerState.h>

namespace Tmpl8 {
	
	PlayerState::PlayerState() :
		sprintSpeed(0.f)
	{}

	float PlayerState::getSprintSpeed(){
		return sprintSpeed;
	} 
} 