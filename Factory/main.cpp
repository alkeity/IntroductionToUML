#include<iostream>
#include<vector>
#include<random>
#include"ShapeFactory.h"

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

std::vector<MyShape*> createShapes(int amount)
{
	ShapeFactory* creators[4]{ new CircleFactory, new SqTriangleFactory, new RectangleFactory, new SquareFactory };
	std::vector<MyShape*> shapeArray;

	for (size_t i = 0; i < amount; i++)
	{
		auto newShape = creators[rand() % 4]->create();
		shapeArray.push_back(newShape);
	}

	return shapeArray;
}


int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));

	const int screenWidth = 800;
	const int screenHeight = 600;
	std::vector<MyShape*> shapes = createShapes(10);

	InitWindow(screenWidth, screenHeight, "Shapes!");
	SetTargetFPS(30);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		for (size_t i = 0; i < shapes.size(); i++)
		{
			shapes[i]->draw();
		}
		EndDrawing();
	}
	CloseWindow();
}
