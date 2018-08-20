#include "../include/Dice.h"

Dice::Dice( int min, int max ) : engine(), distribution( std::uniform_int_distribution<int>(min, max) ) 
{
	// I am kind of confused by std::chrono
	engine.seed( std::chrono::system_clock::now().time_since_epoch().count() );
}

int Dice::roll()
{
	return distribution( engine );
}

Dice::~Dice() {}