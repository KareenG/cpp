#include "basic/quadratic.hpp"
#include <iostream>
#include <cmath>
#include <iomanip> // Include for std::setprecision and std::fixed

namespace basic {

    Quadratic::Quadratic()
    : a{0}
    , b{}
    , c{}
    {        
    }

    Quadratic::Quadratic(double a, double b, double c)
    : a{a}
    , b{b}
    , c{c}
    {        
    }  
    
    Quadratic::Quadratic(Quadratic const& other)
    : a{other.a}
    , b{other.b}
    , c{other.c}
    {
    }

    int Quadratic::find_roots(Roots& roots) const {
        double discriminant = b * b - 4 * a * c;
        if(a == 0)
        {
            roots.first = -1;
            roots.second = -1;
            return 0;
        }
        if(discriminant < 0.0)
        {
            roots.first = -1;
            roots.second = -1;
            return 0;
        }
        else if(discriminant == 0.0)
        {
            roots.first = -b / (2 * a);
            roots.second = -1;
            return 1;
        }
        roots.first = (-b + sqrt(discriminant)) / (2 * a);
        roots.second = (-b - sqrt(discriminant)) / (2 * a);
        return 2;
    }

    double Quadratic::value(double x) const { 
        return a * (x * x) + b * x + c;
    }

    void Quadratic::print() const {
        // Set the decimal precision
        std::cout << std::fixed << std::setprecision(2);
        std::cout << a << " X^2 ";
        if (b < 0)
            std::cout << "- " << std::fabs(b) << " X ";
        else
            std::cout << "+ " << std::fabs(b) << " X ";
        
        if (c < 0)
            std::cout << "- " << std::fabs(c);
        else
            std::cout << "+ " << std::fabs(c);
        
        std::cout << std::endl;
    }

    Quadratic Quadratic::add(Quadratic const& other) {
        a += other.a;
        b += other.b;
        c += other.c;
        return *this;
    }

    Quadratic Quadratic::subtract(Quadratic const& other) {
        a -= other.a;
        b -= other.b;
        c -= other.c;
        return *this;
    }

    Quadratic Quadratic::multiply_by_scalar(double scalar) {
        a *= scalar;
        b *= scalar;
        c *= scalar;
        return *this;
    }
    
} // namespace basic





// Quadratic& Quadratic::operator=(Quadratic const& other) {
    //     if (this != &other) {
    //         a = other.a;
    //         b = other.b;
    //         c = other.c;
    //     }
    //     return *this;
    // }

    // Quadratic& Quadratic::operator+=(Quadratic const& other) {
    //     a += other.a;
    //     b += other.b;
    //     c += other.c;
    //     return *this;
    // }

    // Quadratic& Quadratic::operator-=(Quadratic const& other) {
    //     a -= other.a;
    //     b -= other.b;
    //     c -= other.c;
    //     return *this;
    // }
    
    // Quadratic Quadratic::operator*(double scalar) const {
    //     return Quadratic(a * scalar, b * scalar, c * scalar);
    // }