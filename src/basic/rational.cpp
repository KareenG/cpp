#include "basic/rational.hpp"
#include <cassert>


namespace basic {
    Rational::Rational(int numerator, int denominator)
    : numerator_{numerator}
    , denominator_{denominator}
    {  
        assert(denominator);
    }


    Rational::Rational(Rational const& other)
    : numerator_{other.numerator_}
    , denominator_{other.denominator_}
    {
    }

    Rational& Rational::operator=(Rational const& other) {
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

    
}   // namespace basic