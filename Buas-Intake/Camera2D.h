#include "template.h"

#pragma once
namespace Tmpl8 {
	class Camera2D
	{
	public:
		Camera2D(vec2 pos, vec2 size);

		void follow(vec2 target);
		
		vec2 getPos();

		void SetPosition(vec2 nextPos);
	private:
		vec2 pos;
		vec2 size;
	};
}

