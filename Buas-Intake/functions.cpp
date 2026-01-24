#include "functions.h"

namespace Tmpl8 {

	float mapValue(float value, float inMin, float inMax, float outMin, float outMax) {
		return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
	}

	float constrain(float value, float min, float max) {
		if (value < min)
			return min;
		if (value > max)
			return max; 
		return value;
	}

}