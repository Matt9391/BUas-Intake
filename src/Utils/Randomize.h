#include <random>


#pragma once
namespace Tmpl8 {

	//Randomize class for generating random numbers
	class Randomize
	{
	public:
		static int randomInt(int min, int max);
		static float randomFloat(float min, float max);

	private:
		//random number generator (copied online)
		static std::mt19937 gen;
	}; 
}

