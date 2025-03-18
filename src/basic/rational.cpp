#include "basic/rational.hpp"
#include "basic/math.hpp"
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
        assert(other.numerator_);
        int sign = (numerator_ * other.numerator_ < 0) ? -1 : 1;
        numerator_ = std::abs(numerator_ * other.denominator_);
        denominator_ *= std::abs(other.numerator_);
        *this *= sign;
        return *this;
    }

    void Rational::operator*=(int scalar)
    {
        numerator_ *= scalar;
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
        Rational r = lhs;
        r += rhs;
        return r;
    }

    Rational operator-(Rational const& lhs, Rational const& rhs)
    {
        Rational r = rhs;
        r *= -1;
        return lhs + r;
    }

    Rational operator*(Rational const& lhs, Rational const& rhs)
    {
        Rational r = lhs;
        r *= rhs;
        return r;
    }

    Rational operator/(Rational const& lhs, Rational const& rhs)
    {
        Rational r = lhs;
        r /= rhs;
        return r;
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

    std::ostream& Rational::print(std::ostream& os) const
    {
        os << numerator_ << '/' << denominator_ << '\n';
        return os;
    }

    bool Rational::is_equal_or_smaller(Rational const& other) const
    {
        return numerator_ * other.denominator_ <= denominator_ * other.numerator_;
    }

    bool Rational::is_equal_or_bigger(Rational const& other) const
    {
        return numerator_ * other.denominator_ >= denominator_ * other.numerator_;
    }

    Rational::operator double() const 
    {
        return static_cast<double>(numerator_) / denominator_;
    }

    bool operator==(Rational const& lhs, Rational const& rhs)
    {
        return ((lhs <= rhs) && (lhs >= rhs));
    }

    bool operator!=(Rational const& lhs, Rational const& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator<(Rational const& lhs, Rational const& rhs)
    {
        return !(lhs >= rhs);
    }

    bool operator<=(Rational const& lhs, Rational const& rhs)
    {
        return lhs.is_equal_or_smaller(rhs);
    }
    
    bool operator>(Rational const& lhs, Rational const& rhs)
    {
        return !(lhs <= rhs);
    }

    bool operator>=(Rational const& lhs, Rational const& rhs)
    {
        return lhs.is_equal_or_bigger(rhs);
    }

    std::ostream& operator<<(std::ostream& os, const Rational& r)
    {
        return r.print(os);
    }

}   // namespace basic