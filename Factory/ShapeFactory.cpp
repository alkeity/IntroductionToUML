#include<iostream>
#include<random>
#include "ShapeFactory.h"

using std::cout;
using std::cin;
using std::endl;

Color colors[12]{ RED, ORANGE, YELLOW, GREEN, SKYBLUE, BLUE, VIOLET, PURPLE, PINK, BEIGE, LIME, GOLD };

ShapeFactory::~ShapeFactory()
{
	cout << this << ": shape factory destroyed\n";
}


MyShape* CircleFactory::create()
{
	return new MyCircle(rand() % MAX_SIDE_SIZE, colors[rand() % 12]);
}

MyShape* SqTriangleFactory::create()
{
	return new SquaredTriangle(rand() % MAX_SIDE_SIZE, rand() % MAX_SIDE_SIZE, colors[rand() % 12]);
}

MyShape* RectangleFactory::create()
{
	return new MyRectangle(rand() % MAX_SIDE_SIZE, rand() % MAX_SIDE_SIZE, colors[rand() % 12]);
}

MyShape* SquareFactory::create()
{
	return new MySquare(rand() % MAX_SIDE_SIZE, colors[rand() % 12]);
}
