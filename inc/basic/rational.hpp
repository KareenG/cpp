#pragma once

#include <iostream>

namespace basic {
    /**
    * Represents a rational number defined by a numerator and a denominator.
    */
    class Rational {
        public:
            /**
            * Default constructor. Initializes the rational number to 0/1 if no parameters are provided.
            * @param numerator The numerator of the rational number, defaulting to 0.
            * @param denominator The denominator of the rational number, defaulting to 1.
            *                      It cannot be zero, and the constructor will assert if zero is provided.
            */
            Rational(int numerator = 0, int denominator = 1);

            /**
            * Copy constructor. Creates a new Rational object as a copy of an existing one.
            * @param other A reference to the Rational object to copy.
            */
            Rational(Rational const& other);

            /**
            * Copy assignment operator. Assigns the value of one Rational object to another.
            * @param other A reference to the Rational object to assign from.
            * @return A reference to the updated current object.
            */
            Rational& operator=(Rational const& other);

            /**
            * Default destructor. Destroys the Rational object.
            */
            ~Rational() = default;

            /**
            * Adds another Rational object to this one.
            * @param other The Rational object to add to this one.
            * @return A reference to the current object after addition.
            */
            Rational& operator+=(Rational const& other);

            /**
            * Subtracts another Rational object from this one.
            * @param other The Rational object to subtract from this one.
            * @return A reference to the current object after subtraction.
            */
            Rational& operator-=(Rational const& other);

            /**
            * Multiplies another Rational object with this one.
            * @param other The Rational object to multiply with this one.
            * @return A reference to the current object after multiplication.
            */
            Rational& operator*=(Rational const& other);

            /**
            * Divides this Rational object by another.
            * @param other The Rational object to divide this one by.
            * @return A reference to the current object after division.
            */
            Rational& operator/=(Rational const& other);

            /**
            * Accessor for the numerator of the rational number.
            * @return The numerator of the rational number.
            */
            int numerator() const;

            /**
            * Accessor for the denominator of the rational number.
            * @return The denominator of the rational number.
            */
            int denominator() const;

            /**
            * Reduces the rational number to its simplest form.
            */
            void reduce();

            /**
            * Calculates and returns the inverse of this rational number.
            * @return A new Rational object that is the inverse of this one.
            */
            Rational inverse() const;

            /**
            * Calculates and returns the decimal value of the rational number.
            * @return The decimal (floating-point) value of the rational number.
            */
            double value() const;

            /**
            * Explicit conversion operator to float. Converts the rational number to a float.
            * @return The float representation of the rational number.
            */
            explicit operator float() const;
            
        private:
            /**
            * Helper function for handling sign. the '-' if present will be the sign of the numerator,
            * denominator will always be positive.
            * @param numerator A reference to the numerator to adjust based on the denominator.
            * @param denominator A reference to the denominator to adjust.
            */
            void build_fraction(int& numerator, int& denominator);

            /**
            * Helper function to calculate the greatest common divisor of two integers.
            * @param a The first integer.
            * @param b The second integer.
            * @return The greatest common divisor of a and b.
            */
            int gcd(int a, int b);

        private:
            int numerator_;     // The numerator of the rational number.
            int denominator_;   // The denominator of the rational number.
    };
    
    /**
    * Adds two Rational objects and returns the result as a new Rational object.
    * @param lhs The left-hand side Rational object.
    * @param rhs The right-hand side Rational object.
    * @return A new Rational object that represents the sum of lhs and rhs.
    */
    Rational operator+(Rational const& lhs, Rational const& rhs);

    /**
    * Subtracts one Rational object from another and returns the result as a new Rational object.
    * @param lhs The left-hand side Rational object from which rhs will be subtracted.
    * @param rhs The right-hand side Rational object to subtract from lhs.
    * @return A new Rational object that represents the difference of lhs and rhs.
    */
    Rational operator-(Rational const& lhs, Rational const& rhs);

    /**
    * Multiplies two Rational objects and returns the result as a new Rational object.
    * @param lhs The left-hand side Rational object.
    * @param rhs The right-hand side Rational object.
    * @return A new Rational object that represents the product of lhs and rhs.
    */
    Rational operator*(Rational const& lhs, Rational const& rhs);

    /**
    * Divides one Rational object by another and returns the result as a new Rational object.
    * @param lhs The left-hand side Rational object.
    * @param rhs The right-hand side Rational object, which must not be zero.
    * @return A new Rational object that represents the quotient of lhs and rhs.
    */
    Rational operator/(Rational const& lhs, Rational const& rhs);

    /**
    * Checks if two Rational objects are equal.
    * @param lhs The left-hand side operand of the comparison.
    * @param rhs The right-hand side operand of the comparison.
    * @return True if the two Rational objects are equivalent, false otherwise.
    */
    bool operator==(Rational const& lhs, Rational const& rhs);

    /**
    * Checks if two Rational objects are not equal.
    * @param lhs The left-hand side operand of the comparison.
    * @param rhs The right-hand side operand of the comparison.
    * @return True if the two Rational objects are not equivalent, false otherwise.
    */
    bool operator!=(Rational const& lhs, Rational const& rhs);

    /**
    * Determines if the left-hand side Rational object is less than the right-hand side object.
    * @param lhs The left-hand side operand of the comparison.
    * @param rhs The right-hand side operand of the comparison.
    * @return True if lhs is less than rhs, false otherwise.
    */
    bool operator<(Rational const& lhs, Rational const& rhs);

    /**
    * Determines if the left-hand side Rational object is less than or equal to the right-hand side object.
    * @param lhs The left-hand side operand of the comparison.
    * @param rhs The right-hand side operand of the comparison.
    * @return True if lhs is less than or equal to rhs, false otherwise.
    */
    bool operator<=(Rational const& lhs, Rational const& rhs);

    /**
    * Determines if the left-hand side Rational object is greater than the right-hand side object.
    * @param lhs The left-hand side operand of the comparison.
    * @param rhs The right-hand side operand of the comparison.
    * @return True if lhs is greater than rhs, false otherwise.
    */
    bool operator>(Rational const& lhs, Rational const& rhs);

    /**
    * Determines if the left-hand side Rational object is greater than or equal to the right-hand side object.
    * @param lhs The left-hand side operand of the comparison.
    * @param rhs The right-hand side operand of the comparison.
    * @return True if lhs is greater than or equal to rhs, false otherwise.
    */
    bool operator>=(Rational const& lhs, Rational const& rhs);

    /**
    * Overloads the output stream operator for printing Rational objects.
    * @param os The output stream.
    * @param r The Rational object to output.
    * @return A reference to the output stream.
    */
    std::ostream& operator<<(std::ostream& os, const Rational& r);

}   // namespace basic