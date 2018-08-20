#ifndef BACKGAMMON_H
#define BACKGAMMON_H

#define DEBUG false
#define TOTAL_POINTS 26

#include "../include/Point.h"
#include "../include/Moves.h"

class Backgammon
{
	Point* board;
	int player1Captured;
	int player2Captured;
	Moves moves;

	void setup_board();
	bool all_checkers_home( bool p );

public:
	bool player;

	Backgammon();
	Backgammon( const Backgammon& b );
	Backgammon& operator = ( const Backgammon& b );
	~Backgammon();

	void start( bool firstPlayer, int roll1, int roll2 );

	Point& operator [] ( int point );
	int checkers_on_bar( bool p );

	bool player_has_moves( bool p );
	bool can_move_checker( bool p, int from, int to );
	bool game_over();
	bool has_checker_on_point( bool p, int point );

	void move_checker( bool p, int from, int to );
	void rolled( int roll1, int roll2 );
	void next_player();
};

#endif