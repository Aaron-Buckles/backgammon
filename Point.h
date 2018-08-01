struct Point
{
	bool player;
	int amount;

	Point( bool initialPlayer, bool initialAmount );
	Point( const Point& p );
	Point& operator = ( const Point& p );
	~Point();

	bool is_blot( bool p ); // checks that the point has exactly 1 of the other player
	bool is_open();
	bool has_checkers( bool p, int n ); // checks that the point as n or more checkers of type p
};