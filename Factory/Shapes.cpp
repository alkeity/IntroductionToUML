#include "Shapes.h"

int MyShape::checkSideSize(int side)
{
	if (side < MIN_SIZE) { return MIN_SIZE; }
	else if (side > MAX_SIDE_SIZE) { return MAX_SIDE_SIZE; }
	else { return side; }
}

void MyShape::setColor(Color color)
{
	this->color = color;
}

MyCircle::MyCircle(int radius, Color color)
{
	setRadius(radius);
	setColor(color);
}

void MyCircle::setRadius(int radius) { this->radius = checkSideSize(radius); }

const int& MyCircle::getRadius() const { return radius; }

int MyCircle::getDiameter() const { return radius * 2; }

double MyCircle::getArea() const
{
	return std::numbers::pi * (radius * radius);
}

double MyCircle::getPerimeter() const
{
	return 2 * std::numbers::pi * radius;
}

void MyCircle::draw(Vector2 position) const
{
	DrawCircle(position.x, position.y, radius, color);
}

SquaredTriangle::SquaredTriangle(int sideA, int sideB, Color color)
{
	setColor(color);
	setSideA(sideA);
	setSideB(sideB);
}

void SquaredTriangle::setSideA(int side) { sideA = checkSideSize(side); }
void SquaredTriangle::setSideB(int side) { sideB = checkSideSize(side); }

const int& SquaredTriangle::getSideA() const { return sideA; }
const int& SquaredTriangle::getSideB() const { return sideB; }

double SquaredTriangle::getSideC() const
{
	return sqrt(sideA * sideA + sideB * sideB);
}

double SquaredTriangle::getArea() const
{
	return (sideA * sideB) / 2;
}

double SquaredTriangle::getPerimeter() const
{
	return sideA + sideB + getSideC();
}

void SquaredTriangle::draw(Vector2 position) const
{
	Vector2 pos1{ position.x + sideB, position.y };
	Vector2 pos2{ position.x, position.y + sideA };
	DrawTriangle(pos1, position, pos2, color);
}

MyRectangle::MyRectangle(int sideA, int sideB, Color color)
{
	setSideA(sideA);
	setSideB(sideB);
	setColor(color);
}

void MyRectangle::setSideA(int side) { sideA = checkSideSize(side); }
void MyRectangle::setSideB(int side) { sideB = checkSideSize(side); }

const int& MyRectangle::getSideA() const { return sideA; }
const int& MyRectangle::getSideB() const { return sideB; }

double MyRectangle::getArea() const
{
	return sideA * sideB;
}

double MyRectangle::getPerimeter() const
{
	return 2 * (sideA + sideB);
}

void MyRectangle::draw(Vector2 position) const
{
	DrawRectangle(position.x, position.y, sideA, sideB, color);
}
