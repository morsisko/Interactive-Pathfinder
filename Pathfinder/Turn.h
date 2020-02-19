#pragma once
#include "Point.h"
struct Turn
{
	Point direction;
	int cost;

	Turn(Point direction, int cost);
};

