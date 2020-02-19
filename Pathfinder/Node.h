#pragma once
#include "Point.h"
class Node
{
private:
	Node* parent = nullptr;
	int x;
	int y;
	int g;
	int h;

public:
	Node(int x, int y, int g, int h, Node* parent = nullptr);
	Point getPosition();
	int getG();
	int getF();
	Node* getParent();
	void checkGAndReplaceIfBetter(int newG, Node* newParent);

};

