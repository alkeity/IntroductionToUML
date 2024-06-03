#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<thread>

using std::cin;
using std::cout;
using std::endl;

#define MIN_TANK_VOLUME 20
#define MAX_TANK_VOLUME 150

#define MIN_ENGINE_CONSUMPTION 3
#define MAX_ENGINE_CONSUMPTION 30

#define MAX_SPEED_LOW_LIMIT 120
#define MAX_SPEED_HIGH_LIMIT 400

#define MAX_ACCELERATION 10 // For every car the default acceleration is at most 10 km/h per second.
#define MAX_BRAKE 10 // Every car brakes at most 10 km/h per second.
#define DEFAULT_BRAKE 1 // If the car is free-wheeling (no pedal is used), it slows down the car by 1 km/h by air resistance and rolling resistance.

#define Esc 27
#define Enter 13
#define Space 32
#define ArrowUp 72
#define ArrowDown 80

// TODO natural slowdown if no acceleration
bool isExit = false;

class FuelTank
{
    const int VOLUME; // характеристика объекта
    double fuelLevel; // состояние объекта

public:
    FuelTank(int volume):VOLUME
    (
        volume < MIN_TANK_VOLUME ? MIN_TANK_VOLUME :
        volume > MAX_TANK_VOLUME ? MAX_TANK_VOLUME :
        volume
    )
    {
        fuelLevel = 0;
        cout << this << ": tank ready\n";
    }

    ~FuelTank()
    {
        cout << this << ": tank rip\n";
    }

    int getVolume() const { return VOLUME; }

    double getFuelLevel() const { return fuelLevel; }

    void fill(double amount) // fuel level setter
    {
        if (amount < 0) { return; }
        fuelLevel += amount;
        if (fuelLevel > VOLUME) { fuelLevel = VOLUME; }
    }
    double giveFuel(double amount)
    {
        fuelLevel -= amount;
        if (fuelLevel < 0) { fuelLevel = 0; }
        return fuelLevel;
    }

    void info() const
    {
        cout << "Volume: " << VOLUME << " liters\n";
        cout << "Fuel level: " << getFuelLevel() << " liters\n";
    } 
};

class Engine
{
    const double CONSUMPTION;
    double consumptionPerSec;
    bool isStarted;

public:
    Engine(double consumption):CONSUMPTION
    (
        consumption < MIN_ENGINE_CONSUMPTION ? MIN_ENGINE_CONSUMPTION :
        consumption > MAX_ENGINE_CONSUMPTION ? MAX_ENGINE_CONSUMPTION :
        consumption
    )
    {
        setConsumptionPerSec();
        isStarted = false;
        cout << this << ": engine ready\n";
    }

    ~Engine()
    {
        cout << this << ": engine rip\n";
    }

    double getCONSUMPTION() const { return CONSUMPTION; }

    double getConsumptionPerSec() const { return consumptionPerSec; }

    void setConsumptionPerSec()
    {
        consumptionPerSec = CONSUMPTION * 3e-5;
    }

    void start()
    {
        isStarted = true;
        cout << this << ": engine started\n";
    }

    void stop()
    {
        isStarted = false;
        cout << this << ": engine stopped\n";
    }

    bool started() const { return isStarted; }

    void info() const
    {
        cout << "Consumption: " << CONSUMPTION << " liters/100km\n";
        cout << "Consumption per second: " << consumptionPerSec << " liters/second\n";
        cout << "Is started: ";
        if (isStarted) { cout << "Yes\n"; }
        else { cout << "No\n"; }
    }
};

class Car
{
    Engine engine;
    FuelTank tank;
    const int MAX_SPEED;
    int speed;
    bool isDriverInside;

    struct
    {
        std::thread panelThread;
        std::thread consumeFuelThread;
        std::thread slowdownThread;
    } controlThreads;
public:
    Car(int maxSpeed, double consumption, int tankVolume):engine(consumption), tank(tankVolume),
        MAX_SPEED(
            maxSpeed < MAX_SPEED_LOW_LIMIT ? MAX_SPEED_LOW_LIMIT :
            maxSpeed > MAX_SPEED_HIGH_LIMIT ? MAX_SPEED_HIGH_LIMIT :
            maxSpeed
        )
    {
        speed = 0;
        isDriverInside = false;
        cout << this << ": car ready\n";
        cout << "Press Enter to get in\n";
    }

    ~Car()
    {
        cout << this << ": car over\n";
    }

    void info() const
    {
        engine.info();
        tank.info();
        cout << "Max speed: " << MAX_SPEED << " km/h\n";
    }

    void panel()
    {
        while (isDriverInside)
        {
            system("cls");
            cout << "Speed: " << speed << " km/h\n";
            cout << "Engine is: " << (engine.started() ? "started" : "stopped") << " \n";
            cout << "Fuel level: " << tank.getFuelLevel() << " liters\n";
            cout << "Consumption: " << getEngineConsumption() << " liters/sec\n";
            Sleep(500);
        }
    }

    void getIn()
    {
        isDriverInside = true;
        controlThreads.panelThread = std::thread(&Car::panel, this);
    }

    void getOut()
    {
        isDriverInside = false;
        if (controlThreads.panelThread.joinable())
        {
            controlThreads.panelThread.join();
        }
        system("cls");
        cout << "You got out from car\n";
    }

    void control()
    {
        char key;
        controlThreads.slowdownThread = std::thread(&Car::slowDownDefault, this);
        do
        {
            key = _getch();
            switch (key)
            {
            case Enter:
                // isDriverInside ? getOut() : getIn();
                if (isDriverInside) { if (speed == 0) { getOut(); } }
                else { getIn(); }
                break;
            case Space:
                if (isDriverInside)
                {
                    engine.started() ? stopEngine() : startEngine();
                }
                break;
            case ArrowUp:
                if (isDriverInside && engine.started()) { accelerate(MAX_ACCELERATION); }
                break;
            case ArrowDown:
                if (isDriverInside) { slowDown(MAX_BRAKE); }
                break;
            case Esc:
                stopEngine();
                getOut();
                isExit = true;
                break;
            default:
                break;
            }
        } while (key != Esc);
        cout << "(pls give it a couple of seconds, it's stopping slowdown thread...)\n";
        if (controlThreads.slowdownThread.joinable())
        {
            controlThreads.slowdownThread.join();
        }
    }

    void refuel(double amount) { tank.fill(amount); }

    double getEngineConsumption()
    {
        if (speed == 0) { return engine.getConsumptionPerSec(); }
        else if ((double)speed / MAX_SPEED < 0.2) { return engine.getCONSUMPTION() * 2e-4; }
        else if ((double)speed / MAX_SPEED < 0.4) { return engine.getCONSUMPTION() * 14e-5; }
        else if ((double)speed / MAX_SPEED < 0.6) { return engine.getCONSUMPTION() * 2e-4; }
        else if ((double)speed / MAX_SPEED < 0.8) { return engine.getCONSUMPTION() * 25e-5; }
        else { return engine.getCONSUMPTION() * 3e-4; }
    }

    void consumeFuel() // func call == 1 second
    {

        while (engine.started())
        {
            if (tank.giveFuel(getEngineConsumption()) <= 0)
            {
                engine.stop();
                break;
            }
            Sleep(500);
        }
    }

    void startEngine()
    {
        if (tank.getFuelLevel() > 0)
        {
            engine.start();
            controlThreads.consumeFuelThread = std::thread(&Car::consumeFuel, this);
        }
    }

    void stopEngine()
    {
        engine.stop();
        if (controlThreads.consumeFuelThread.joinable())
        {
            controlThreads.consumeFuelThread.join();
        }
    }

    void accelerate(int amount)
    {
        amount < 0 ? amount = 0 :
            amount > MAX_ACCELERATION ? amount = MAX_ACCELERATION :
            amount;

        speed += amount;

        speed > MAX_SPEED ? speed = MAX_SPEED : speed;
    }

    void slowDown(int amount)
    {
        amount < 0 ? amount = 0 :
            amount > MAX_BRAKE ? amount = MAX_BRAKE :
            amount;

        speed -= amount;

        speed < 0 ? speed = 0 : speed;
    }

    void slowDownDefault()
    {
        while (true)
        {
            if (isExit) { break; }
            slowDown(DEFAULT_BRAKE);
            Sleep(4000); // TODO <chrono> or <time> maybe??
        }
    }
};

//#define TANK_CHECK // директивы препроцессора

void main()
{
    setlocale(LC_ALL, "");
    //int fuel;

    Car bmw(250, 10, 80);
    bmw.refuel(1);

    //bmw.info();

    bmw.control();

#if defined TANK_CHECK
    FuelTank tank(3000);
    do
    {
        tank.info();
        cout << "Введите объем топлива: ";
        cin >> fuel;
        tank.fill(fuel);
    } while (fuel);
#endif

    //Engine engine(10);
    //engine.printInfo();
}
