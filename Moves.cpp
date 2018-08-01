#include "Moves.h"

void Moves::compute_moves()
{
	set_to_zero( possibleMoves, 4 );

	if ( movesRemaining[0] == movesRemaining[1] )
	{
		for ( int i = 1; i < 5; ++i )
		{
			possibleMoves[i] = movesRemaining[0] * i;
		}
	}
	else
	{
		possibleMoves[0] = movesRemaining[0];
		possibleMoves[1] = movesRemaining[1];
		possibleMoves[2] = movesRemaining[0] + movesRemaining[1];	
	}
}

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
	set_to_zero( possibleMoves, 4 );
}

Moves::Moves( const Moves& m )
{
	for ( int i = 0; i < 4; ++i )
	{
		movesRemaining[i] = m.movesRemaining[i];
		possibleMoves[i] = m.possibleMoves[i];
	}
}

Moves& Moves::operator = ( const Moves& m )
{
	for ( int i = 0; i < 4; ++i )
	{
		movesRemaining[i] = m.movesRemaining[i];
		possibleMoves[i] = m.possibleMoves[i];
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
		if ( possibleMoves[i] == distance ) return true;
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

	compute_moves();
}

void Moves::checker_moved( int distance )
{
	if ( movesRemaining[0] == movesRemaining[1] )
	{
		// the player had doubles
		int movesToRemove = distance / movesRemaining[0];
		for ( int i = 4; i > 4 - movesToRemove; --i )
		{
			movesRemaining[i] = 0;
		}
	}
	else
	{
		if ( movesRemaining[0] + movesRemaining[1] == distance )
		{
			set_to_zero( movesRemaining, 4 );
		}
		else
		{
			for ( int i = 0; i < 2; ++i )
			{
				if ( movesRemaining[i] == distance )
				{
					movesRemaining[i] = 0;
					break;
				}
			}
		}
	}

	compute_moves();
}