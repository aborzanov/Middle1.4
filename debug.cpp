#include <iostream>
#include <vector>

class Wheel
{
private:
	float diameter;

public:
	Wheel(float diameter) : diameter(diameter) { std::cout << "Wheel construct: " << diameter << "\n"; }
	Wheel(const Wheel& wheel) : diameter(wheel.diameter) { std::cout << "Wheel copy construct: " << diameter << "\n"; }

	float getDiameter() const { return diameter; }
};


class Engine
{
private:
	float power;

public:
	Engine(float power) : power(power) { std::cout << "Engine construct: " << power << "\n"; }
	Engine(const Engine& engine) : power(engine.power) { std::cout << "Engine copy construct: " << power << "\n"; }
	float getPower() const { return power; }
};


class Vehicle
{
protected:
	virtual std::ostream& print(std::ostream&) const = 0;

public:
	friend std::ostream& operator<<(std::ostream& out, const Vehicle& vehicle)
	{
		vehicle.print(out);
		return out;
	}
};


class WaterVehicle : public Vehicle
{
protected:
	float draft;

	std::ostream& print(std::ostream& out) const override
	{
		out << "WaterVehicle : " << draft;
		return out;
	}

public:
	WaterVehicle(float draft) : draft(draft) {}
};


class RoadVehicle : public Vehicle
{
protected:
	float clearance;

	std::ostream& print(std::ostream& out) const override
	{
		out << "RoadVehicle : " << clearance;
		return out;
	}

public:
	RoadVehicle(float clearance) : clearance(clearance) {}

};


class Bicycle : public RoadVehicle
{
protected:
	std::vector<Wheel> wheels;;

	std::ostream& print(std::ostream& out) const override
	{
		out << "Bicycle Wheels : ";

		for (auto it = wheels.begin(); it != wheels.end(); it++)
		{
			out << (*it).getDiameter() << ' ';
		}

		out << "Ride height : " << clearance;
		return out;
	}

public:
	Bicycle(Wheel w1, Wheel w2, float clearance)
		: RoadVehicle(clearance),
		wheels{ w1, w2 }
	{
		std::cout << "Construct: " << *this << "\n";
	}

};


class Car : public RoadVehicle
{
protected:
	Engine engine;

	std::vector<Wheel> wheels;

	std::ostream& print(std::ostream& out) const override
	{
		out << "Car Engine : " << engine.getPower() << " Wheels : ";

		for (auto it = wheels.begin(); it != wheels.end(); it++)
		{
			out << (*it).getDiameter() << ' ';
		}

		out << "Ride height : " << clearance;
		return out;
	}

public:
	Car(Engine engine, Wheel w1, Wheel w2, Wheel w3, Wheel w4, float clearance)
		: RoadVehicle(clearance),
		engine(engine),
		wheels{ w1, w2, w3, w4 }
	{
		std::cout << "Construct: " << *this << "\n";
	}

	Car(const Car& car)
		: RoadVehicle(car.clearance),
		engine(car.engine),
		wheels{ car.wheels[0], car.wheels[1], car.wheels[2], car.wheels[3] }
	{
		std::cout << "Engine copy construct: " << *this << "\n";
	}

	friend float getHighestPower(const std::vector<Vehicle*>& v);

};


float getHighestPower(const std::vector<Vehicle*>& v)
{
	Car* car = nullptr;
	float maxPower = 0;

	for (auto elem : v)
	{
		car = dynamic_cast<Car*>(elem);
		if (car && maxPower < car->engine.getPower())
		{
			maxPower = car->engine.getPower();
		}
	}

	return maxPower;

}


int main()
{
	/*
	Производил следующий результат :
	Car Engine : 150 Wheels : 17 17 18 18 Ride height : 150
	Bicycle Wheels : 20 20 Ride height : 300
	*/

	Car c(Engine(1), Wheel(1), Wheel(2), Wheel(3), Wheel(4), 150);
	std::cout << c << "\n\n";

	Bicycle t(Wheel(5), Wheel(6), 300);
	std::cout << t << "\n\n";

	std::vector<Vehicle*> v;
	v.push_back(new Car(Engine(5), Wheel(1), Wheel(2), Wheel(3), Wheel(4), 100));
	v.push_back(new Car(Engine(7), Wheel(5), Wheel(6), Wheel(7), Wheel(8), 200));
	v.push_back(new Car(Engine(2), Wheel(5), Wheel(6), Wheel(7), Wheel(8), 300));
	v.push_back(new WaterVehicle(5000));

	//Вывод элементов вектора 
	for (Vehicle* elem : v)
	{
		std::cout << *elem << "\n";
	}

	//getHighestPower
	std::cout << "\nThe highest power is " << getHighestPower(v) << '\n';

	//Удаление элементов вектора
	for (Vehicle* elem : v)
	{
		delete (elem);
	}
	v.clear();

	return 0;
}
