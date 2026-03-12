#include "functions.h"
#include <sstream>
#include <string>
#include <cstdio>
#include <algorithm>

namespace Tmpl8 {

	//copied from Arduino map function
	float mapValue(float value, float inMin, float inMax, float outMin, float outMax) {
		return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
	}

	//constrain the 'value' between min and max values
	float constrain(float value, float min, float max) {
		if (value < min)
			return min;
		if (value > max)
			return max; 
		return value;
	}

	std::string formatCoins(long long coins) {
		std::string text;

		//format coins into K, M, B notation
		if (coins >= 1'000'000'000) {
			double value = coins / 1'000'000'000.0;
			char buf[32];
			snprintf(buf, sizeof(buf), "%.1fB", value);
			text = buf;
		}
		else if (coins >= 1'000'000) {
			double value = coins / 1'000'000.0;
			char buf[32];
			snprintf(buf, sizeof(buf), "%.1fM", value);
			text = buf;
		}
		else if (coins >= 1000) {
			double value = coins / 1'000.0;
			char buf[32];
			snprintf(buf, sizeof(buf), "%.1fK", value);
			text = buf;
		}
		else {
			text = std::to_string(coins);
		}

		return text;

	}

	int getLength(std::string str) {
		return  int(str.length());
	}
	
	int countLines(std::string str) {
		return int(std::count(str.begin(), str.end(), '\n')) + 1;
	}

	int getMaxLengthLines(std::string str) {
	
		std::istringstream stream(str);
		std::string line;
		int maxL = -1;

		while (std::getline(stream, line)) {
			int l = getLength(line);
			if (l > maxL)
				maxL = l;
		}

		return maxL;
	
	}

}