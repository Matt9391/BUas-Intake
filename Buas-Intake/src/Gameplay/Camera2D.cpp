#include "../../tmpl8/template.h"
#include "../Utils/MapHandler.h"
#include "../Utils/functions.h"

#include "Camera2D.h"

namespace Tmpl8 {
	Camera2D::Camera2D(vec2 pos, vec2 size) :
		pos(pos),
		size(size),
		worldSize({0,0})
		{} 

	void Camera2D::follow(vec2 target) {
		// "-this->size / 2" because the pivot (of the camera) is in the top-left corner
		this->pos.x = target.x - this->size.x / 2;
		this->pos.y = target.y - this->size.y / 2;

		//constrain the camera within the world bounds:
		//camera position must be >= 0 and <= world size minus camera size
		this->pos.x = constrain(this->pos.x, 0, this->worldSize.x - this->size.x);
		this->pos.y = constrain(this->pos.y, 0, this->worldSize.y - this->size.y);
	}
 
	vec2 Camera2D::getPos() {
		return this->pos;
	}

	void Camera2D::setWorldSize(vec2 size) {
		//multiply the number of tiles on the x and y axes by the tile size
		this->worldSize = size * float(MapHandler::tileSize);
	}

	
}