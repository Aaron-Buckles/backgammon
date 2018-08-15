#include "Moves.h"

void Moves::set_to_zero( int* arr, int size )
{
	for ( int i = 0; i < size; ++i )
	{
		arr[i] = 0;
	}
}

Moves::Moves()
{
	set_to_zero( movesRemaining, 4 );
}

Moves::Moves( const Moves& m )
{
	for ( int i = 0; i < 4; ++i )
	{
		movesRemaining[i] = m.movesRemaining[i];
	}
}

Moves& Moves::operator = ( const Moves& m )
{
	for ( int i = 0; i < 4; ++i )
	{
		movesRemaining[i] = m.movesRemaining[i];
	}
	return *this;
}

Moves::~Moves() {}

bool Moves::has_moves()
{
	for ( int i = 0; i < 4; ++i )
	{
		if ( movesRemaining[i] != 0 ) return true;
	}
	return false;
}

bool Moves::can_move_distance( int distance )
{
	for ( int i = 0; i < 4; ++i )
	{
		if ( movesRemaining[i] == distance ) return true;
	}
	return false;
}

void Moves::from_roll( int roll1, int roll2 )
{
	set_to_zero( movesRemaining, 4 );

	movesRemaining[0] = roll1;
	movesRemaining[1] = roll2;

	if ( roll1 == roll2 )
	{
		movesRemaining[2] = roll1;
		movesRemaining[3] = roll1;
	}
}

void Moves::checker_moved( int distance )
{
	for ( int i = 0; i < 4; ++i )
	{
		if ( movesRemaining[i] == distance )
		{
			movesRemaining[i] = 0;
			break;
		}
	}
}