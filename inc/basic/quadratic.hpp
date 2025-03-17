#pragma once

#include <iostream>

namespace basic {

    struct Roots {
        double first;   // First root of the quadratic equation.
        double second;  // Second root of the quadratic equation.
    };

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
         * Parameterized constructor that initializes a Quadratic equation with given coefficients.
         * Allows for partial parameter specification by providing default values.
         *
         * @param a Coefficient for x^2. This coefficient must always be provided and cannot default
         *          to zero as it defines the quadratic nature of the equation.
         * @param b Coefficient for x. Defaults to 0.0 if not specified, allowing the equation
         *          to be effectively reduced to ax^2 + c when b is omitted.
         * @param c Constant term of the equation. Defaults to 0.0 if not specified, allowing the
         *          equation to be effectively reduced to ax^2 + bx when c is omitted.
         */
        Quadratic(double a, double b = 0.0, double c = 0.0);

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
        Quadratic& operator=(const Quadratic& other) = default;

        /**
         * Multiplies this Quadratic equation by a scalar and returns the resulting Quadratic.
         * This operation scales all coefficients (a, b, c) of the quadratic equation by the given scalar value.
         *
         * @param scalar The scalar value to multiply the equation's coefficients.
         * @return The new Quadratic equation resulting from the scalar multiplication.
         */
        Quadratic multiply_by_scalar(double scalar);

        /**
         * Finds the real roots of the quadratic equation and stores them in the provided Roots struct.
         * The function returns the number of real roots found (0, 1, or 2). Depending on the number of roots,
         * the roots struct is updated accordingly. If no real roots are found, both values in roots are set to -1.
         *
         * @param roots A reference to a Roots struct where the roots will be stored if found.
         * @return The number of real roots found (0, 1, or 2).
         */
        int find_roots(Roots& roots) const;
        
        /**
         * Calculates and returns the value of the quadratic equation at a given x value.
         * The equation used is: ax^2 + bx + c.
         *
         * @param x The x value at which the equation is evaluated.
         * @return The value of the quadratic equation at the specified x.
         */
        double value(double x) const; 

        /**
         * Prints the quadratic equation in a standard format aX^2 + bX + c to the standard output.
         * This function is useful for debugging purposes or when you need to display the equation.
         */
        void print() const;

        /**
         * Adds another Quadratic equation to this one and returns the resulting Quadratic.
         * This function performs element-wise addition of the coefficients from two Quadratic equations.
         *
         * @param other The other Quadratic equation to add to this one.
         * @return A new Quadratic object that is the result of the addition.
         */
        Quadratic add(Quadratic const& other);

        /**
         * Subtracts another Quadratic equation from this one and returns the resulting Quadratic.
         * This function performs element-wise subtraction of the coefficients from another Quadratic equation.
         *
         * @param other The other Quadratic equation to subtract from this one.
         * @return A new Quadratic object that is the result of the subtraction.
         */
        Quadratic subtract(Quadratic const& other);
    };

}  // namespace basic




// /**
        //  * Addition assignment operator for adding another Quadratic to this one.
        //  *
        //  * @param other Another Quadratic to add to this object.
        //  * @return Reference to the current object after addition.
        //  */
        // Quadratic& operator+=(const Quadratic& other);

        // /**
        //  * Subtraction assignment operator for subtracting another Quadratic from this one.
        //  *
        //  * @param other Another Quadratic to subtract from this object.
        //  * @return Reference to the current object after subtraction.
        //  */
        // Quadratic& operator-=(const Quadratic& other);

        //  /**
        //  * Multiplication operator to scale the Quadratic by a scalar value.
        //  *
        //  * @param scalar The double value to multiply all coefficients of this quadratic by.
        //  * @return A new Quadratic object that is the result of the multiplication.
        //  */
        // Quadratic operator*(double scalar) const;