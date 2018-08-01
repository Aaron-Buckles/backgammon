#include <random>
#include <chrono>

class Dice
{
	std::default_random_engine engine;
	std::uniform_int_distribution<int> distribution;

public:
	Dice( int min, int max );
	int roll();
	~Dice();
};