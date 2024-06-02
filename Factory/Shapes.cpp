#include<iostream>
#include "Shapes.h"

using std::cout;
using std::cin;
using std::endl;

//abstract class MyShape

MyShape::~MyShape()
{
	cout << this << ": shape destroyed\n";
}

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

void MyShape::setPosition(Vector2 position)
{
	if (position.x < 0) { position.x = 0; }
	if (position.y < 0) { position.y = 0; }
	this->position = position;
}

// class MyCircle

MyCircle::MyCircle(int radius, Color color, Vector2 pos)
{
	setRadius(radius);
	setColor(color);
	setPosition(pos);
	cout << this << ": circle created\n";
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

void MyCircle::draw() const
{
	DrawCircle(position.x, position.y, radius, color);
}

// class SquaredTriangle

SquaredTriangle::SquaredTriangle(int sideA, int sideB, Color color, Vector2 pos)
{
	setColor(color);
	setSideA(sideA);
	setSideB(sideB);
	setPosition(pos);
	cout << this << ": squared triangle created\n";
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

void SquaredTriangle::draw() const
{
	Vector2 pos1{ position.x + sideB, position.y };
	Vector2 pos2{ position.x, position.y + sideA };
	DrawTriangle(pos1, position, pos2, color);
}

//class MyRectangle

MyRectangle::MyRectangle(int sideA, int sideB, Color color, Vector2 pos)
{
	setSideA(sideA);
	setSideB(sideB);
	setColor(color);
	setPosition(pos);
	cout << this << ": rectangle created\n";
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

void MyRectangle::draw() const
{
	DrawRectangle(position.x, position.y, sideA, sideB, color);
}
