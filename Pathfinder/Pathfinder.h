#pragma once
#include "Map.h"
#include "Node.h"
#include "Point.h"
#include "Turn.h"
#include <memory>
#include <list>
#include <algorithm>
#include <math.h>
#include <array>

class Pathfinder
{
public:
	enum Algorithm
	{
		A_STAR = 0,
		DIJKSTRA
	};

private:
	bool end = false;
	bool started = false;
	Map& map;
	std::array<Turn, 8> turns;
	std::list<std::unique_ptr<Node>> openList;
	std::list<std::unique_ptr<Node>> closedList;
	std::vector<Point> foundRoute;
	Algorithm algorithm;

	Point start, stop;

	int calculateManhattanDistance(int x1, int y1, int x2, int y2);
	Node* getBestNode();
	void removeFromOpenListAndAddToClosed(Node* node);
	std::unique_ptr<Node> makeNode(const Point& point, int g, Node* parent = nullptr);
	void makeRoute(Node* node);
public:
	Pathfinder(Map& map, Algorithm algorithm = A_STAR);
	void begin(int startX, int startY, int stopX, int stopY);
	void oneStepSearch();
	bool search();
	bool isOnOpenList(const Point& point);
	bool isOnClosedList(const Point& point);
	bool isInFoundRoute(const Point& point);
	bool isEnd();
	bool isStarted();
	Node* getNodeFromOpenList(const Point& point);
	Node* getNodeFromClosedList(const Point& point);
};

