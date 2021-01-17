#include <iostream>
#include <vector>

class Wheel
{
private:
	float diameter;

public:
	Wheel(float diameter) : diameter(diameter) {}
	Wheel(const Wheel& wheel) = delete;
	Wheel(Wheel&& wheel) noexcept : diameter(wheel.diameter) {}

	float getDiameter() const { return diameter; }
};


class Engine
{
private:
	float power;

public:
	Engine(float power) : power(power) { }
	Engine(const Engine& engine) = delete;
	Engine(Engine&& engine) noexcept : power(engine.power) {}

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
		: RoadVehicle(clearance)
	{
		wheels.push_back(std::move(w1));
		wheels.push_back(std::move(w2));
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
		engine(std::move(engine))
	{
		wheels.push_back(std::move(w1));
		wheels.push_back(std::move(w2));
		wheels.push_back(std::move(w3));
		wheels.push_back(std::move(w4));
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
	Car c(Engine(1), Wheel(1), Wheel(2), Wheel(3), Wheel(4), 150.0f);
	std::cout << c << '\n';

	Bicycle t(Wheel(5), Wheel(6), 300);
	std::cout << t << "\n\n";

	std::vector<Vehicle*> v;
	v.push_back(new Car(Engine(5), Wheel(1), Wheel(2), Wheel(3), Wheel(4), 100));
	v.push_back(new Car(Engine(7), Wheel(5), Wheel(6), Wheel(7), Wheel(8), 200));
	v.push_back(new Car(Engine(2), Wheel(9), Wheel(10), Wheel(11), Wheel(12), 300));
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
