#include <DataTypes/PlayerVisual.h>
#include <DataTypes/SceneType.h>
#include <Gameplay/Player.h>
#include <InteractableObjects/InteractableObject.h>
#include "Gate.h"

#include <game.h>
#include <template.h>


namespace Tmpl8 {

	Gate::Gate(int type, vec2 pos, vec2 size) :
		InteractableObject(type, pos, size)
	{
		this->textHover = "Press 'F' to change form";
		this->textHoverPosition = vec2(pos.x + size.x / 2 - 64, pos.y);
	}
	
	//if the player is human, change to fish scene, else change to human scene
	void Gate::interact(Player& player, Game& game) {
		if (player.getPlayerVisual() == PlayerVisual::Human) {
			game.setPendingScene(SceneType::SceneFish);
		}
		else {
			game.setPendingScene(SceneType::SceneHuman);
		} 
	} 

}