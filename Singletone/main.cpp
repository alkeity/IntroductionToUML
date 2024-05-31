#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<time.h>

using std::cout;
using std::cin;
using std::endl;

class Human
{
	static Human* instance;
	std::string firstName;
	std::string lastName;
	tm birthDate;

	Human()
	{
		cout << "ctor Human:\t" << this << endl;
	}
public:
	const std::string& getFirstName() const
	{
		// Константный метод обязательно должен возвращать константное значение
		// константный метод не может изменять this
		return firstName;
	}

	const std::string& getLastName() const
	{
		return lastName;
	}

	const tm& getBirthDate() const
	{
		return birthDate;
	}

	void setLastName(const std::string& lastName) { this->lastName = lastName; }

	void setFirstName(const std::string& firstName) { this->firstName = firstName; }

	void setBirthDate(const tm& birthDate) { this->birthDate = birthDate; }

	void setBirthDate(int year, int month, int day)
	{
		birthDate.tm_year = year - 1900;
		birthDate.tm_mon = month - 1;
		birthDate.tm_mday = day;
	}

	~Human()
	{
		cout << "dtor Human:\t" << this << endl;
	}

	void print() const
	{
		time_t rtime;
		time(&rtime);
		tm* currentTime = localtime(&rtime);
		unsigned int age = currentTime->tm_year - birthDate.tm_year;
		if (currentTime->tm_yday < birthDate.tm_year) { age--; }
		
		cout << firstName << " " << lastName << " " << age << " y/o" << endl;
	}

	static Human& getInstance()
	{
		if (instance == nullptr) { instance = new Human(); }
		return *instance;
	}
};

Human* Human::instance = nullptr;

int main()
{
	setlocale(LC_ALL, "");
	Human main = Human::getInstance();

	main.setLastName("Vercetty");
	main.setFirstName("Tommy");
	main.setBirthDate(1991, 9, 6);

	main.print();

}