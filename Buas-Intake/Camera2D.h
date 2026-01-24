#include "template.h"

#pragma once
namespace Tmpl8 {
	class Camera2D
	{
	public:
		Camera2D(vec2 pos, vec2 size); 

		void follow(vec2 target);

		void setWorldSize(vec2 size);

		vec2 getPos();

	private:
		float constrain(float value, float min, float max);
	 	
		vec2 pos;
		vec2 size;
		vec2 worldSize;
	};
}

