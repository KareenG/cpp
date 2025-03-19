#pragma once

#include <iostream>
#include "basic/rational.hpp"

namespace algebra {

/**
* Represents a polynomial of degree n with rational coefficients.
*/
class Polynomial {
public:
    explicit Polynomial(int n_degree = 0);
    Polynomial(Polynomial const& other);
    ~Polynomial();
    Polynomial& operator=(Polynomial const& other);

    /**
     * @brief Constructs a Polynomial object representing a polynomial that interpolates between two points.
     * 
     * This constructor initializes a Polynomial that interpolates between the rational points specified by the `start` 
     * and `end` pointers. Each `basic::Rational` object should represent a point on the polynomial, typically defined by a 
     * rational number indicating its position on the polynomial curve.
     * 
     * @param start A pointer to a basic::Rational object representing the starting point of the polynomial.
     * @param end A pointer to a basic::Rational object representing the ending point of the polynomial.
     */
    Polynomial(basic::Rational* start, basic::Rational* end);

    /**
     * @brief Swaps the contents of this polynomial with another polynomial.
     *
     * @param p A reference to another Polynomial object with which to swap this object's state.
     */
    void swap(Polynomial& p);    
    
    /**
     * @brief Outputs the polynomial to a stream.
     *
     * @param os A reference to an std::ostream object where the polynomial will be output.
     * @return Returns a reference to the std::ostream object to allow for chaining of output operations.
     */
    std::ostream& print(std::ostream& os) const;

    /**
     * @brief Accesses a coefficient of the polynomial by index.
     *
     * @param index The zero-based index of the coefficient in the polynomial.
     * @return Returns a reference to the `basic::Rational` representing the coefficient, allowing for modification.
     */
    basic::Rational& operator[](unsigned int index);

    /**
     * @brief Accesses a coefficient of the polynomial by index in a read-only fashion.
     *
     * @param index The index of the coefficient in the polynomial. [0] for coefficient of X^0.
     * @return Returns a copy of the `basic::Rational` representing the coefficient.
     */
    basic::Rational operator[](unsigned int index) const;

    /**
     * @brief Evaluates the polynomial at a given rational point.
     *
     * @param r A constant reference to a `basic::Rational` representing the rational number at which to evaluate the polynomial.
     * @return Returns a `basic::Rational` representing the evaluated result of the polynomial at the given point.
     */
    basic::Rational operator()(basic::Rational const& r);

    Polynomial& operator*=(int scalar);
    Polynomial& operator*=(basic::Rational const& other);
    Polynomial& operator+=(Polynomial const& other);
    Polynomial& operator-=(Polynomial const& other);
    Polynomial operator-() const;
    Polynomial operator*(Polynomial const& other) const;
    
    int degree() const;

private:
    int degree_;
    basic::Rational* coefficients_;
};

Polynomial operator*(Polynomial const& p, int scalar);
Polynomial operator+(Polynomial const& lhp, Polynomial const& rhp);
Polynomial operator-(Polynomial const& lhp, Polynomial const& rhp);

Polynomial derive(Polynomial const& p);
double integrate(Polynomial const& p, double start, double end);

std::ostream& operator<<(std::ostream& os, const Polynomial& p);

}   // namespace algebra
