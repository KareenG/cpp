#include <math.h>
#include <vector>
#include <iostream>

class AbstractShape {
public:
    AbstractShape() = default;
    virtual ~AbstractShape() = default;
    virtual double area() const = 0;
protected:      // hide the fact that we wont allow copy constructor and copy assignment
    AbstractShape(AbstractShape const&) = delete;
    AbstractShape& operator=(AbstractShape const&) = delete;
};

class Rectangle : public AbstractShape {
    double length;
    double width;
public:
    Rectangle(double length, double width)
    : length{length}
    , width{width}
    {
    }
    
    Rectangle(Rectangle const&) = default; 
    
    ~Rectangle() override = default;

    virtual double area() const override {
        return length * width;
    }
};

class Circle : public AbstractShape {
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

class Square : public AbstractShape {
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

double paint_needed(std::vector<AbstractShape*>& shapes, double thickness)
{
    double total_area{0.0};
    for(AbstractShape* shape : shapes) {
        total_area += shape->area();
    }
    return total_area * thickness;
}

int main()
{
    std::vector<AbstractShape*> shapes;
    shapes.push_back(new Rectangle{5.0, 2.0});
    shapes.push_back(new Circle{4.0});
    shapes.push_back(new Square{6.0});

    std::cout << paint_needed(shapes, 0.5) << '\n';

    for (AbstractShape* p : shapes)
    {
        delete p;
    }
        
    // Rectangle r1{3, 4};
    // Rectangle r2 = r1;

    // std::vector<Rectangle> c;
}