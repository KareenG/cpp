#include "basic/rational.hpp"
#include <cassert>
#include <stdlib.h>

namespace basic {
    Rational::Rational(int numerator, int denominator)
    : numerator_{numerator}
    , denominator_{denominator}
    {  
        assert(denominator);
        build_fraction(numerator_, denominator_);
    }

    Rational::Rational(Rational const& other)
    : numerator_{other.numerator_}
    , denominator_{other.denominator_}
    {
    }

    Rational& Rational::operator=(Rational const& other) 
    {
        if (this != &other) {
            numerator_ = other.numerator_;
            denominator_ = other.denominator_;
        }
        return *this;
    }

    int Rational::numerator() const
    {
        return numerator_;
    }

    int Rational::denominator() const
    {
        return denominator_;
    }

    Rational& Rational::operator+=(Rational const& other) 
    {
        numerator_ = numerator_ * other.denominator_ + denominator_ * other.numerator_;
        denominator_ = denominator_ * other.denominator_;
        return *this;
    }

    Rational& Rational::operator-=(Rational const& other) 
    {
        numerator_ = numerator_ * other.denominator_ - denominator_ * other.numerator_;
        denominator_ = denominator_ * other.denominator_;
        return *this;
    }

    Rational& Rational::operator*=(Rational const& other) 
    {
        numerator_ = numerator_ * other.numerator_;
        denominator_ = denominator_ * other.denominator_;
        return *this;
    }

    Rational& Rational::operator/=(Rational const& other) 
    {
        numerator_ = numerator_ * other.denominator_;
        denominator_ = denominator_ * other.numerator_;
        return *this;
    }

    void Rational::reduce()
    {
        int divider = gcd(numerator_, denominator_);
        numerator_ /= divider;
        denominator_ /= divider;
    }

    Rational Rational::inverse() const
    {
        return Rational(denominator_, numerator_);
    }

    double Rational::value() const
    {
        double val = static_cast<double>(numerator_)/denominator_;
        return val;
    }

    Rational operator+(Rational const& lhs, Rational const& rhs)
    {
        int new_numerator = lhs.numerator() * rhs.denominator() + lhs.denominator() * rhs.numerator();
        int new_denominator = lhs.denominator() * rhs.denominator();
        return Rational(new_numerator, new_denominator);
    }

    Rational operator-(Rational const& lhs, Rational const& rhs)
    {
        int new_numerator = lhs.numerator() * rhs.denominator() - lhs.denominator() * rhs.numerator();
        int new_denominator = lhs.denominator() * rhs.denominator();
        return Rational(new_numerator, new_denominator);
    }

    Rational operator*(Rational const& lhs, Rational const& rhs)
    {
        int new_numerator = lhs.numerator() * rhs.numerator();
        int new_denominator = lhs.denominator() * rhs.denominator();
        return Rational(new_numerator, new_denominator);
    }

    Rational operator/(Rational const& lhs, Rational const& rhs)
    {
        int new_numerator = lhs.numerator() * rhs.denominator();
        int new_denominator = lhs.denominator() * rhs.numerator();
        return Rational(new_numerator, new_denominator);
    }

    void Rational::build_fraction(int& numerator, int& denominator) 
    {
        if (numerator * denominator < 0) {
            numerator = -std::abs(numerator);
            denominator = std::abs(denominator);
        } else if (numerator * denominator == 0) {
            numerator = 0;
            denominator = 1;
        } else {
            numerator = std::abs(numerator);
            denominator = std::abs(denominator);
        }
    }

    int Rational::gcd(int a, int b) 
    {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    Rational::operator float() const 
    {
        return static_cast<float>(numerator_) / denominator_;
    }

    bool operator==(Rational const& lhs, Rational const& rhs)
    {
        int first = lhs.numerator() * rhs.denominator();
        int second = lhs.denominator() * rhs.numerator();
        return (first == second);
    }

    bool operator!=(Rational const& lhs, Rational const& rhs)
    {
        int first = lhs.numerator() * rhs.denominator();
        int second = lhs.denominator() * rhs.numerator();
        return !(first == second);
    }

    bool operator<(Rational const& lhs, Rational const& rhs)
    {
        int first = lhs.numerator() * rhs.denominator();
        int second = lhs.denominator() * rhs.numerator();
        return (first < second);
    }

    bool operator<=(Rational const& lhs, Rational const& rhs)
    {
        int first = lhs.numerator() * rhs.denominator();
        int second = lhs.denominator() * rhs.numerator();
        return !(first < second);
    }
    
    bool operator>(Rational const& lhs, Rational const& rhs)
    {
        int first = lhs.numerator() * rhs.denominator();
        int second = lhs.denominator() * rhs.numerator();
        return (first > second);
    }

    bool operator>=(Rational const& lhs, Rational const& rhs)
    {
        int first = lhs.numerator() * rhs.denominator();
        int second = lhs.denominator() * rhs.numerator();
        return !(first > second);
    }

    std::ostream& operator<<(std::ostream& os, const Rational& r)
    {
        os << r.numerator() << '/' << r.denominator() << '\n';
        return os;
    }

}   // namespace basic