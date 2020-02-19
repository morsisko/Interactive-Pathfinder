#include "Point.h"

Point::Point(int x, int y) :
	x(x),
	y(y)
{
}

Point operator+(const Point& lhs, const Point& rhs)
{
	return Point{ lhs.x + rhs.x, lhs.y + rhs.y };
}

bool operator==(const Point& lhs, const Point& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
