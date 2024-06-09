#include<iostream>
#include<string>
#include<Windows.h>
#include"Shapes.h"

using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n|----------------------------------------------|\n"


class ShapeBuilder
{
protected:
	MyGeometry::Shape* shape;
public:
	ShapeBuilder()
	{
		this->shape = nullptr;
	}

	virtual ~ShapeBuilder()
	{
		delete[]this->shape;
	}

	MyGeometry::Shape* getShape()
	{
		return shape;
	}

	virtual void setX() = 0;
	virtual void setY() = 0;
	virtual void setLineWidth() = 0;
	virtual void setColor() = 0;
};

class RectangleBuilder :public ShapeBuilder
{
public:
	RectangleBuilder()
	{
		this->shape = new MyGeometry::Rectangle();
	}

	void setWidth() { dynamic_cast<MyGeometry::Rectangle*>(shape)->setWidth(300); }
	void setHeight() { dynamic_cast<MyGeometry::Rectangle*>(shape)->setHeight(200); }

	void setX() override { shape->setX(200); }
	void setY() override { shape->setY(500); }
	void setLineWidth() override { shape->setLineWidth(8); }
	void setColor() override { shape->setColor(RGB(205, 164, 248)); }
};

class SquareBuilder :public ShapeBuilder
{
public:
	SquareBuilder()
	{
		this->shape = new MyGeometry::Square();
	}

	void setSide() { dynamic_cast<MyGeometry::Square*>(shape)->setSide(300); }

	void setX() override { shape->setX(400); }
	void setY() override { shape->setY(200); }
	void setLineWidth() override { shape->setLineWidth(5); }
	void setColor() override { shape->setColor(RGB(164, 248, 205)); }
};

class CircleBuilder :public ShapeBuilder
{
public:
	CircleBuilder()
	{
		this->shape = new MyGeometry::Circle();
	}

	void setRadius() { dynamic_cast<MyGeometry::Circle*>(shape)->setRadius(330); }

	void setX() override { shape->setX(600); }
	void setY() override { shape->setY(400); }
	void setLineWidth() override { shape->setLineWidth(3); }
	void setColor() override { shape->setColor(RGB(248, 164, 165)); }
};

class TriangleScaleneBuilder :public ShapeBuilder
{
public:
	TriangleScaleneBuilder()
	{
		this->shape = new MyGeometry::TriangleScalene();
	}

	void setSideA() { dynamic_cast<MyGeometry::Triangle*>(shape)->setSideA(300); }
	void setSideB() { dynamic_cast<MyGeometry::Triangle*>(shape)->setSideB(200); }
	void setSideC() { dynamic_cast<MyGeometry::Triangle*>(shape)->setSideC(400); }

	void setX() override { shape->setX(250); }
	void setY() override { shape->setY(430); }
	void setLineWidth() override { shape->setLineWidth(2); }
	void setColor() override { shape->setColor(RGB(164, 165, 248)); }
};

class TriangleRightBuilder :public ShapeBuilder
{
public:
	TriangleRightBuilder()
	{
		this->shape = new MyGeometry::TriangleRight();
	}

	void setSideA() { dynamic_cast<MyGeometry::Triangle*>(shape)->setSideA(100); }
	void setSideB() { dynamic_cast<MyGeometry::Triangle*>(shape)->setSideB(200); }
	void setSideC() { dynamic_cast<MyGeometry::Triangle*>(shape)->setSideC(dynamic_cast<MyGeometry::TriangleRight*>(shape)->getHypotenuse(100, 200)); }

	void setX() override { shape->setX(650); }
	void setY() override { shape->setY(330); }
	void setLineWidth() override { shape->setLineWidth(7); }
	void setColor() override { shape->setColor(RGB(164, 207, 248)); }
};

class TriangleIsoscelesBuilder :public ShapeBuilder
{
public:
	TriangleIsoscelesBuilder()
	{
		this->shape = new MyGeometry::TriangleIsosceles();
	}

	void setSideA() { dynamic_cast<MyGeometry::Triangle*>(shape)->setSideA(340); }
	void setSideB() { dynamic_cast<MyGeometry::Triangle*>(shape)->setSideB(200); }
	void setSideC() { dynamic_cast<MyGeometry::Triangle*>(shape)->setSideC(200); }

	void setX() override { shape->setX(550); }
	void setY() override { shape->setY(530); }
	void setLineWidth() override { shape->setLineWidth(3); }
	void setColor() override { shape->setColor(RGB(207, 248, 164)); }
};

class TriangleEquilateralBuilder :public ShapeBuilder
{
public:
	TriangleEquilateralBuilder()
	{
		this->shape = new MyGeometry::TriangleEquilateral();
	}

	void setSideA() { dynamic_cast<MyGeometry::Triangle*>(shape)->setSideA(300); }
	void setSideB() { dynamic_cast<MyGeometry::Triangle*>(shape)->setSideB(300); }
	void setSideC() { dynamic_cast<MyGeometry::Triangle*>(shape)->setSideC(300); }

	void setX() override { shape->setX(320); }
	void setY() override { shape->setY(530); }
	void setLineWidth() override { shape->setLineWidth(8); }
	void setColor() override { shape->setColor(RGB(248, 205, 164)); }
};


int main()
{
	setlocale(LC_ALL, "");
	// TODO
}
