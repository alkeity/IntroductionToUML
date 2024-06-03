#include<iostream>
#include<random>
#include "ShapeFactory.h"
#define MAX_SIDE_SIZE 100

using std::cout;
using std::cin;
using std::endl;

#define MIN_X 50
#define MIN_Y 50
#define MAX_X 750
#define MAX_Y 550

Color colors[12]{ RED, ORANGE, YELLOW, GREEN, SKYBLUE, BLUE, VIOLET, PURPLE, PINK, BEIGE, LIME, GOLD };

ShapeFactory::~ShapeFactory()
{
	cout << this << ": shape factory destroyed\n";
}


MyShape* CircleFactory::create()
{
	return new MyCircle(
		rand() % MAX_SIDE_SIZE, colors[rand() % 12],
		Vector2{ (float)(MIN_X + rand() % (MAX_X - MIN_X + 1)), (float)(MIN_Y + rand() % (MAX_Y - MIN_Y + 1)) }
	);
}

MyShape* SqTriangleFactory::create()
{
	return new SquaredTriangle(
		rand() % MAX_SIDE_SIZE, rand() % MAX_SIDE_SIZE, colors[rand() % 12],
		Vector2{ (float)(MIN_X + rand() % (MAX_X - MIN_X + 1)), (float)(MIN_Y + rand() % (MAX_Y - MIN_Y + 1)) }
	);
}

MyShape* RectangleFactory::create()
{
	return new MyRectangle(
		rand() % MAX_SIDE_SIZE, rand() % MAX_SIDE_SIZE, colors[rand() % 12],
		Vector2{ (float)(MIN_X + rand() % (MAX_X - MIN_X + 1)), (float)(MIN_Y + rand() % (MAX_Y - MIN_Y + 1)) }
	);
}

MyShape* SquareFactory::create()
{
	return new MySquare(
		rand() % MAX_SIDE_SIZE, colors[rand() % 12],
		Vector2{ (float)(MIN_X + rand() % (MAX_X - MIN_X + 1)), (float)(MIN_Y + rand() % (MAX_Y - MIN_Y + 1)) }
	);
}
