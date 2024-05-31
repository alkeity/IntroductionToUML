#include<iostream>
#include<raylib.h>

using std::cout;
using std::cin;
using std::endl;

class Shape
{
protected:
	//
public:
};

class Circle :public Shape
{

};

class Triangle : public Shape
{

};

class Rectangle :public Shape
{
protected:
	//
public:
};

class Square : public Rectangle
{

};


int main()
{
	setlocale(LC_ALL, "");

}
