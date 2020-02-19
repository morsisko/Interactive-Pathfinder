#include "Node.h"

Node::Node(int x, int y, int g, int h, Node* parent) :
	x(x),
	y(y),
	g(g),
	h(h),
	parent(parent)
{

}

Point Node::getPosition()
{
	return Point(x, y);
}

int Node::getG()
{
	return g;
}

int Node::getF()
{
	return g + h;
}

Node* Node::getParent()
{
	return parent;
}

void Node::checkGAndReplaceIfBetter(int newG, Node* newParent)
{
	if (newG < g)
	{
		g = newG;
		parent = newParent;
	}
}
