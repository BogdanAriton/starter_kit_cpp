#include <iostream>

class Rectangle
{
public:
    Rectangle(int with, int height) : with(with), height(height) {};
    int area() const { return this->with * this->height; };
    virtual void setWith(int width) { this->with = with; };
    virtual void setHeight(int height) { this->height = height; };
    virtual int getWith() const { return this->with; };
    virtual int getHeight() const { return this->height; };
    
protected:
    int with, height;
};

// example of a violation
class Square : public Rectangle
{
public:
    Square(int size) : Rectangle(size, size) {};
    void setWith(int width) override { this->with = this->height = width; };
    void setHeight(int height) override { this->with = this->height = height; };
};

struct RectangleFactory
{
    static Rectangle CreateRectangle(int w, int h);
    static Rectangle CreateSquare(int size); // this will create a rectangle like  square
};


void process(Rectangle& r)
{
    int w = r.getWith();
    r.setHeight(10);
    printf("expected area = %d, but we got= %d", w*10, r.area());
}

int main()
{
    Rectangle rect{5, 5};
    process(rect);

    Square s {5};
    process(s);

    return 0;
}