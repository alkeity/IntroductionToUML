#include"Shapes.h"
using std::cout;
using std::cin;
using std::endl;

//В проекте 'Factory' реализовать иерархию геометрических фигур :
//Квадрат, Прямоугольник, Крут, треугольник.......
//для каждой фигуры нужно вывести ее первичные свойства, например,
//длина сторон, радиус ........и вторичные свойства : диагональ,
//площадь, периметр....
//Так же каждую фигуру нужно нарисовать.
//
//Необходимо сгенерировать все эти фигуры в случайном порядке со случайными свойствами.


int main()
{
	setlocale(LC_ALL, "");

	MyShape* shapes[4]{ new MyCircle(30, VIOLET), new SquaredTriangle(40, 30, SKYBLUE), new MyRectangle(50, 30, BEIGE), new MySquare(40, PINK)};

	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Shapes!");
	SetTargetFPS(30);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		for (size_t i = 0; i < 4; i++)
		{
			shapes[i]->draw(Vector2(100, 100 + i * 100));
		}
		EndDrawing();
	}
	CloseWindow();
}
