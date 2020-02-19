#include "Pathfinder.h"

int Pathfinder::calculateManhattanDistance(int x1, int y1, int x2, int y2)
{
	return (abs(x1 - x2) + abs(y1 - y2)) * 10;
}

bool Pathfinder::isOnOpenList(const Point& point)
{
	return std::find_if(openList.begin(), openList.end(),
		[point](const std::unique_ptr<Node>& o){ return point == o->getPosition(); }) != openList.end();
}

Node* Pathfinder::getNodeFromOpenList(const Point& point)
{
	auto it = std::find_if(openList.begin(), openList.end(),
		[point](const std::unique_ptr<Node>& o) { return point == o->getPosition(); });

	if (it == openList.end())
		return nullptr;

	return it->get();
}

Node* Pathfinder::getNodeFromClosedList(const Point& point)
{
	auto it = std::find_if(closedList.begin(), closedList.end(),
		[point](const std::unique_ptr<Node>& o) { return point == o->getPosition(); });

	if (it == closedList.end())
		return nullptr;

	return it->get();
}

bool Pathfinder::isOnClosedList(const Point& point)
{
	return std::find_if(closedList.begin(), closedList.end(),
		[point](const std::unique_ptr<Node>& o) { return point == o->getPosition(); }) != closedList.end();
}

bool Pathfinder::isInFoundRoute(const Point& point)
{
	return std::find_if(foundRoute.begin(), foundRoute.end(),
		[point](const Point& o) { return point == o; }) != foundRoute.end();
}

bool Pathfinder::isEnd()
{
	return end;
}

bool Pathfinder::isStarted()
{
	return started;
}

Node* Pathfinder::getBestNode()
{
	if (openList.empty())
		return nullptr;

	return std::min_element(openList.begin(), openList.end(),
		[](const std::unique_ptr<Node>& a, const std::unique_ptr<Node>& b) { return a->getF() < b->getF(); })->get();
}

void Pathfinder::removeFromOpenListAndAddToClosed(Node* node)
{
	auto it = std::find_if(openList.begin(), openList.end(),
		[node](const std::unique_ptr<Node>& o) { return node->getPosition() == o->getPosition(); });

	closedList.push_back(std::move(*it));
	openList.erase(it);
}

std::unique_ptr<Node> Pathfinder::makeNode(const Point& point, int g, Node* parent)
{
	int h = 0;
	if (algorithm == A_STAR)
		h = calculateManhattanDistance(point.x, point.y, stop.x, stop.y);

	return std::make_unique<Node>(point.x, point.y, g, h, parent);
}

void Pathfinder::makeRoute(Node* node)
{
	foundRoute.clear();

	Node* nextNode = node;
	while (nextNode = nextNode->getParent())
		foundRoute.push_back(nextNode->getPosition());
}

Pathfinder::Pathfinder(Map& map, Algorithm algorithm) :
	map(map),
	algorithm(algorithm),
	turns({
		(Turn(Point(1, 0), 10)),
		(Turn(Point(0, 1), 10)),
		(Turn(Point(-1, 0), 10)),
		(Turn(Point(0, -1), 10)),
		(Turn(Point(-1, -1), 14)),
		(Turn(Point(1, -1), 14)),
		(Turn(Point(1, 1), 14)),
		(Turn(Point(-1, 1), 14)),
		})
{

}

void Pathfinder::begin(int startX, int startY, int stopX, int stopY)
{
	start.x = startX;
	start.y = startY;
	stop.x = stopX;
	stop.y = stopY;
	openList.clear();
	closedList.clear();
	foundRoute.clear();

	openList.push_back(makeNode(start.x, start.y, 0));
}

void Pathfinder::oneStepSearch()
{
	started = true;
	Node* bestNode;
	if (bestNode = getBestNode())
	{
		removeFromOpenListAndAddToClosed(bestNode);

		if (bestNode->getPosition() == stop)
		{
			makeRoute(bestNode);
			end = true;
		}

		for (auto& turn : turns)
		{
			Point newPoint = bestNode->getPosition() + turn.direction;
			int g = bestNode->getG() + turn.cost;

			if (!map.isWalkable(newPoint))
				continue;

			if (isOnClosedList(newPoint))
				continue;

			if (Node* node = getNodeFromOpenList(newPoint)) //is already in open list
				node->checkGAndReplaceIfBetter(g, bestNode);

			else
				openList.push_back(makeNode(newPoint, g, bestNode));
		}
	}

	else
		end = true;
}

bool Pathfinder::search()
{
	while (!end)
		oneStepSearch();

	return !foundRoute.empty();
}
