#include <iostream>
#include <functional>
#include <string>
#include <new>

#define str_name(x) {#x}

class Calculations
{
    int _no1;
    int _no2;
    int incremenet;

public:
    Calculations(int _no1 = 1, int _no2 = 1, int incremenet = 0) :
     _no1(_no1), 
     _no2(_no2),
     incremenet(incremenet)
    {
        std::cout << "Implicit constructor\n";
    }

    Calculations( const Calculations& rhs)
    {
        _no1 = rhs.get_no1();
        _no2 = rhs.get_no2();
        incremenet = rhs.get_increment();
        std::cout << "Copy constructor\n";
    }

    Calculations& operator=( const Calculations& rhs)
    {
        std::cout << "Copy assignment operator\n";
        if (this != &rhs)
        {
            this->_no1 = rhs.get_no1();
            this->_no2 = rhs.get_no2();
            incremenet = rhs.get_increment();
        }
        return *this;
    }

    ~Calculations() {
        std::cout << "destructor: " << std::string(*this) << std::endl;
    };

    operator std::string() const;

    void set_no1(const int& no) { this->_no1 = no; };
    int get_no1() const { return this->_no1; };
    void set_no2(const int& no) { this->_no2 = no; };
    int get_no2() const { return this->_no2; };
    int get_increment() const { return this->incremenet; }

    Calculations& operator++();
    Calculations operator++(int);
    Calculations& operator--();
    Calculations operator--(int);
};

Calculations::operator std::string() const
{
    return  " no1 = " + std::to_string(this->get_no1()) + 
    "; no2 = " +  std::to_string(this->get_no2()) + 
    "; increment = " + std::to_string(this->get_increment());
}

inline std::ostream& operator<<( std::ostream& o, const Calculations& rhs)
{
    return o << std::string(rhs);
}

Calculations& Calculations::operator++()
{
    std::cout << "Pre-Increment\n";
    this->incremenet += 1;
    return *this;
}

Calculations Calculations::operator++(int)
{
    std::cout << "Post Increment\n";
    Calculations temp = *this;
    this->incremenet += 1; 
    return temp; // we return the copy before we increment
}

Calculations& Calculations::operator--()
{
    std::cout << "Pre decrement\n";
    this->incremenet -= 1;
    return *this;
}

Calculations Calculations::operator--(int)
{
    std::cout << "Post decrement\n";
    Calculations temp = *this; // keep a copy before increment
    this->incremenet -= 1;
    return temp;
}


// functor example
class num {
    int multiply;
public:
    num() = delete;
    num( int number ): multiply(number) {}; 
    
    // just overload operator ()
    int operator()(int nr ) const { return nr * multiply; };
};

int main()
{
    Calculations t;
    std::cout << t++ << std::endl;
    std::cout << ++t << std::endl;
    std::cout << ++t << std::endl;
    std::cout << t-- << std::endl;
    std::cout << --t << std::endl;

    // Calculations *c = new(std::nothrow) Calculations[5];
    // delete[] c;

    const num times2(2);
    const num times3(3);
    const num times4(4);

    std::cout << "multiply " << 4 << " times2 = " << times2(4) << std::endl;
    std::cout << "multiply " << 6 << " times2 = " << times2(6) << std::endl;
    std::cout << "multiply " << 7 << " times2 = " << times2(7) << std::endl;
    std::cout << "multiply " << 8 << " times2 = " << times2(8) << std::endl;
    std::cout << "multiply " << 10 << " times2 = " << times2(10) << std::endl;

    std::cout << t << std::endl;

}