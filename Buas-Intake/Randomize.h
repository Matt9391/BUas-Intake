#include <random>


#pragma once
namespace Tmpl8 {

	class Randomize
	{
	public:
		
		static int randomInt(int min, int max);
		static float randomFloat(float min, float max);

	private:
		static std::mt19937 gen;
	};
}

