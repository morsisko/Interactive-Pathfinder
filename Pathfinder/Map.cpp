#include "Map.h"

Map::Map(int x, int y) :
	width(x),
	height(y)
{
	data.resize(y);

	for (int i = 0; i < y; i++)
	{
		data[i].resize(x);
		for (int j = 0; j < x; j++)
			data[i][j] = true;
	}
}

bool Map::isWalkable(int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return false;

	return data[y][x];
}

bool Map::isWalkable(const Point& point)
{
	return isWalkable(point.x, point.y);
}

void Map::changeStateOfCell(int x, int y, bool walkable)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;

	data[y][x] = walkable;
}

int Map::getWidth()
{
	return width;
}

int Map::getHeight()
{
	return height;
}
