#include "Camera2D.h"

namespace Tmpl8 {
	Camera2D::Camera2D(vec2 pos, vec2 size) :
		pos(pos),
		size(size)
		{}

	void Camera2D::follow(vec2 target) {
		this->pos.x = target.x - this->size.x / 2;
		this->pos.y = target.y - this->size.y / 2;
	}

	vec2 Camera2D::getPos() {
		return this->pos;
	}

	
}