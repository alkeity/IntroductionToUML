#include<iostream>
#include<Windows.h>

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
        BLACK = 0x00000000
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
            /*for (size_t i = 0; i < height; i++)
            {
                for (size_t j = 0; j < width; j++)
                {
                    cout << "*";
                }
                cout << endl;
            }*/

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

        void info() const override
        {
            cout << typeid(*this).name() << endl;
            cout << "Ширина: " << width << endl;
            cout << "Высота: " << height << endl;
            Shape::info();
        }
    };
}

int main()
{
    setlocale(LC_ALL, "");
    MyGeometry::Rectangle rect(100, 50, 100, 200, 8, MyGeometry::Color::BLUE);
    rect.info();
}
