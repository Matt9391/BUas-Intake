#include "Camera2D.h"

namespace Tmpl8 {
	Camera2D::Camera2D(vec2 pos, vec2 size) :
		pos(pos),
		size(size),
		worldSize({0,0})
		{} 

	void Camera2D::follow(vec2 target) {
		this->pos.x = target.x - this->size.x / 2;
		this->pos.y = target.y - this->size.y / 2;

		this->pos.x = this->constrain(this->pos.x, 0, this->worldSize.x - this->size.x);
		this->pos.y = this->constrain(this->pos.y, 0, this->worldSize.y - this->size.y);
	}
 
	vec2 Camera2D::getPos() {
		return this->pos;
	}

	void Camera2D::setWorldSize(vec2 size) {
		this->worldSize = size * 32;
		printf("WORLDSIZES: %.2f, %.2f\n", this->worldSize.x, this->worldSize.y);
	}

	float Camera2D::constrain(float value, float min, float max) {
		if (value < min)
			return min;
		if (value > max)
			return max;
		return value;
	}
	
}