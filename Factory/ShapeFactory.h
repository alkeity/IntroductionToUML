#pragma once
#include"Shapes.h"

class ShapeFactory
{
public:
	~ShapeFactory();
	virtual MyShape* create() = 0;
};


class CircleFactory :public ShapeFactory
{
public:
	MyShape* create() override;
};

class SqTriangleFactory :public ShapeFactory
{
public:
	MyShape* create() override;
};

class RectangleFactory :public ShapeFactory
{
public:
	MyShape* create() override;
};

class SquareFactory :public ShapeFactory
{
public:
	MyShape* create() override;
};
