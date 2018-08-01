#include "Point.h"

Point::Point( bool initialPlayer = true, bool initialAmount = 0 ) : player( initialPlayer ), amount( initialAmount ) {}

Point::Point( const Point& p ) : player( p.player ), amount( p.amount ) {}

Point& Point::operator = ( const Point& p )
{
	player = p.player;
	amount = p.amount;
	return *this;
}

Point::~Point() {}

bool Point::is_blot( bool p )
{
	return p != player && amount == 1;
}

bool Point::is_open()
{
	return amount == 0;
}

bool Point::has_checkers( bool p, int n = 1 )
{
	return p == player && amount >= n; 
}