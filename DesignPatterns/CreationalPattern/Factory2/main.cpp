#include<iostream>
#include<Windows.h>
#include<numbers>
#include<vector>

#define _USE_MATH_DEFINES

using std::cout;
using std::cin;
using std::endl;

namespace MyGeometry
{
    enum Color // 0xAABBGGRR
    {
        RED = 0x000000FF,
        GREEN = 0x0000FF00,
        BLUE = 0x00FF0000,
        YELLOW = 0x0000FFFF,
        GREY = 0x00AAAAAA,
        WHITE = 0x00FFFFFF,
        BLACK = 0x00000000,
        AQUAMARINE = 0x00D4FF7F,
        HELIOTROPE = 0x00FF7FD4,
        SALOMIE = 0x007FD4FF,
        THISTLE = 0x00D8BFD8,
        TICKLE_ME_PINK = 0x00AA7FFF,
        MEDIUM_PURPLE = 0x00DB7093
    };


    class Shape
    {
    protected:
        static const int MIN_SIZE = 50;
        static const int MAX_SIZE = 800;
        static const int MIN_LINE_WIDTH = 1;
        static const int MAX_LINE_WIDTH = 25;
        static const int MAX_HORISONTAL_RESOLUTION = 800;
        static const int MAX_VERTICAL_RESOLUTION = 600;

        unsigned int x;
        unsigned int y;
        unsigned int lineWindth;
        Color color;
    public:
        Shape(unsigned int x, unsigned int y, unsigned int lineWidth = 5, Color color = Color::GREY) :color(color)
        {
            setX(x);
            setY(y);
            setLineWidth(lineWindth);
        }

        virtual ~Shape() {}

        const unsigned int& getX() const { return x; }
        const unsigned int& getY() const { return y; }
        const unsigned int& getLineWidth() const { return lineWindth; }
        const Color& getColor() const { return color; }

        unsigned int setSize(unsigned int size)
        {
            return size < MIN_SIZE ? MIN_SIZE :
                size > MAX_SIZE ? MAX_SIZE :
                size;
        }

        void setX(unsigned int x)
        {
            this->x = x < MAX_HORISONTAL_RESOLUTION ? x : MAX_HORISONTAL_RESOLUTION;
        }

        void setY(unsigned int y)
        {
            this->y = y < MAX_VERTICAL_RESOLUTION ? y : MAX_VERTICAL_RESOLUTION;
        }

        void setLineWidth(unsigned int lineWidth)
        {
            if (lineWidth < MIN_LINE_WIDTH) { lineWidth = MIN_LINE_WIDTH; }
            else if (lineWidth > MAX_LINE_WIDTH) { lineWidth = MAX_LINE_WIDTH; }
            this->lineWindth = lineWidth;
        }

        virtual double getArea() const = 0;
        virtual double getPerimeter() const = 0;
        virtual void draw() const = 0;

        virtual void info() const
        {
            cout << "Площадь фигуры: " << getArea() << endl;
            cout << "Периметр фигуры: " << getPerimeter() << endl;
            draw();
        }
    };


    class Rectangle :public Shape
    {
        double width;
        double height;
    public:
        Rectangle(double width, double length, unsigned int x, unsigned int y, unsigned int lineWidth, Color color)
            :Shape(x, y, lineWidth, color)
        {
            setWidth(width);
            setHeight(length);
        }

        const double& getWidth() const { return width; }
        const double& getHeight() const { return height; }

        void setWidth(double width) { this->width = setSize(width); }
        void setHeight(double length) { this->height = setSize(length); }

        double getArea() const override
        {
            return width * height;
        }

        double getPerimeter() const override
        {
            return 2 * (width + height);
        }

        void draw() const override
        {
            HWND hwnd = GetConsoleWindow(); // получаем дескриптор окна консоли
            // HWND - handler to window, нужен для того чтобы обращаться к окну
            
            // чтобы рисовать, нужен контекст устройства (device context), он есть у каждого окна
            HDC hdc = GetDC(hwnd);
            // hdc - то, на чем мы будем рисовать (аналог бумаги)

            // для рисования требуются ручки-карандаши-кисти-этцетера:
            HPEN hPen = CreatePen(PS_SOLID, lineWindth, color); // карандаш (ручка) рисует контур фигуры
            HBRUSH hBrush = CreateSolidBrush(color); // кисть заливает фигуру
            // iStyle - тип линии (это можно и нужно погуглить)

            // теперь нужно выбрать, чем и на чем рисовать:
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);

            ::Rectangle(hdc, x, y, x + width, y + height);

            // удаляем все созданные объекты для освобождения ресурсов
            DeleteObject(hPen);
            DeleteObject(hBrush);
            ReleaseDC(hwnd, hdc);
        }

        virtual void info() const
        {
            cout << typeid(*this).name() << endl;
            cout << "Ширина: " << width << endl;
            cout << "Высота: " << height << endl;
            Shape::info();
        }
    };


    class Square :public Rectangle
    {
        using Rectangle::getHeight;
        using Rectangle::getWidth;
        using Rectangle::setHeight;
        using Rectangle::setWidth;
    public:
        Square(double side, unsigned int x, unsigned int y, unsigned int lineWidth, Color color)
            :Rectangle(side, side, x, y, lineWidth, color) {}

        const double& getSide() const { return getWidth(); }

        void setSide(double side)
        {
            setWidth(side);
            setHeight(side);
        }

        void info() const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Сторона: " << getSide() << endl;
            Shape::info();
        }
    };


    class Circle :public Shape
    {
        double radius;
    public:
        Circle(double radius, unsigned int x, unsigned int y, unsigned int lineWidth, Color color)
            :Shape(x, y, lineWidth, color)
        {
            setRadius(radius);
        }

        const double& getRadius() const { return radius; }

        void setRadius(double radius) { this->radius = setSize(radius); }

        double getDiameter() const { return radius * 2; }

        double getArea() const override
        {
            return std::numbers::pi * (radius * radius);
        }

        double getPerimeter() const override
        {
            return 2 * std::numbers::pi * radius;
        }

        void draw() const override
        {
            HWND hwnd = GetConsoleWindow();
            HDC hdc = GetDC(hwnd);
            HPEN hPen = CreatePen(PS_SOLID, lineWindth, color);
            HBRUSH hBrush = CreateSolidBrush(color);

            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);

            ::RoundRect(hdc, x, y, x + getDiameter(), y + getDiameter(), getDiameter(), getDiameter());

            DeleteObject(hPen);
            DeleteObject(hBrush);
            ReleaseDC(hwnd, hdc);
        }

        void info() const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Радиус: " << radius << endl;
            cout << "Диаметр: " << getDiameter() << endl;
            Shape::info();
        }
    };


    class Triangle :public Shape
    {
    public:
        Triangle(unsigned int x, unsigned int y, unsigned int lineWidth, Color color)
            :Shape(x, y, lineWidth, color) {}
    };


    class TriangleScalene :public Triangle
    {
        double sideA;
        double sideB;
        double sideC;
    public:
        TriangleScalene(double sideA, double sideB, double sideC, unsigned int x, unsigned int y, unsigned int lineWidth, Color color)
            :Triangle(x, y, lineWidth, color)
        {
            setSideA(sideA);
            setSideB(sideB);
            setSideC(sideC);
        }

        const double& getSideA() const { return sideA; }
        const double& getSideB() const { return sideB; }
        const double& getSideC() const { return sideC; }

        void setSideA(double side)
        {
            sideA = setSize(side);
        }
        void setSideB(double side)
        {
            sideB = setSize(side);
        }
        void setSideC(double side)
        {
            sideC = setSize(side);
        }

        bool isDegenerate()
        {
            return sideA + sideB < sideC ||
                sideA + sideC < sideB ||
                sideB + sideC < sideA;
        }
    };


    class TriangleRight :public Triangle
    {
        double legA;
        double legB;
    public:
        TriangleRight(double legA, double legB, unsigned int x, unsigned int y, unsigned int lineWidth, Color color)
            :Triangle(x, y, lineWidth, color)
        {
            setLegA(legA);
            setLegB(legB);
        }

        const double& getLegA() const { return legA; }
        const double& getLegB() const { return legB; }

        void setLegA(double size) { legA = setSize(size); }
        void setLegB(double size) { legB = setSize(size); }

        double getHypotenuse() const { return sqrt(legA * legA + legB * legB); }

        double getArea() const override
        {
            return (legA * legB) / 2;
        }

        double getPerimeter() const override
        {
            return legA + legB + getHypotenuse();
        }

        void draw() const override
        {
            HWND hwnd = GetConsoleWindow();
            HDC hdc = GetDC(hwnd);
            HPEN hPen = CreatePen(PS_SOLID, lineWindth, color);
            HBRUSH hBrush = CreateSolidBrush(color);
            POINT verticles[3]{ {x, y}, {x + legA, y}, {x, y - legB} };

            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);

            ::Polygon(hdc, verticles, 3);

            DeleteObject(hPen);
            DeleteObject(hBrush);
            ReleaseDC(hwnd, hdc);
        }

        void info() const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Катет A: " << legA << endl;
            cout << "Катет B: " << legB << endl;
            cout << "Гипотенуза: " << getHypotenuse() << endl;
            Shape::info();
        }
    };


    class TriangleIsosceles :public Triangle
    {
        double side;
        double base;
    public:
        TriangleIsosceles(double side, double base, unsigned int x, unsigned int y, unsigned int lineWidth, Color color)
            :Triangle(x, y, lineWidth, color)
        {

        }

        const double& getSide() const { return side; }
        const double& getBase() const { return side; }
    };


    class TriangleEquilateral :public Triangle
    {
        double side;
    public:
        TriangleEquilateral(double side, unsigned int x, unsigned int y, unsigned int lineWidth, Color color)
            :Triangle(x, y, lineWidth, color)
        {
            setSide(side);
        }

        const double& getSide() const { return side; }

        void setSide(double size) { side = setSize(size); }
    };
}

int main()
{
    setlocale(LC_ALL, "");

    const unsigned int shapeArraySize = 4;
    unsigned int posY = 150;
    unsigned int lineWidth = 8;

    MyGeometry::Shape* shapes[shapeArraySize]
    {
        new MyGeometry::Rectangle(100, 50, 30, posY, lineWidth, MyGeometry::Color::AQUAMARINE),
        new MyGeometry::Square(50, 160, posY, lineWidth, MyGeometry::Color::THISTLE),
        new MyGeometry::Circle(50, 240, posY, lineWidth, MyGeometry::Color::TICKLE_ME_PINK),
        new MyGeometry::TriangleRight(50, 60, 370, posY + 50, lineWidth, MyGeometry::Color::MEDIUM_PURPLE)
    };

    for (size_t i = 0; i < shapeArraySize; i++)
    {
        shapes[i]->draw();
    }
}
