#include "basic/quadratic.hpp"
#include <iostream>
#include <cmath>
#include <iomanip> // Include for std::setprecision and std::fixed

namespace basic {

    Quadratic::Quadratic()
    : a{0}
    , b{}  // also to zero
    , c{}
    {        
    }

    Quadratic::Quadratic(double a, double b, double c)
    : a{a}
    , b{b}
    , c{c}
    {        
    }  
    
    // cctor
    Quadratic::Quadratic(Quadratic const& other)
    : a{other.a}
    , b{other.b}
    , c{other.c}
    {
    }

    Quadratic& Quadratic::operator=(Quadratic const& other) {
        if (this != &other) {
            a = other.a;
            b = other.b;
            c = other.c;
        }
        return *this;
    }

    Quadratic& Quadratic::operator+=(Quadratic const& other) {
        a += other.a;
        b += other.b;
        c += other.c;
        return *this;
    }

    Quadratic& Quadratic::operator-=(Quadratic const& other) {
        a -= other.a;
        b -= other.b;
        c -= other.c;
        return *this;
    }
    
    Quadratic Quadratic::operator*(double scalar) const {
        return Quadratic(a * scalar, b * scalar, c * scalar);
    }

    int find_roots(Quadratic const& q, Roots& roots) {
        double discriminant = q.b * q.b - 4 * q.a * q.c;
        if(q.a == 0)
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
            roots.first = -q.b / (2 * q.a);
            roots.second = -1;
            return 1;
        }
        roots.first = (-q.b + sqrt(discriminant)) / (2 * q.a);
        roots.second = (-q.b - sqrt(discriminant)) / (2 * q.a);
        return 2;
    }

    double value(Quadratic const& q, double x) {
        return q.a * (x * x) + q.b * x + q.c;
    }

    void print (Quadratic const& q) {
        std::cout << std::fixed << std::setprecision(2); // Set the decimal precision
        std::cout << q.a << " X^2 ";
        if (q.b < 0)
            std::cout << "- " << std::fabs(q.b) << " X ";
        else
            std::cout << "+ " << std::fabs(q.b) << " X ";
        
        if (q.c < 0)
            std::cout << "- " << std::fabs(q.c);
        else
            std::cout << "+ " << std::fabs(q.c);
        
        std::cout << std::endl;
    }

    Quadratic multiply_by_scalar(const Quadratic& q, double scalar) {
        return q * scalar;
    }
    
} // namespace basic

