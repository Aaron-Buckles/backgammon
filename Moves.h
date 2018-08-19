struct Moves
{
	int movesRemaining[4];

	Moves();
	Moves( const Moves& m );
	Moves& operator = ( const Moves& m );
	~Moves();

	bool has_moves();
	bool can_move_exact_distance( int distance ); // uses ==
	bool can_move_distance( int distance ); // ex. can move distance of 3 if has move of 3, 4, 5, 6

	void from_roll( int roll1, int roll2 );
	void checker_moved( int distance );
	
private:
	void set_to_zero( int* arr, int size );
};