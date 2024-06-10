#include<iostream>
#include<string>
#include<map>
#include<memory>

using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n|----------------------------------------------|\n"

//#define PROBLEM
#define SOLUTION

#ifdef PROBLEM
class RecordPlayer
{
	std::string name;
	unsigned int ID;
public:
	RecordPlayer(const std::string& name, unsigned int ID) :name(name), ID(ID) {}
	~RecordPlayer() {}

	void print()
	{
		cout << this << " " << ID << ". " << name << endl;
	}
};
#endif // PROBLEM

#ifdef SOLUTION
class RecordPlayer
{
public:
	virtual std::unique_ptr<RecordPlayer> clone() const = 0;
	virtual ~RecordPlayer() {}

	virtual void print() const = 0;
};

class CarPlayer :public RecordPlayer
{
	std::string name;
	unsigned int ID;
public:
	CarPlayer(const std::string& name, unsigned int ID) :name(name), ID(ID)
	{
		cout << this << ": ctor CarPlayer\n";
	}

	~CarPlayer()
	{
		cout << this << ": dtor CarPlayer\n";
	}

	void print() const override
	{
		cout << this << ": " << ID << " " << name << endl;
	}

	std::unique_ptr<RecordPlayer> clone() const override
	{
		return std::make_unique<CarPlayer>(*this);
	}
};

class BikePlayer :public RecordPlayer
{
	std::string name;
	unsigned int ID;
public:
	BikePlayer(const std::string& name, unsigned int ID) :name(name), ID(ID)
	{
		cout << this << ": ctor BikePlayer\n";
	}

	~BikePlayer()
	{
		cout << this << ": dtor BikePlayer\n";
	}

	void print() const override
	{
		cout << this << ": " << ID << " " << name << endl;
	}

	std::unique_ptr<RecordPlayer> clone() const override
	{
		return std::make_unique<BikePlayer>(*this);
	}
};

enum PlayerType { CAR, BIKE };

class PlayerFactory
{
	// TODO need to init map somehow
	static std::map<PlayerType, std::unique_ptr<RecordPlayer>> players;
	static void Init()
	{
		if (players.find(CAR) == players.end())
		{
			players[CAR] = std::make_unique<CarPlayer>(CarPlayer("BMW", 735));
		}
		if (players.find(BIKE) == players.end())
		{
			players[BIKE] = std::make_unique<BikePlayer>(BikePlayer("Harley Davidson", 234));
		}
	}
public:
	static std::unique_ptr<RecordPlayer> createPlayer(PlayerType type)
	{
		Init();
		return players[type]->clone();
	}
};

#endif // SOLUTION


int main()
{
	setlocale(LC_ALL, "");

#ifdef PROBLEM
	RecordPlayer carPlayerTemplate("Car player", 100);
	RecordPlayer bikePlayerTemplate("Bike player", 200);

	carPlayerTemplate.print();
	bikePlayerTemplate.print();

	RecordPlayer carPlayer = carPlayerTemplate;
	carPlayer.print();

	RecordPlayer bikePlayer = bikePlayerTemplate;
	bikePlayer.print();
#endif // PROBLEM
	////smart pointers automate process of deleting objects
#ifdef SOLUTION
	/*cout << delimiter;
	std::unique_ptr<RecordPlayer> carPlayer = PlayerFactory::createPlayer(CAR);
	carPlayer->print();
	cout << delimiter;

	std::unique_ptr<RecordPlayer> bikePlayer = PlayerFactory::createPlayer(BIKE);
	bikePlayer->print();
	cout << delimiter;*/
#endif // SOLUTION
}
