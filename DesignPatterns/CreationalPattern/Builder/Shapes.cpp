#include<iostream>
#include<numbers>
#include "Shapes.h"

using std::cout;
using std::cin;
using std::endl;

#define _USE_MATH_DEFINES

// class Shape

#define DEFAULT_SHAPE_PARAMS 0, 0, 1, RGB(255, 255, 255)

MyGeometry::Shape::Shape(SHAPE_TAKE_PARAMETERS) :color(color)
{
    setX(x);
    setY(y);
    setLineWidth(lineWindth);
}

const unsigned int& MyGeometry::Shape::getX() const { return x; }
const unsigned int& MyGeometry::Shape::getY() const { return y; }
const unsigned int& MyGeometry::Shape::getLineWidth() const { return lineWindth; }
const COLORREF& MyGeometry::Shape::getColor() const { return color; }

unsigned int MyGeometry::Shape::setSize(unsigned int size)
{
    return size < MIN_SIZE ? MIN_SIZE :
        size > MAX_SIZE ? MAX_SIZE :
        size;
}

void MyGeometry::Shape::setX(unsigned int x)
{
    this->x = x < MAX_HORISONTAL_RESOLUTION ? x : MAX_HORISONTAL_RESOLUTION;
}

void MyGeometry::Shape::setY(unsigned int y)
{
    this->y = y < MAX_VERTICAL_RESOLUTION ? y : MAX_VERTICAL_RESOLUTION;
}

void MyGeometry::Shape::setLineWidth(unsigned int lineWidth)
{
    if (lineWidth < MIN_LINE_WIDTH) { lineWidth = MIN_LINE_WIDTH; }
    else if (lineWidth > MAX_LINE_WIDTH) { lineWidth = MAX_LINE_WIDTH; }
    this->lineWindth = lineWidth;
}

void MyGeometry::Shape::setColor(COLORREF color)
{
    this->color = color;
}

void MyGeometry::Shape::draw() const
{
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);
    HPEN hPen = CreatePen(PS_SOLID, lineWindth, color);
    HBRUSH hBrush = CreateSolidBrush(color);
    SelectObject(hdc, hPen);
    SelectObject(hdc, hBrush);
    drawShape(hdc);
    DeleteObject(hPen);
    DeleteObject(hBrush);
    ReleaseDC(hwnd, hdc);
}

void MyGeometry::Shape::info() const
{
    cout << "Площадь фигуры: " << getArea() << endl;
    cout << "Периметр фигуры: " << getPerimeter() << endl;
    draw();
}

// class Rectangle

void MyGeometry::Rectangle::drawShape(HDC& hdc) const
{
    ::Rectangle(hdc, x, y, x + width, y + height);
}

MyGeometry::Rectangle::Rectangle() :Shape(DEFAULT_SHAPE_PARAMS)
{
    setWidth(100);
    setHeight(200);
}

MyGeometry::Rectangle::Rectangle(double width, double length, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
{
    setWidth(width);
    setHeight(length);
}

const double& MyGeometry::Rectangle::getWidth() const { return width; }
const double& MyGeometry::Rectangle::getHeight() const { return height; }

void MyGeometry::Rectangle::setWidth(double width) { this->width = setSize(width); }
void MyGeometry::Rectangle::setHeight(double length) { this->height = setSize(length); }

double MyGeometry::Rectangle::getArea() const
{
    return width * height;
}

double MyGeometry::Rectangle::getPerimeter() const
{
    return 2 * (width + height);
}

void MyGeometry::Rectangle::info() const
{
    cout << typeid(*this).name() << endl;
    cout << "Ширина: " << width << endl;
    cout << "Высота: " << height << endl;
    Shape::info();
}

// class Square

MyGeometry::Square::Square() :Rectangle(100, 100, DEFAULT_SHAPE_PARAMS) {}
MyGeometry::Square::Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}

const double& MyGeometry::Square::getSide() const { return getWidth(); }


void MyGeometry::Square::setSide(double side)
{
    setWidth(side);
    setHeight(side);
}


void MyGeometry::Square::info() const
{
    cout << typeid(*this).name() << endl;
    cout << "Сторона: " << getSide() << endl;
    Shape::info();
}

// class Circle

void MyGeometry::Circle::drawShape(HDC& hdc) const
{
    ::Ellipse(hdc, x, y, x + getDiameter(), y + getDiameter());
}

MyGeometry::Circle::Circle() :Shape(DEFAULT_SHAPE_PARAMS)
{
    setRadius(50);
}

MyGeometry::Circle::Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
{
    setRadius(radius);
}

const double& MyGeometry::Circle::getRadius() const { return radius; }
void MyGeometry::Circle::setRadius(double radius) { this->radius = setSize(radius); }
double MyGeometry::Circle::getDiameter() const { return radius * 2; }

double MyGeometry::Circle::getArea() const
{
    return std::numbers::pi * (radius * radius);
}

double MyGeometry::Circle::getPerimeter() const
{
    return std::numbers::pi * getDiameter();
}

void MyGeometry::Circle::info() const
{
    cout << typeid(*this).name() << endl;
    cout << "Радиус: " << radius << endl;
    cout << "Диаметр: " << getDiameter() << endl;
    Shape::info();
}

// class Triangle

void MyGeometry::Triangle::drawShape(HDC& hdc) const
{
    POINT verticles[3];
    getVerticles(verticles);
    ::Polygon(hdc, verticles, 3);
}

MyGeometry::Triangle::Triangle(double sideA, double sideB, double sideC, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
{
    setSideA(sideA);
    setSideB(sideB);
    setSideC(sideC);
}

const double& MyGeometry::Triangle::getSideA() const { return sideA; }
const double& MyGeometry::Triangle::getSideB() const { return sideB; }
const double& MyGeometry::Triangle::getSideC() const { return sideC; }

void MyGeometry::Triangle::setSideA(double side) { sideA = setSize(side); };
void MyGeometry::Triangle::setSideB(double side) { sideB = setSize(side); };
void MyGeometry::Triangle::setSideC(double side) { sideC = setSize(side); };

double MyGeometry::Triangle::getPerimeter() const
{
    return isDegenerate() ? 0 : sideA + sideB + sideC;
}

double MyGeometry::Triangle::getArea() const
{
    double area = 0;
    if (!isDegenerate())
    {
        double p = getPerimeter() / 2;
        area = sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
    }
    return area;
}

double MyGeometry::Triangle::getHeightFromSideA() const
{
    return isDegenerate() ? 0 : (2 * getArea()) / sideA;
}

bool MyGeometry::Triangle::isDegenerate() const
{
    return sideA + sideB < sideC ||
        sideA + sideC < sideB ||
        sideB + sideC < sideA;
}

void MyGeometry::Triangle::info() const
{
    cout << typeid(*this).name() << endl;
    cout << "Сторона A: " << sideA << endl;
    cout << "Сторона B: " << sideB << endl;
    cout << "Сторона C: " << sideC << endl;
    cout << "Вырожденный: ";
    if (isDegenerate()) { cout << "Да\n"; }
    else
    {
        cout << "Нет\n";
        Shape::info();
    }
}

void MyGeometry::Triangle::draw() const
{
    if (!isDegenerate()) { Shape::draw(); }
}

// class TriangleScalene

MyGeometry::TriangleScalene::TriangleScalene() :Triangle(50, 30, 20, DEFAULT_SHAPE_PARAMS) {}

MyGeometry::TriangleScalene::TriangleScalene(double sideA, double sideB, double sideC, SHAPE_TAKE_PARAMETERS)
    :Triangle(sideA, sideB, sideC, SHAPE_GIVE_PARAMETERS) {}

void MyGeometry::TriangleScalene::getVerticles(POINT vertArray[3]) const
{
    vertArray[0] = { (long)x, (long)y };
    vertArray[1] = { (long)(x + sideA), (long)y };
    vertArray[2] = {
        (long)(x + sqrt(sideB * sideB + getHeightFromSideA() * getHeightFromSideA())),
        (long)(y - getHeightFromSideA()) };
}

// class TriangleRight

double MyGeometry::TriangleRight::getHypotenuse(double legA, double legB) const
{
    return sqrt(legA * legA + legB * legB);
}

MyGeometry::TriangleRight::TriangleRight():Triangle(50, 30, getHypotenuse(50, 30), DEFAULT_SHAPE_PARAMS) {}

MyGeometry::TriangleRight::TriangleRight(double legA, double legB, SHAPE_TAKE_PARAMETERS)
    :Triangle(legA, legB, getHypotenuse(legA, legB), SHAPE_GIVE_PARAMETERS) {}

void MyGeometry::TriangleRight::getVerticles(POINT vertArray[3]) const
{
    vertArray[0] = { (long)x, (long)y };
    vertArray[1] = { (long)(x + sideA), (long)y };
    vertArray[2] = { (long)x, (long)(y - sideB) };
}

// class TriangleIsosceles

MyGeometry::TriangleIsosceles::TriangleIsosceles() :Triangle(50, 30, 30, DEFAULT_SHAPE_PARAMS) {}

MyGeometry::TriangleIsosceles::TriangleIsosceles(double side, double base, SHAPE_TAKE_PARAMETERS)
    :Triangle(base, side, side, SHAPE_GIVE_PARAMETERS) {}

void MyGeometry::TriangleIsosceles::getVerticles(POINT vertArray[3]) const
{
    vertArray[0] = { (long)x, (long)y };
    vertArray[1] = { (long)(x + sideA), (long)y };
    vertArray[2] = { (long)(x + sideA / 2), (long)(y - sideB) };
}

// class TriangleEquilateral

MyGeometry::TriangleEquilateral::TriangleEquilateral() :Triangle(50, 50, 50, DEFAULT_SHAPE_PARAMS) {}

MyGeometry::TriangleEquilateral::TriangleEquilateral(double side, SHAPE_TAKE_PARAMETERS)
    :Triangle(side, side, side, SHAPE_GIVE_PARAMETERS) {}

void MyGeometry::TriangleEquilateral::getVerticles(POINT vertArray[3]) const
{
    vertArray[0] = { (long)x, (long)y };
    vertArray[1] = { (long)(x + sideA), (long)y };
    vertArray[2] = { (long)(x + sideA / 2), (long)(y - sideA) };
}
