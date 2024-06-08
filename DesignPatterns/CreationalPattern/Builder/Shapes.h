#pragma once
#include<Windows.h>

namespace MyGeometry
{
#define SHAPE_TAKE_PARAMETERS unsigned int x, unsigned int y, unsigned int lineWidth, COLORREF color
#define SHAPE_GIVE_PARAMETERS x, y, lineWidth, color

    class Shape
    {
    protected:
        unsigned int x;
        unsigned int y;
        unsigned int lineWindth;
        COLORREF color;

        virtual void drawShape(HDC& hdc) const = 0;
    public:
        static const int MIN_SIZE = 20;
        static const int MAX_SIZE = 800;
        static const int MIN_LINE_WIDTH = 1;
        static const int MAX_LINE_WIDTH = 25;
        static const int MAX_HORISONTAL_RESOLUTION = 800;
        static const int MAX_VERTICAL_RESOLUTION = 600;

        Shape(SHAPE_TAKE_PARAMETERS);

        virtual ~Shape() {}

        const unsigned int& getX() const;
        const unsigned int& getY() const;
        const unsigned int& getLineWidth() const;
        const COLORREF& getColor() const;

        unsigned int setSize(unsigned int size);
        void setX(unsigned int x);
        void setY(unsigned int y);
        void setLineWidth(unsigned int lineWidth);
        void setColor(COLORREF color);

        virtual double getArea() const = 0;
        virtual double getPerimeter() const = 0;
        virtual void draw() const;
        virtual void info() const;
    };


    class Rectangle :public Shape
    {
        double width;
        double height;

        void drawShape(HDC& hdc) const override;
    public:
        Rectangle();
        Rectangle(double width, double length, SHAPE_TAKE_PARAMETERS);

        const double& getWidth() const;
        const double& getHeight() const;

        void setWidth(double width);
        void setHeight(double length);

        double getArea() const override;
        double getPerimeter() const override;
        virtual void info() const;
    };


    class Square :public Rectangle
    {
        using Rectangle::getHeight;
        using Rectangle::getWidth;
        using Rectangle::setHeight;
        using Rectangle::setWidth;
    public:
        Square();
        Square(double side, SHAPE_TAKE_PARAMETERS);
        const double& getSide() const;
        void setSide(double side);
        void info() const override;
    };


    class Circle :public Shape
    {
        double radius;

        void drawShape(HDC& hdc) const override;
    public:
        Circle();
        Circle(double radius, SHAPE_TAKE_PARAMETERS);
        const double& getRadius() const;
        void setRadius(double radius);
        double getDiameter() const;
        double getArea() const override;
        double getPerimeter() const override;
        void info() const override;
    };


    class Triangle :public Shape
    {
    protected:
        double sideA;
        double sideB;
        double sideC;

        void drawShape(HDC& hdc) const override;
    public:
        Triangle(double sideA, double sideB, double sideC, SHAPE_TAKE_PARAMETERS);
        const double& getSideA() const;
        const double& getSideB() const;
        const double& getSideC() const;

        void setSideA(double side);
        void setSideB(double side);
        void setSideC(double side);

        virtual void getVerticles(POINT vertArray[3]) const = 0;
        double getPerimeter() const override;
        double getArea() const override;
        double getHeightFromSideA() const;
        bool isDegenerate() const;
        void info() const override;
        void draw() const override;
    };


    class TriangleScalene :public Triangle
    {
    public:
        TriangleScalene();
        TriangleScalene(double sideA, double sideB, double sideC, SHAPE_TAKE_PARAMETERS);
        void getVerticles(POINT vertArray[3]) const override;
    };


    class TriangleRight :public Triangle
    {
    public:
        TriangleRight();
        TriangleRight(double legA, double legB, SHAPE_TAKE_PARAMETERS);
        double getHypotenuse(double legA, double legB) const;
        void getVerticles(POINT vertArray[3]) const override;
    };


    class TriangleIsosceles :public Triangle
    {
    public:
        TriangleIsosceles();
        TriangleIsosceles(double side, double base, SHAPE_TAKE_PARAMETERS);
        void getVerticles(POINT vertArray[3]) const override;
    };


    class TriangleEquilateral :public Triangle
    {
    public:
        TriangleEquilateral();
        TriangleEquilateral(double side, SHAPE_TAKE_PARAMETERS);
        void getVerticles(POINT vertArray[3]) const override;
    };
}
