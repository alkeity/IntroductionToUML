#include<iostream>
#include<string>
#include<Windows.h>

using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n|----------------------------------------------|\n"


template<typename T>
class Color
{
protected:
	T red;
	T green;
	T blue;

	virtual T checkValue(T value) = 0;

public:

	// constructors, destructor

	Color()
	{
		red = 0;
		green = 0;
		blue = 0;
		cout << this << ": default color (black) created\n";
	}

	Color(int red, int green, int blue)
	{
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

	void setRed(T value) { red = checkValue(value); }
	void setGreen(T value) { green = checkValue(value); }
	void setBlue(T value) { blue = checkValue(value); }

	// getters

	const T& getRed() const { return red; }
	const T& getGreen() const { return green; }
	const T& getBlue() const { return blue; }

	// methods
	void printInfo() const
	{
		cout << delimiter;
		cout << typeid(*this).name() << endl;
		cout << "RGB values: " << red << "." << blue << "." << green << endl;
	}
};


class ColorInt : public Color<unsigned int>
{
	unsigned int checkValue(unsigned int value) override
	{
		value < 0 ? value = 0 : value > 255 ? value = 255 : value;
		return value;
	}

public:
	ColorInt(unsigned int red, unsigned int green, unsigned int blue) : Color(red, green, blue) {}

	COLORREF getColorRef() const { return RGB(red, blue, green); }
};


class ColorFloat : public Color<float>
{
	float checkValue(float value) override
	{
		value < 0 ? value = 0 : value > 1 ? value = 1 : value;
		return value;
	}

public:
	ColorFloat(float red, float green, float blue) : Color(red, green, blue) {}
};
