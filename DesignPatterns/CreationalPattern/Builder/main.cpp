#include<iostream>
#include<string>
#include<Windows.h>

using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n|----------------------------------------------|\n"


class Computer
{
	std::string type;
	std::string motherboard;
	std::string cpu;
	std::string ram;
	std::string ssd;
	std::string hdd;
	std::string gpu;
	std::string psu;
	std::string cooler;
	std::string chassis;
	bool on;

public:
	Computer()
	{
		on = false;
		cout << this << ": default assembly\n";
	}

	Computer(
		const std::string& type,
		const std::string& motherboard,
		const std::string& cpu,
		const std::string& ram,
		const std::string& ssd,
		const std::string& hdd,
		const std::string& gpu,
		const std::string& psu,
		const std::string& cooler,
		const std::string& chassis
	)
	{
		setType(type);
		setMotherboard(motherboard);
		setCPU(cpu);
		setRAM(ram);
		setSSD(ssd);
		setHDD(hdd);
		setGPU(gpu);
		setPSU(psu);
		setCooler(cooler);
		setChassis(chassis);
		on = false;

		cout << this << ": assembly done\n";
	}

	~Computer()
	{
		cout << this << ": disassembled\n";
	}

	void setType(const std::string& type) { this->type = type; }
	void setMotherboard(const std::string& motherboard) { this->motherboard = motherboard; }
	void setCPU(const std::string& cpu) { this->cpu = cpu; }
	void setRAM(const std::string& ram) { this->ram = ram; }
	void setSSD(const std::string& ssd) { this->ssd = ssd; }
	void setHDD(const std::string& hdd) { this->hdd = hdd; }
	void setGPU(const std::string& gpu) { this->gpu = gpu; }
	void setPSU(const std::string& psu) { this->psu = psu; }
	void setCooler(const std::string& cooler) { this->cooler = cooler; }
	void setChassis(const std::string& chassis) { this->chassis = chassis; }

	const bool& isOn() const { return on; }

	void powerButton()
	{
		on = !on;
		if (on)
		{
			cout << "Загрузка Windows, пожалуйста ждите...\n";
			Sleep(500);
			cout << "Ваш рабочий стол\n";
			Sleep(500);
			info();
		}
		else
		{
			cout << "Завершение работы системы...\n";
			Sleep(500);
			cout << "Не забудь выдернуть меня из розетки\n";
		}
	}

	void info() const
	{
		cout << "Свойства системы:\n";
		cout << type << endl;
		cout << motherboard << endl;
		cout << cpu << endl;
		cout << ram << endl;
		cout << ssd << endl;
		cout << hdd << endl;
		cout << gpu << endl;
		cout << psu << endl;
		cout << cooler << endl;
		cout << chassis << endl;
	}
};


class ComputerBuilder
{
protected:
	Computer* computer;
public:
	ComputerBuilder()
	{
		this->computer = new Computer();
	}

	virtual ~ComputerBuilder()
	{
		delete this->computer;
	}

	Computer* getComputer()
	{
		return computer;
	}

	virtual void setType() = 0;
	virtual void setMotherboard() = 0;
	virtual void setCPU() = 0;
	virtual void setRAM() = 0;
	virtual void setSSD() = 0;
	virtual void setHDD() = 0;
	virtual void setGPU() = 0;
	virtual void setPSU() = 0;
	virtual void setCooler() = 0;
	virtual void setChassis() = 0;
};


class OfficeComputerBuilder :public ComputerBuilder
{
public:
	void setType() override { computer->setType("Офисный компьютер"); }
	void setMotherboard() override { computer->setMotherboard("MSI B660 MicroATX"); }
	void setCPU() override { computer->setCPU("Intel Celeron G6900 DDR4"); }
	void setRAM() override { computer->setRAM("Silicon Power 8GB"); }
	void setSSD() override { computer->setSSD("Kingston A400 240GB"); }
	void setHDD() override { computer->setHDD("Seagate Expansion+ 2TB"); }
	void setGPU() override { computer->setGPU("Intel HD Graphics"); }
	void setPSU() override { computer->setPSU("Chieftec 500W"); }
	void setCooler() override { computer->setCooler("Stock Intel Cooler"); }
	void setChassis() override { computer->setChassis("DeepCool Mini Tower"); }
};


class DevComputerBuilder :public ComputerBuilder
{
public:
	void setType() override { computer->setType("Компьютер разработчика"); }
	void setMotherboard() override { computer->setMotherboard("ASUS ROG SMAXIMUS Z790 DARK HERO"); }
	void setCPU() override { computer->setCPU("Intel Core i9-12900K"); }
	void setRAM() override { computer->setRAM("Corsair Dominator 64GB DDR5"); }
	void setSSD() override { computer->setSSD("Samsung 970 Pro M2 4000GB"); }
	void setHDD() override { computer->setHDD("Seagate Expansion+ 2TB"); }
	void setGPU() override { computer->setGPU("Geforce 4900Ti"); }
	void setPSU() override { computer->setPSU("Seasonic 1600W"); }
	void setCooler() override { computer->setCooler("Zalman CNPS-20 X"); }
	void setChassis() override { computer->setChassis("Thermaltake Divider 550 TG Ultra"); }
};

class SysAdmin
{
	ComputerBuilder* builder;
public:
	SysAdmin() :builder(nullptr) {}

	void assembleComputer(ComputerBuilder* builder)
	{
		this->builder = builder;
		builder->setType();
		builder->setMotherboard();
		builder->setCPU();
		builder->setRAM();
		builder->setSSD();
		builder->setHDD();
		builder->setGPU();
		builder->setPSU();
		builder->setCooler();
		builder->setChassis();
	}

	void turnOnComputer()
	{
		cout << delimiter;
		if (builder)
		{
			builder->getComputer()->powerButton();
		}
		else
		{
			cout << "Nothing to turn on.\n";
		}
		cout << delimiter;
	}
};

//#define PROBLEM
#define SOLUTION

int main()
{
	setlocale(LC_ALL, "");

#ifdef PROBLEM
	Computer cheapPC(
		"Бюджетный ПК",
		"MSI B660 MicroATX",
		"Intel Celeron G6900 DDR4",
		"Silicon Power 8GB",
		"Kingston A400 240GB",
		"Seagate Expansion+ 2TB",
		"Intel HD Graphics",
		"Chieftec 500W",
		"Stock Intel Cooler",
		"DeepCool Mini Tower"
	);
	cout << delimiter;
	cheapPC.powerButton();
	cout << delimiter;

	Computer gameDevPC(
		"ПК разработчика",
		"ASUS ROG SMAXIMUS Z790 DARK HERO",
		"Intel Core i9-12900K",
		"Corsair Dominator 64GB DDR5",
		"Samsung 970 Pro M2 4000GB",
		"Seagate Expansion+ 2TB",
		"Geforce 4900Ti",
		"Seasonic 1600W",
		"Zalman CNPS-20 X",
		"Thermaltake Divider 550 TG Ultra"
	);

	cout << delimiter;
	gameDevPC.powerButton();
	cout << delimiter;
#endif // PROBLEM
	
#ifdef SOLUTION
	SysAdmin admin;
	OfficeComputerBuilder computerBoss;
	DevComputerBuilder computerDev;

	admin.assembleComputer(&computerBoss);
	admin.turnOnComputer();

	admin.assembleComputer(&computerDev);
	admin.turnOnComputer();
#endif // SOLUTION

}