#pragma once
#include<numbers>
#include<raylib.h>


class MyShape
{
protected:
	Color color;
	Vector2 position;
	int checkSideSize(int side);
public:
	~MyShape();
	void setColor(Color color);
	void setPosition(Vector2 position);
	virtual void printInfo();
	virtual double getArea() const = 0;
	virtual double getPerimeter() const = 0;
	virtual void draw() const = 0;
};


class MyCircle :public MyShape
{
	unsigned int radius;
public:
	MyCircle(int radius, Color color, Vector2 pos);
	void setRadius(int radius);
	const int& getRadius() const;
	int getDiameter() const;
	double getArea() const override;
	double getPerimeter() const override;
	void draw() const override;
	void printInfo() override;
};

class SquaredTriangle : public MyShape
{
	unsigned int sideA;
	unsigned int sideB;
public:
	SquaredTriangle(int sideA, int sideB, Color color, Vector2 pos);
	void setSideA(int side);
	void setSideB(int side);
	const int& getSideA() const;
	const int& getSideB() const;
	double getSideC() const;
	double getArea() const override;
	double getPerimeter() const override;
	void draw() const override; // position is coord of the squared angle of triangle
	void printInfo() override;
};


class MyRectangle :public MyShape
{
protected:
	unsigned int sideA;
	unsigned int sideB;
public:
	MyRectangle(int sideA, int sideB, Color color, Vector2 pos);
	void setSideA(int side);
	void setSideB(int side);
	const int& getSideA() const;
	const int& getSideB() const;
	double getArea() const override;
	double getPerimeter() const override;
	void draw() const override;
	virtual void printInfo();
};


class MySquare : public MyRectangle
{
public:
	const int& getSideB() const = delete;
	const int& setSideB() const = delete;
	MySquare(int side, Color color, Vector2 pos) :MyRectangle(side, side, color, pos) {}
	void printInfo() override;
};
