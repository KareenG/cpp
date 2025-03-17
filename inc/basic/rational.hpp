#pragma once

namespace basic {
    class Rational {
        public:
            Rational(int numerator = 0, int denominator = 1);
            Rational(const Rational& other);
            Rational& operator=(const Rational& other);
            ~Rational() = default;
            Rational& operator+=(const Rational& other);
            Rational& operator-=(const Rational& other);
            Rational& operator*=(const Rational& other);
            Rational& operator/=(const Rational& other);

            int numerator() const;
            int denominator() const;

            double value() const;
            
        private:
            ;
        private:
            int numerator_;
            int denominator_;
    };
        
    Rational operator+(Rational const& lhs, Rational const& rhs);
    Rational operator-(Rational const& lhs, Rational const& rhs);
    Rational operator*(Rational const& lhs, Rational const& rhs);
    Rational operator/(Rational const& lhs, Rational const& rhs);

    bool operator==(Rational const& lhs, Rational const& rhs);
    bool operator!=(Rational const& lhs, Rational const& rhs);
    bool operator<(Rational const& lhs, Rational const& rhs);
    bool operator<=(Rational const& lhs, Rational const& rhs);
    bool operator>(Rational const& lhs, Rational const& rhs);
    bool operator>=(Rational const& lhs, Rational const& rhs);


}   // namespace basic