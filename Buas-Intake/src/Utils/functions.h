#pragma once
#include <string>

namespace Tmpl8 {

	//map a 'value' from one range to another
	float mapValue(float value, float inMin, float inMax, float outMin, float outMax);
	//contrain the 'value' between min and max values
	float constrain(float value, float min, float max); 

	//format coins in string, example: 1600 -> 1.6K
	std::string formatCoins(long long coins);

	//get the length of any given string
	int getLength(std::string str);
 
}
