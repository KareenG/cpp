#include <math.h>
#include <vector>
#include <iostream>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

class Rectangle : public Shape {
    double length;
    double width;
public:
    Rectangle(double length, double width)
    : length{length}
    , width{width}
    {
    }
    ~Rectangle() override = default;
    virtual double area() const override {
        return length * width;
    }
};

class Circle : public Shape {
    double radius;
public:
    Circle(double radius)
    : radius{radius}
    {
    }
    ~Circle() override = default;
    virtual double area() const override {
        return M_PI * radius * radius;
    }
};

class Square : public Shape {
    double side;
public:
    Square(double side)
    : side{side}
    {
    }
    ~Square() override = default;
    virtual double area() const override {
        return side * side;
    }
};

double paint_needed(std::vector<Shape*> shapes, double thickness)
{
    int size = static_cast<int>(shapes.size());
    double sum_areas{0.0};
    for(int i = 0; i < size; ++i) {
        sum_areas += shapes[i]->area();
    }
    return sum_areas * thickness;
}

int main()
{
    std::vector<Shape*> shapes;
    shapes.emplace_back(new Rectangle{5.0, 2.0});
    shapes.emplace_back(new Circle{4.0});
    shapes.emplace_back(new Square{6.0});
    std::cout << paint_needed(shapes, 3) << '\n';
}