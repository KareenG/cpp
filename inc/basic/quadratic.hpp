#pragma once

#include <iostream>

namespace basic {

     /**
     * Represents a quadratic equation of the form ax^2 + bx + c.
     */
    struct Quadratic {
        double a;       // Coefficient of x^2
        double b;       // Coefficient of x
        double c;       // Constant term

        /**
         * Default constructor. Initializes the coefficients to zero.
         */
        Quadratic();

        /**
         * Parameterized constructor to set the coefficients of the quadratic equation.
         *
         * @param a Coefficient for x^2.
         * @param b Coefficient for x.
         * @param c Constant coefficient.
         */
        Quadratic(double a, double b, double c);

        /**
         * Copy constructor.
         *
         * @param other Another Quadratic object to copy data from.
         */
        Quadratic(const Quadratic& other);

        /**
         * Destructor.
         */
        ~Quadratic() = default;

        /**
         * Assignment operator.
         *
         * @param other Another Quadratic object to assign from.
         * @return Reference to the current object.
         */
        Quadratic& operator=(const Quadratic& other);

        /**
         * Addition assignment operator for adding another Quadratic to this one.
         *
         * @param other Another Quadratic to add to this object.
         * @return Reference to the current object after addition.
         */
        Quadratic& operator+=(const Quadratic& other);

        /**
         * Subtraction assignment operator for subtracting another Quadratic from this one.
         *
         * @param other Another Quadratic to subtract from this object.
         * @return Reference to the current object after subtraction.
         */
        Quadratic& operator-=(const Quadratic& other);

         /**
         * Multiplication operator to scale the Quadratic by a scalar value.
         *
         * @param scalar The double value to multiply all coefficients of this quadratic by.
         * @return A new Quadratic object that is the result of the multiplication.
         */
        Quadratic operator*(double scalar) const;

    };

    struct Roots {
        double first;   // First root of the quadratic equation.
        double second;  // Second root of the quadratic equation.
    };

    /**
     * Multiplies a Quadratic equation by a scalar and returns the resulting Quadratic.
     *
     * @param q The Quadratic to multiply.
     * @param scalar The scalar to multiply by.
     * @return The new Quadratic equation after multiplication.
     */
    Quadratic multiply_by_scalar(const Quadratic& q, double scalar);

    /**
     * Finds the roots of the quadratic equation.
     *
     * @param q The Quadratic equation to find roots for.
     * @param roots A Roots struct where the roots will be stored.
     * @return The number of real roots found (0, 1, or 2).
     * @note if no root is found then the roots will be -1, -1
     *       if one root is found then roots.first will have the root and roots.second will be -1
     *       if two roots are found then both members will have the roots. 
     */
    int find_roots(const Quadratic& q, Roots& roots);

     /**
     * Calculates the value of the quadratic equation at a given x value.
     *
     * @param q The Quadratic equation.
     * @param x The x value at which to evaluate the equation.
     * @return The value of the quadratic equation at the specified x.
     */
    double value(const Quadratic& q, double x);

     /**
     * Prints the quadratic equation in the form of ax^2 + bx + c to the standard output.
     *
     * @param q The Quadratic equation to print.
     */
    void print(const Quadratic& q);

}  // namespace basic
