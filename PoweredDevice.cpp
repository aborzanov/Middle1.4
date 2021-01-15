#include <iostream>

class PoweredDevice
{
public:
	PoweredDevice(int power)
	{
		std::cout << "PoweredDevice: " << power;
	}
};

class Scaner : public PoweredDevice
{
public:
	Scaner(int scaner, int power)
		:PoweredDevice(power)
	{
		std::cout << "Scaner: " << scaner;
	}
};
class Printer : public PoweredDevice
{
public:
	Printer(int printer, int power)
		:PoweredDevice(power)
	{
		std::cout << "Printer: ";
	}
};
class Copier : public Scaner, public Printer
{
public:
	Copier(int printer, int scaner, int power)
		: Scaner(scaner, power), Printer(printer, power)
	{

	}
};