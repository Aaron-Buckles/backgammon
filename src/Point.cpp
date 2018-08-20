#include "../include/Point.h"

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
	return player != p && amount == 1;
}