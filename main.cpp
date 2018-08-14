#include <iostream>
#include "Backgammon.cpp"

class BackgammonUI
{
	Backgammon backgammon;
	int checkersPerPoint;
	int roll1;
	int roll2;
	Dice die;

	void draw()
	{
		draw_info();
		draw_board();
	}

	void draw_info()
	{
		std::cout << "\n";
		std::cout << "Player: " << symbol( backgammon.player ) << std::endl;
		std::cout << "Roll: " << roll1 << " " << roll2 << std::endl;
		std::cout << "\n";
	}

	void draw_board()
	{
		std::cout << " " << symbol( false ) << "'s home" << std::endl;
		std::cout << " a b c d e f g  h i j k l m" << std::endl;

		for ( int row = 0; row < checkersPerPoint; ++row )
		{
			for ( int point = 0; point < 13; ++point ) draw_checker( row, point, 7 );
			std::cout << "\n";
		}

		draw_point_overflow( 0, 13, 1, 7 );
		draw_bar();
		draw_point_overflow( TOTAL_POINTS - 1, 13, -1, 18 );

		for ( int row = checkersPerPoint - 1; row >= 0; --row )
		{
			for ( int point = TOTAL_POINTS - 1; point >= 13; --point ) draw_checker( row, point, 18 );
			std::cout << "\n";
		}

		std::cout << " z y x w v u t  s r q p o n" << std::endl;
		std::cout << " " << symbol( true ) << "'s home" << std::endl;
	}

	void draw_checker( int row, int point, int bar )
	{
		if ( point == bar ) std::cout << "|";

		if ( backgammon[point].amount - row > 0 )
			std::cout << "|" << symbol( backgammon[point].player );
		else
			std::cout << "| ";
	}

	void draw_point_overflow( int start, int end, int direction, int bar )
	{
		for ( int point = start; point != end; point += direction )
		{
			if ( point == bar ) std::cout << " ";

			if ( backgammon[point].amount - checkersPerPoint > 0 )
			{
				std::cout << "+" << backgammon[point].amount - checkersPerPoint;
			}
			else
			{
				std::cout << "  ";
			}
		}
		std::cout << "\n";
	}

	void draw_bar( )
	{
		for ( int i = 0; i < backgammon.checkers_on_bar(true); ++i ) std::cout << symbol( true );
		std::cout << "\n";
		for ( int i = 0; i < backgammon.checkers_on_bar(false); ++i ) std::cout << symbol( false );
		std::cout << "\n";
	}

	char symbol( bool player )
	{
		return player ? 'X' : 'O';
	}

	void roll()
	{
		roll1 = die.roll();
		roll2 = die.roll();
		std::cout << symbol( backgammon.player ) << " rolled a " << roll1 << " and a " << roll2;
		backgammon.rolled( roll1, roll2 );
	}

	int read_from()
	{
		if ( backgammon.checkers_on_bar( backgammon.player ) > 0 )
		{
			return backgammon.player ? 0 : TOTAL_POINTS - 1;
		}

		std::string input;
		while ( true )
		{
			std::cout << "From ('b' - 'y'): ";
			std::cin >> input;
			int from = input[0] - 97;

			if ( from < 1 || from >= TOTAL_POINTS - 1 )
			{
				std::cout << "Must be between 'b' and 'y'... Try again" << std::endl;
				continue;
			}

			if ( !backgammon.has_checker_on_point( backgammon.player, from ) )
			{
				std::cout << "Must have a checker on specified point... Try again" << std::endl;
				continue;
			}
			
			return from;
		}
	}

	int read_to( int& from )
	{
		std::string input;
		while ( true )
		{
			std::cout << "To ('a' - 'z' and 'cancel' to choose from again): ";
			std::cin >> input;

			if ( input == "cancel")
			{
				from = read_from();
				continue;
			}

			int to = input[0] - 97;

			if ( to < 0 || to >= TOTAL_POINTS )
			{
				std::cout << "Must be between 'a' and 'z'... Try again" << std::endl;
				continue;
			}

			if ( !backgammon.can_move_checker( backgammon.player, from, to ) )
			{
				std::cout << "Cannot move checker to this point... Try again" << std::endl;
				continue;
			}

			return to;
		}
	}

	void game_loop()
	{
		while ( !backgammon.game_over() )
		{
			while ( backgammon.player_has_moves( backgammon.player ) )
			{
				draw();

				int from = read_from();
				int to = read_to( from );

				backgammon.move_checker( backgammon.player, from, to );
			}

			std::cout << "Next player" << std::endl;
			std::cout << backgammon.player << std::endl;
			backgammon.next_player();
			std::cout << backgammon.player << std::endl;
			roll();
		}

		draw();
		std::cout << "Game over!" << std::endl;
	}

public:
	BackgammonUI( Backgammon b, int newCheckersPerPoint ) : backgammon( b ), checkersPerPoint( newCheckersPerPoint ),
		roll1( 0 ), roll2( 0 ), die( 1, 6 ) {}
	
	~BackgammonUI() {}

	void start()
	{
		bool firstPlayer = true;

		while ( true )
		{
			roll1 = die.roll();
			roll2 = die.roll();

			if ( roll1 > roll2 )
			{
				break;
			}
			else if ( roll2 > roll1 )
			{
				firstPlayer = false;
				break;
			}
		}

		std::cout << symbol( true ) << " rolled a " << roll1 << std::endl;
		std::cout << symbol( false ) << " rolled a " << roll2 << std::endl;

		backgammon.start( firstPlayer, roll1, roll2 );
		game_loop();
	}
};

int main()
{
	Backgammon b;
	BackgammonUI game( b, 5 );
	game.start();
	return 0;
}