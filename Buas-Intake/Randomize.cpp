#include "Randomize.h"

namespace Tmpl8 {
	std::mt19937 Randomize::gen(std::random_device{}());

	int Randomize::randomInt(int min, int max) {
		std::uniform_int_distribution<> distrib(min, max);
		return distrib(gen);
	}

	float Randomize::randomFloat(float min, float max) {
		std::uniform_real_distribution<> distrib(min, max);
		return distrib(gen);
	}
}