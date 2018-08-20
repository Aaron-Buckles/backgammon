#ifndef POINT_H
#define POINT_H

struct Point
{
	bool player;
	int amount;

	Point( bool initialPlayer, bool initialAmount );
	Point( const Point& p );
	Point& operator = ( const Point& p );
	~Point();

	bool is_blot( bool p );
};

#endif