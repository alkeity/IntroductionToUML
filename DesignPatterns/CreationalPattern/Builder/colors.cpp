#include<iostream>
#include<string>
#include<Windows.h>

using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n|----------------------------------------------|\n"


class Color
{
	std::string name;
	unsigned int red;
	unsigned int green;
	unsigned int blue;

	int checkValue(int value)
	{
		value < 0 ? value = 0 : value > 255 ? value = 255 : value;
		return value;
	}
public:
	// constructors, destructor

	Color()
	{
		name = "Black";
		red = 0;
		green = 0;
		blue = 0;
		cout << this << ": default color (black) created\n";
	}

	Color(std::string name, int red, int blue, int green)
	{
		setName(name);
		setRed(red);
		setGreen(green);
		setBlue(blue);
		cout << this << ": color created\n";
	}

	virtual ~Color()
	{
		cout << this << ": color destroyed\n";
	}

	// setters

	void setName(std::string name) { this->name = name; }
	void setRed(int value) { red = checkValue(value); }
	void setGreen(int value) { green = checkValue(value); }
	void setBlue(int value) { blue = checkValue(value); }

	// getters

	const std::string& getName() const { return name; }
	const unsigned int& getRed() const { return red; }
	const unsigned int& getGreen() const { return green; }
	const unsigned int& getBlue() const { return blue; }

	// methods

	COLORREF getColorRef() const { return RGB(red, blue, green); }

	void printInfo() const
	{
		cout << delimiter;
		cout << "Color name: " << name << endl;
		cout << "RGB values: " << red << "." << blue << "." << green << endl;
	}
};

// TODO that's not really a hierarchy thing so far, i need to sleep on it...

int main()
{
	setlocale(LC_ALL, "");
}
