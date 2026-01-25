#include "./tmpl8/template.h"

#pragma once
namespace Tmpl8 {
	class Camera2D
	{
	public:
		Camera2D(vec2 pos, vec2 size); 

		//makes the camera follow the target aka player
		void follow(vec2 target);

		//sets camera bounds based on the map size
		void setWorldSize(vec2 size);

		//return the position of the camera
		vec2 getPos();

	private:
		vec2 pos; //camera position
		vec2 size; //camera size, screen pixels (x,y)
		vec2 worldSize; //map numbers of tiles (x,y) * tileSize
	};
}

