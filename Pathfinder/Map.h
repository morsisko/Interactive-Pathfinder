#pragma once
#include <vector>
#include "Point.h"

class Map
{
private:
	int width;
	int height;
	std::vector<std::vector<bool>> data;

public:
	Map(int x, int y);
	bool isWalkable(int x, int y);
	bool isWalkable(const Point& point);
	void changeStateOfCell(int x, int y, bool walkable);
	int getWidth();
	int getHeight();
};

