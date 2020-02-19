#pragma once
struct Point
{
	int x;
	int y;

	Point(int x = 0, int y = 0);
};

Point operator+(const Point& lhs, const Point& rhs);
bool operator==(const Point& lhs, const Point& rhs);


