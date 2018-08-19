#include "Backgammon.h"

void Backgammon::setup_board()
{
	board[1].amount = 2;
	board[12].amount = 5;
	board[17].amount = 3;
	board[19].amount = 5;

	board[24].player = false;
	board[13].player = false;
	board[8].player = false;
	board[6].player = false;
	board[24].amount = 2;
	board[13].amount = 5;
	board[8].amount = 3;
	board[6].amount = 5;
}

bool Backgammon::all_checkers_home( bool p )
{
	if ( p )
	{
		for ( int i = 0; i < 19; ++i )
		{
			if ( has_checker_on_point( p, i ) ) return false;
		}
	}
	else
	{
		for ( int i = 7; i < TOTAL_POINTS; ++i )
		{
			if ( has_checker_on_point( p, i ) ) return false;
		}
	}
	return true;
}

Backgammon::Backgammon() : board( new Point[TOTAL_POINTS] ), player1Captured( 0 ), 
	player2Captured( 0 ), moves(), player( true ) {}

Backgammon::Backgammon( const Backgammon& b ) : board( new Point[TOTAL_POINTS] ), player1Captured( b.player1Captured ),
	player2Captured( b.player2Captured ), moves(), player( true )
{
	for ( int i = 0; i < TOTAL_POINTS; ++i )
	{
		board[i] = b.board[i];
	}

	moves = b.moves;
}

Backgammon& Backgammon::operator = ( const Backgammon& b )
{
	for ( int i = 0; i < TOTAL_POINTS; ++i )
	{
		board[i] = b.board[i];
	}

	moves = b.moves;
	player1Captured = b.player1Captured;
	player2Captured = b.player2Captured;
	player = true;

	return *this;
}

Backgammon::~Backgammon()
{
	delete[] board;
}

void Backgammon::start( bool firstPlayer, int roll1, int roll2 )
{
	setup_board();
	player = firstPlayer;
	rolled( roll1, roll2 );
}

Point& Backgammon::operator [] ( int point )
{
	return board[point];
}

int Backgammon::checkers_on_bar( bool p )
{
	return p ? player1Captured : player2Captured;
}

bool Backgammon::player_has_moves( bool p )
{
	// Don't waste any time checking because the player ran out of rolls
	if ( !moves.has_moves() )
	{
		if (DEBUG) std::cout << "The player does not have any rolls left" << std::endl;
		return false;
	}

	// When the player has checkers on the bar
	if ( (p && player1Captured > 0) || (!p && player2Captured > 0) )
	{
		std::cout << "Player has checkers on bar" << std::endl;
		for ( int i = 0; i < 4; ++i )
		{
			int pointIndex = p ? (moves.movesRemaining[i]) : (TOTAL_POINTS - moves.movesRemaining[i] - 1);
			if ( pointIndex == 0 || pointIndex == TOTAL_POINTS - 1 ) continue;
			std::cout << "PointIndex: " << pointIndex << std::endl;

			if ( board[pointIndex].player == p || board[pointIndex].amount <= 1 )
			{
				return true;
			}
		}

		if (DEBUG) std::cout << "The player cannot move its checker off the bar" << std::endl;
		return false;
	}

	// Brute force checking of all from all points to all points
	// TODO: Find a better/more efficient solution
	for ( int from = 0; from < TOTAL_POINTS; ++from )
	{
		if ( board[ from ].player == p && board[ from ].amount > 0 )
		{
			if ( p )
			{
				for ( int to = 0; to < TOTAL_POINTS; ++to )
				{
					if ( can_move_checker( p, from, to ) ) return true;
				}
			}
			else
			{
				for ( int to = TOTAL_POINTS - 1; to >= 0; --to )
				{
					if ( can_move_checker( p, from, to ) ) return true;
				}
			}
		}
	}

	return false;
}

// TODO: Make this member function smaller (break up into functions)
bool Backgammon::can_move_checker( bool p, int from, int to )
{
	// The player must have a checker on the point they're moving from
	if ( from == 0 || from == TOTAL_POINTS - 1 )
	{
		if ( (p && player1Captured <= 0) || (!p && player2Captured <= 0) ) 
		{
			if (DEBUG) std::cout << "Player does not have checkers on the bar" << std::endl;
			return false;
		}
	}
	else
	{
		if ( !has_checker_on_point( p, from ) ) 
		{
			if (DEBUG) std::cout << "Player does not have checker on this point" << std::endl;
			return false;
		}
	}

	// Can only bear off if all checkers are home
	if ( to == 0 || to == TOTAL_POINTS - 1 )
	{
		if ( !all_checkers_home(p) )
		{
			if (DEBUG) std::cout << "Cannot bear off because not all checkers are home" << std::endl;
			return false;
		}
	}

	// Check the direction
	if ( (p && from >= to) || (!p && from <= to) )
	{
		if (DEBUG) std::cout << "Wrong direction" << std::endl;
		return false;
	}

	// Check that the checker can move this distance
	if ( !moves.can_move_exact_distance( std::abs(from - to) ) ) 
	{
		if ( to == 0 || to == TOTAL_POINTS - 1 )
		{
			if ( !moves.can_move_distance( std::abs(from - to) ) )
			{
				return false;
			}
		}
		else
		{
			if (DEBUG) std::cout << "Cannot move distance of " << std::abs(from - to) << std::endl;
			return false;
		}
	}

	// The player can only move to a point that is NOT controlled by the OTHER player
	if ( board[to].player == !p && board[to].amount > 1 )
	{
		if (DEBUG) std::cout << "The point moving to is controlled by the other player" << std::endl;
		return false;
	}

	return true;
}

bool Backgammon::has_checker_on_point( bool p, int point )
{
	if ( point > 0 && point < TOTAL_POINTS - 1 )
	{
		return board[point].player == p && board[point].amount > 0;
	}
	return false;
}

void Backgammon::move_checker( bool p, int from, int to )
{
	// Remove a checker from the point the player is moving from
	if ( from != 0 && from != TOTAL_POINTS - 1 )
	{
		--board[ from ].amount;
	}
	else
	{
		p ? --player1Captured : --player2Captured;
	}

	// Add a checker to the point the player is moving to
	// or if landing on a blot, add to the other players bar
	if ( board[ to ].is_blot(p) )
	{
		p ? ++player2Captured : ++player1Captured;
	}
	else
	{
		++board[ to ].amount;
	}
	board[ to ].player = p;

	// Update the Moves object with the distance moved
	moves.checker_moved( std::abs( from - to ) );

	if (DEBUG)
	{
		std::cout << "Moves Remaining: ";
		for ( int i = 0; i < 4; ++i )
		{
			if ( moves.movesRemaining[i] != 0 )
				std::cout << moves.movesRemaining[i] << " ";
		} 
		std::cout << "\n";
	}
}

void Backgammon::rolled( int roll1, int roll2 )
{
	moves.from_roll( roll1, roll2 );
}

void Backgammon::next_player()
{
	player = !player;
}

bool Backgammon::game_over()
{
	return board[ TOTAL_POINTS - 1 ].amount == 15 || board[0].amount == 15;
}