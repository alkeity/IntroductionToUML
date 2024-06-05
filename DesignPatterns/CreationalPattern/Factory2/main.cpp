#include<iostream>
#include<Windows.h>
#include<numbers>
#include<vector>

#define _USE_MATH_DEFINES

//#define USING_ENUM_COLOR
#define USING_COLORREF

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
        MEDIUM_PURPLE = 0x00DB7093,
        TWILIGHT = 0x00CBBFD8
    };

#define SHAPE_TAKE_PARAMETERS unsigned int x, unsigned int y, unsigned int lineWidth, COLORREF color
#define SHAPE_GIVE_PARAMETERS x, y, lineWidth, color

    class Shape
    {
    protected:
        unsigned int x;
        unsigned int y;
        unsigned int lineWindth;
#ifdef USING_ENUM_COLOR
        Color color;
#endif // USING_ENUM_COLOR

#ifdef USING_COLORREF
        COLORREF color;
#endif // USING_COLORREF

    public:
        static const int MIN_SIZE = 20;
        static const int MAX_SIZE = 800;
        static const int MIN_LINE_WIDTH = 1;
        static const int MAX_LINE_WIDTH = 25;
        static const int MAX_HORISONTAL_RESOLUTION = 800;
        static const int MAX_VERTICAL_RESOLUTION = 600;

        Shape(SHAPE_TAKE_PARAMETERS) :color(color)
        {
            setX(x);
            setY(y);
            setLineWidth(lineWindth);
        }

        virtual ~Shape() {}

        const unsigned int& getX() const { return x; }
        const unsigned int& getY() const { return y; }
        const unsigned int& getLineWidth() const { return lineWindth; }
        const COLORREF& getColor() const { return color; }

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
        Rectangle(double width, double length, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
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
        Square(double side, SHAPE_TAKE_PARAMETERS) :Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}

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
        Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
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
            return std::numbers::pi * getDiameter();
        }

        void draw() const override
        {
            HWND hwnd = GetConsoleWindow();
            HDC hdc = GetDC(hwnd);
            HPEN hPen = CreatePen(PS_SOLID, lineWindth, color);
            HBRUSH hBrush = CreateSolidBrush(color);

            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);

            //::RoundRect(hdc, x, y, x + getDiameter(), y + getDiameter(), getDiameter(), getDiameter());
            ::Ellipse(hdc, x, y, x + getDiameter(), y + getDiameter());

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
    protected:
        double sideA;
        double sideB;
        double sideC;
    public:
        Triangle(double sideA, double sideB, double sideC, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
        {
            setSideA(sideA);
            setSideB(sideB);
            setSideC(sideC);
        }

        const double& getSideA() const { return sideA; }
        const double& getSideB() const { return sideB; }
        const double& getSideC() const { return sideC; }

        void setSideA(double side) { sideA = setSize(side); };
        void setSideB(double side) { sideB = setSize(side); };
        void setSideC(double side) { sideC = setSize(side); };

        virtual void getVerticles(POINT vertArray[3]) const = 0;

        double getPerimeter() const override
        {
            return sideA + sideB + sideC;
        }

        double getArea() const override
        {
            double p = getPerimeter() / 2;
            return sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
        }

        double getHeightFromSideA() const
        {
            return (2 * getArea()) / sideA;
        }

        bool isDegenerate() const
        {
            return sideA + sideB < sideC ||
                sideA + sideC < sideB ||
                sideB + sideC < sideA;
        }

        void info() const override
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

        void draw() const override
        {
            if (!isDegenerate())
            {
                HWND hwnd = GetConsoleWindow();
                HDC hdc = GetDC(hwnd);
                HPEN hPen = CreatePen(PS_SOLID, lineWindth, color);
                HBRUSH hBrush = CreateSolidBrush(color);
                POINT verticles[3];

                getVerticles(verticles);

                SelectObject(hdc, hPen);
                SelectObject(hdc, hBrush);

                ::Polygon(hdc, verticles, 3);

                DeleteObject(hPen);
                DeleteObject(hBrush);
                ReleaseDC(hwnd, hdc);
            }
        }
    };


    class TriangleScalene :public Triangle
    {
    public:
        TriangleScalene(double sideA, double sideB, double sideC, SHAPE_TAKE_PARAMETERS)
            :Triangle(sideA, sideB, sideC, SHAPE_GIVE_PARAMETERS) {}

        void getVerticles(POINT vertArray[3]) const override
        {
            vertArray[0] = { (long)x, (long)y };
            vertArray[1] = { (long)(x + sideA), (long)y };
            vertArray[2] = {
                (long)(x + sqrt(sideB * sideB + getHeightFromSideA() * getHeightFromSideA())),
                (long)(y - getHeightFromSideA()) };
        }
    };


    class TriangleRight :public Triangle
    {
        double getHypotenuse(double legA, double legB) const
        {
            return sqrt(legA * legA + legB * legB);
        }
    public:
        TriangleRight(double legA, double legB, SHAPE_TAKE_PARAMETERS)
            :Triangle(legA, legB, getHypotenuse(legA, legB), SHAPE_GIVE_PARAMETERS) {}

        void getVerticles(POINT vertArray[3]) const override
        {
            vertArray[0] = { (long)x, (long)y };
            vertArray[1] = { (long)(x + sideA), (long)y };
            vertArray[2] = { (long)x, (long)(y - sideB) };
        }
    };


    class TriangleIsosceles :public Triangle
    {
    public:
        TriangleIsosceles(double side, double base, SHAPE_TAKE_PARAMETERS)
            :Triangle(base, side, side, SHAPE_GIVE_PARAMETERS) {}

        void getVerticles(POINT vertArray[3]) const override
        {
            vertArray[0] = { (long)x, (long)y };
            vertArray[1] = { (long)(x + sideA), (long)y };
            vertArray[2] = { (long)(x + sideA / 2), (long)(y - sideB) };
        }
    };


    class TriangleEquilateral :public Triangle
    {
    public:
        TriangleEquilateral(double side, SHAPE_TAKE_PARAMETERS)
            :Triangle(side, side, side, SHAPE_GIVE_PARAMETERS) {}

        void getVerticles(POINT vertArray[3]) const override
        {
            vertArray[0] = { (long)x, (long)y };
            vertArray[1] = { (long)(x + sideA), (long)y };
            vertArray[2] = { (long)(x + sideA / 2), (long)(y - sideA) };
        }
    };

    Shape* ShapeFactory(int shapeID)
    {
#define PARAMS rand() % 700, rand() % 300, rand() % Shape::MAX_LINE_WIDTH, RGB(rand(), rand(), rand())
        Shape* shape = nullptr;
        const unsigned int maxSize = Shape::MAX_SIZE / 2;
        switch (shapeID)
        {
        case 1:
            shape = new Rectangle(rand() % maxSize, rand() % maxSize, PARAMS);
            break;
        case 2:
            shape = new Square(rand() % maxSize, PARAMS);
            break;
        case 3:
            shape = new Circle(rand() % maxSize, PARAMS);
            break;
        case 4:
            shape = new TriangleScalene(
                rand() % maxSize, rand() % maxSize, rand() % maxSize,
                PARAMS);
            break;
        case 5:
            shape = new TriangleRight(rand() % maxSize, rand() % maxSize, PARAMS);
            break;
        case 6:
            shape = new TriangleIsosceles(rand() % maxSize, rand() % maxSize, PARAMS);
            break;
        case 7:
            shape = new TriangleEquilateral(rand() % maxSize, PARAMS);
            break;
        default:
            break;
        }
        return shape;
    }
}

int main()
{
    setlocale(LC_ALL, "");
    srand(time(NULL));

    const size_t shapeArraySize = 20;
    unsigned int posY = 100;
    unsigned int lineWidth = 8;

#ifdef USING_ENUM_COLOR
    MyGeometry::Shape* shapes[shapeArraySize]
    {
        new MyGeometry::Rectangle(100, 50, 30, posY, lineWidth, MyGeometry::Color::AQUAMARINE),
        new MyGeometry::Square(50, 160, posY, lineWidth, MyGeometry::Color::THISTLE),
        new MyGeometry::Circle(25, 240, posY, lineWidth, MyGeometry::Color::TICKLE_ME_PINK),
        new MyGeometry::TriangleScalene(30, 40, 50, 320, posY + 50, lineWidth, MyGeometry::Color::SALOMIE),
        new MyGeometry::TriangleRight(60, 50, 410, posY + 50, lineWidth, MyGeometry::Color::MEDIUM_PURPLE),
        new MyGeometry::TriangleIsosceles(80, 50, 500, posY + 50, lineWidth, MyGeometry::Color::HELIOTROPE),
        new MyGeometry::TriangleEquilateral(60, 580, posY + 50, lineWidth, MyGeometry::Color::TWILIGHT)
    };
#endif // USING_ENUM_COLOR

#ifdef USING_COLORREF

    MyGeometry::Shape* shapes[shapeArraySize];

    for (size_t i = 0; i < shapeArraySize; i++)
    {
        shapes[i] = MyGeometry::ShapeFactory(1 + rand() % 7);
    }
#endif // USING_COLORREF

    for (size_t i = 0; i < shapeArraySize; i++)
    {
        //shapes[i]->info();
        shapes[i]->draw();
        Sleep(500);
    }

    for (size_t i = 0; i < shapeArraySize; i++)
    {
        delete[]shapes[i];
    }
}
