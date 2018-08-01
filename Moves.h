class Moves
{
	int movesRemaining[4];
	int possibleMoves[4];

	void compute_moves();
	void set_to_zero( int* arr, int size );

public:
	Moves();
	Moves( const Moves& m );
	Moves& operator = ( const Moves& m );
	~Moves();

	bool has_moves();
	bool can_move_distance( int distance );

	void from_roll( int roll1, int roll2 );
	void checker_moved( int distance );
};