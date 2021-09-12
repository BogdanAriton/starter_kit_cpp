#include <iostream>

struct Animal
{
    int i{2};
    int j{3};
    Animal(int x, int y): i(x), j(y) {};
    virtual void print() const = 0;
    virtual ~Animal() = default;
};

struct Dog: Animal
{
    Dog(int x, int y) : Animal(x, y) {};
    void print() const override 
    {
        printf("%d, %d", i ,j);
    }
};

struct Balena: Animal
{
    Balena(int x, int y) : Animal(x, y) {};
    void print() const override 
    {
        printf("%d, %d", i ,j);
    }
};

void testamPolimorfism(const Animal& var)
{
    var.print();
};

void fx(){ printf("fx ");};
void fy(){printf("fy ");};
void fz(){printf("fz ");};

int getSize()
{ 
    return 10;
};

class E1
{
    public:
    virtual void print() { std::cout << "e1"; };
    const int x;
    E1(): x(2) {};
};


class E2 : public E1
{
    public:
    void print() { std::cout << "e2"; };
};
#include <vector>
int getAge(int no)
{
    E1 e1;
    E2 e2;

    e2.x;

    std::vector<E1> vec;
    vec.push_back(e1);
    int Age = 0;
    if (no ==102)
    {
        throw(e1);
    }
    else
    {
        throw(e2);
    }

    return Age;
}

class Base
{
public:
    Base() {this->st();};
    void func() { std::cout << "Base" << '\n'; };
    virtual void st() = 0;
};

class Derived: public Base
{
public:
    void func() { std::cout << "Derived" << '\n'; };
};

class Orange
{
    enum use {Earing, Juice};
public:
    use type;
};

template <class T1, class T2>
auto myfunc(const T1 lhs, const T2& rhs) { return lhs + rhs; }

class SomeClass
{
protected:
    int data;
    friend class Another;
};

void SomeFunc(SomeClass ss)
{
    ss.data = 5;
}

class Another
{
    public:
    friend void SomeFunc(SomeClass ss);
};


int main()
{
    SomeClass sc;
    SomeFunc(sc);
    std::cout << sc.data;
}