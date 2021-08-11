// example of composition using private inheritance
#include <iostream>
#include <memory>

class Engine
{
    int cylinders;
public:
    Engine(int cylinders): cylinders(cylinders) {};
    void start()
    {
        std::cout << "engine starts" << '\n';
    }
};

class Car : private Engine
{
public: 
    Car() : Engine(8) {};
    using Engine::start; // this idiom is used to access a member from the base class otherwise we wouldn't be able co call start from a Car instance because start is part of Engine and it's private
    // it becomes private because of the private inheritance
};

void someFunction(const std::shared_ptr<Car>& someCar)
{
    someCar->start();
};

int main()
{
    std::shared_ptr<Car> newCar;
    std::unique_ptr<Car> FirstCar;
    {
        std::unique_ptr<Car> car = std::make_unique<Car>();
        FirstCar = std::unique_ptr<Car>(new Car());
        newCar = std::make_shared<Car>(*car.get());
        someFunction(newCar);
        car->start();
    }
    FirstCar->start();
    newCar->start();
}