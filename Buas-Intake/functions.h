#pragma once

namespace Tmpl8 {

	//map a 'value' from one range to another
	float mapValue(float value, float inMin, float inMax, float outMin, float outMax);
	//contrain the 'value' between min and max values
	float constrain(float value, float min, float max); 
 
}
