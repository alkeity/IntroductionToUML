#include<iostream>
#include<thread>

using namespace std;
using namespace std::chrono_literals;

bool finish = false;

void Plus()
{
	while (!finish)
	{
		cout << "+ ";
		std::this_thread::sleep_for(1s);
	}
}

void Minus()
{
	while (!finish)
	{
		cout << "- ";
		std::this_thread::sleep_for(1s);
	}
}

void main()
{
	setlocale(LC_ALL, "");
	
	std::thread plusThread(Plus);
	std::thread minusThread(Minus);

	cin.get(); // ожидает нажатие Enter
	finish = true;

	if (minusThread.joinable()) { minusThread.join(); }

	if (plusThread.joinable()) { plusThread.join(); }
}
