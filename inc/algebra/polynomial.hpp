#pragma once

#include <iostream>
#include "basic/rational.hpp"

namespace algebra {

/**
 * @brief Class representing a polynomial.
 *
 * @details
 * Members:
 * - degree_: Represents the maximum degree the polynomial can have. This is the highest power of x for which the coefficient
 *   is non-zero.
 * - coefficients_: Pointer to an array of `basic::Rational` objects. Each element in this array represents the coefficient
 *   of the polynomial at a specific power of x. Specifically, `coefficients_[i]` is the coefficient of x^i.
 * 
 * @note The array `coefficients_` might contain additional slots for higher degrees that are currently zero.
 */
class Polynomial {
public:
    explicit Polynomial(int n_degree = 0);
    Polynomial(Polynomial const& other);
    ~Polynomial();
    Polynomial& operator=(Polynomial const& other);

   /**
     * @brief Constructs a Polynomial object that interpolates between two points using given rational coefficients.
     * 
     * This constructor initializes a Polynomial to interpolate between the rational points specified by the `start` 
     * and `end` pointers. The coefficients are taken from a sequence in memory starting at `start` and ending just before 
     * `end`, interpreting the sequence as coefficients from highest to lowest degree. It is assumed that the sequence
     * starts with the coefficient for the highest degree term (at `start`) and ends with the constant term (just before `end`).
     * 
     * @param start A pointer to a basic::Rational object representing the starting point of the polynomial's coefficients,
     *              corresponding to the highest degree.
     * @param end A pointer to a basic::Rational object representing the endpoint of the polynomial's coefficients,
     *            just past the lowest degree (constant term).
     * 
     * @note It is asserted that `start` must be less than or equal to `end`. If `start` is greater than `end`, the behavior
     *       is undefined, and an assertion will fail during runtime to prevent out-of-bounds access or other logical errors.
     */
    Polynomial(basic::Rational* start, basic::Rational* end);

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
     * @param r A constant reference to a Rational representing the rational number at which to evaluate the polynomial.
     * @return Returns a Rational representing the evaluated result of the polynomial at the given point.
     */
    basic::Rational operator()(basic::Rational r);

    /**
     * @brief Multiplies this polynomial by a scalar integer.
     *
     * @param scalar The scalar integer by which to multiply all coefficients of the polynomial.
     * @return A reference to this polynomial after scaling.
     */
    Polynomial& operator*=(int scalar);

    /**
     * @brief Multiplies this polynomial by a scalar Rational number.
     *
     * @param other A constant reference to a Rational number used as the scalar by which to multiply all coefficients of the polynomial.
     * @return A reference to this polynomial after scaling.
     */
    Polynomial& operator*=(basic::Rational other);

    /** @brief Adds another polynomial to this polynomial and updates the current instance.
     *
     * @param other A constant reference to another Polynomial whose coefficients are to be added to this polynomial.
     * @return A reference to this polynomial after adding the 'other' polynomial's coefficients.
     */
    Polynomial& operator+=(Polynomial const& other);

    /** 
     * @brief Subtracts another polynomial from this polynomial and updates the current instance.
     *
     * @param other A constant reference to another Polynomial whose coefficients are to be subtracted from
     *              this polynomial.
     * @return A reference to this polynomial after the 'other' polynomial's coefficients have
     *         been subtracted.
     */
    Polynomial& operator-=(Polynomial const& other);

    /**
     * @brief Negates this polynomial.
     *
     * @return A new Polynomial instance that represents the additive inverse of this polynomial, where
     *         each coefficient has been negated.
     */
    Polynomial operator-() const;
    
    /**
     * @brief Returns the degree of the polynomial.
     *
     * @return int The degree of the polynomial, determined by the highest non-zero coefficient. If all coefficients are zero,
     *         returns 0, representing the zero polynomial.
     */
    int degree() const;

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

private:
    void allocate_and_copy(Polynomial& polynom, basic::Rational* start, basic::Rational* end);

private:
    int degree_;
    basic::Rational* coefficients_;
};

/**
 * @brief Multiplies a polynomial by a scalar integer.
 *
 * @param polynom A constant reference to a Polynomial to be multiplied.
 * @param scalar An integer by which the polynomial is to be multiplied.
 * @return A new Polynomial instance that is the result of multiplying each coefficient of the polynomial 'p'
 *         by the integer 'scalar'.
 */
Polynomial operator*(Polynomial const& polynom, int scalar);

/**
 * @brief Adds two polynomials together.
 *
 * @param lhs A constant reference to the left-hand_side Polynomial to be added.
 * @param rhs A constant reference to the right-hand_side Polynomial to be added.
 * @return A new Polynomial instance that is the result of the addition of polynomial 'lhp' and 'rhp'.
 */
Polynomial operator+(Polynomial const& lhs, Polynomial const& rhs);

/**
 * @brief Subtracts one polynomial from another.
 *
 * @param lhs A constant reference to the left-hand_side Polynomial from which the right-hand Polynomial will be subtracted.
 * @param rhs A constant reference to the right-hand_side Polynomial to be subtracted from the left-hand Polynomial.
 * @return A new Polynomial instance that is the result of the subtraction of polynomial 'rhp' from 'lhp'.
 */
Polynomial operator-(Polynomial const& lhs, Polynomial const& rhs);

 /**
 * @brief Multiplies one polynomial by another.
 *
 * @param lhs A constant reference to the left-hand_side Polynomial.
 * @param rhs A constant reference to the right-hand_side Polynomial.
 * @return A new Polynomial instance that is the result of the multiplication of polynomial 'rhp' with 'lhp'
 */
Polynomial operator*(Polynomial const& lhs, Polynomial const& rhs); // TODO: make global

/**
 * @brief Calculates the derivative of a given polynomial.
 *
 * @param polynom A constant reference to the Polynomial whose derivative is to be calculated.
 * @return Polynomial A new Polynomial instance representing the derivative of 'p'.
 */
Polynomial derive(Polynomial const& polynom);

/**
 * @brief Computes the definite integral of a polynomial between two bounds.
 *
 * Calculates the integral of the polynomial 'p' from 'start' to 'end'. The integration is performed analytically,
 * and the result is the area under the polynomial curve between these two points. If 'end' is less than 'start',
 * the integral is computed as if the bounds were swapped and then multiplied by -1. If 'start' is equal to 'end',
 * the result is zero, reflecting the mathematical principle that the integral over a zero-width interval is zero.
 *
 * @param polynom A constant reference to the Polynomial to be integrated.
 * @param start The lower bound of the integration interval as a double.
 * @param end The upper bound of the integration interval as a double.
 * @return double The result of the integration, representing the area under the curve from 'start' to 'end'.
 *                Returns zero if 'start' equals 'end', or the integral with reversed bounds multiplied by -1
 *                if 'start' is greater than 'end'.
 */
double integrate(Polynomial const& polynom, double start, double end);

/**
 * @brief Inserts a textual representation of a polynomial into an output stream.
 *
 * Providing a human-readable format of the polynomial, typically expressed in terms of its coefficients 
 * and powers of x (e.g., 3x^2 + 2x + 1).
 *
 * @param os A reference to the std::ostream object where the polynomial will be inserted.
 * @param polynom A constant reference to the Polynomial object to be inserted into the stream.
 * @return A reference to the modified std::ostream object, allowing for chaining of insertion operations.
 */
std::ostream& operator<<(std::ostream& os, const Polynomial& polynom);

}   // namespace algebra
