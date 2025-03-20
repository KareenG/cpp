#include <cassert>
#include <cmath>

#include "algebra/polynomial.hpp"

namespace algebra {

Polynomial::Polynomial(int n_degree)
: degree_{n_degree}
, coefficients_{ new basic::Rational[n_degree + 1]{} }
{
    assert(n_degree >= 0);
}

Polynomial::Polynomial(basic::Rational* start, basic::Rational* end)
: coefficients_{nullptr}
{
    // assert first then do new
    allocate_and_copy(*this, start, end);
}

void Polynomial::allocate_and_copy(Polynomial& polynom, basic::Rational* start, basic::Rational* end) 
{
    assert(start != nullptr && end != nullptr && start <= end);
    polynom.degree_ = static_cast<int>(end - start - 1);
    assert(polynom.degree_ >= 0);
    polynom.coefficients_ = new basic::Rational[polynom.degree_ + 1];
    for (int i = 0; i <= polynom.degree_; ++i) {
        polynom.coefficients_[i] = start[polynom.degree_ - i];
    }
}

Polynomial::~Polynomial()
{
    delete[] coefficients_;
}

Polynomial::Polynomial(Polynomial const& other)
: degree_ {other.degree_}
, coefficients_{ new basic::Rational[other.degree_ + 1]{} }
{
    std::copy(other.coefficients_, other.coefficients_ + other.degree_ + 1, coefficients_);
}

Polynomial& Polynomial::operator=(Polynomial const& other)
{
    // If degree_ == other.degree_ no need to allocate, copy the coef's.
    if(degree_ == other.degree_) {
        for(int i = 0; i <= degree_; ++i) {
            coefficients_[i] = other.coefficients_[i];
        }
        return *this;
    }
    if(this != &other) {
        Polynomial temp(other);
        swap(temp);
    }
    return *this;
}

void Polynomial::swap(Polynomial& other)
{
    std::swap(degree_, other.degree_);
    std::swap(coefficients_, other.coefficients_);
}

std::ostream& Polynomial::print(std::ostream& os) const 
{
    basic::Rational zero{};
    if (degree_ == 0) {
        return (coefficients_[0] != zero) ? coefficients_[0].print(os) : os << "0";
    }
    if (coefficients_[degree_].value() < 0) {
        os << "-";
        (-coefficients_[degree_]).print(os);
    } else {
        coefficients_[degree_].print(os);
    }
    os << " X^" << degree_;
    for (int i = degree_ - 1; i >= 0; --i) {
        if (coefficients_[i] != zero) {
            os << (coefficients_[i].value() >= 0 ? " + " : " - ");
            (coefficients_[i].value() < 0 ? -coefficients_[i] : coefficients_[i]).print(os);
            if (i > 0) {
                os << " X" << (i > 1 ? "^" + std::to_string(i) : "");
            }
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& polynom)
{
    return polynom.print(os);
}

basic::Rational& Polynomial::operator[](unsigned int index)
{
    assert(static_cast<int>(index) <= degree_); // option 2: using AT func
    return coefficients_[index];
}

basic::Rational Polynomial::operator[](unsigned int index) const
{
    assert(static_cast<int>(index) <= degree_);
    return coefficients_[index];
}

basic::Rational Polynomial::operator()(basic::Rational r)
{
    basic::Rational result{coefficients_[0]};
    for(int i = 1; i <= degree_; ++i) {
        result += (coefficients_[i]) * r;
        r *= r;
    }
    return result;
}

int Polynomial::degree() const 
{
    basic::Rational zero{};
    for(int i = degree_; i >= 0; --i) {
        if(coefficients_[i] != zero) {
            return i;
        }
    }
    return 0;
}

Polynomial& Polynomial::operator*=(int scalar)
{
    basic::Rational r{scalar};
    for(int i = 0; i <= degree_; ++i) {
        coefficients_[i] *= r;
    }
    return *this;
}

Polynomial& Polynomial::operator*=(basic::Rational other) 
{ 
    for(int i = 0; i <= degree_; ++i) {
        coefficients_[i] *= other;
    }
    return *this;
}

Polynomial& Polynomial::operator+=(Polynomial const& other)
{
    int new_degree = std::max(degree_, other.degree_);
    if (new_degree > degree_) {
        basic::Rational *temp{ new basic::Rational[new_degree + 1]{} };
        for (int i = 0; i <= degree_; i++) {
            temp[i] = coefficients_[i];
        }
        delete[] coefficients_;
        coefficients_ = temp;
        degree_ = new_degree;
    }

    for (int i = 0; i <= other.degree_; i++) {
        coefficients_[i] += other.coefficients_[i];
    }
    return *this;
}

Polynomial& Polynomial::operator-=(Polynomial const& other)
{
    *this += -other;
    return *this;
}

Polynomial Polynomial::operator-() const
{
    Polynomial p{*this};
    p *= -1;
    return p;
}

Polynomial operator*(Polynomial const& lhs, Polynomial const& rhs) 
{
    int lhs_degree = lhs.degree();
    int rhs_defree = rhs.degree();
    Polynomial result(lhs_degree + rhs_defree);
    for (int i = 0; i <= lhs_degree; ++i) {
        for (int j = 0; j <= rhs_defree; ++j) {
            result[i + j] += lhs[i] * rhs[j];
        }
    }
    return result;
}

Polynomial operator*(Polynomial const& polynom, int scalar)
{
    Polynomial cpy_p{polynom};
    cpy_p *= scalar;
    return cpy_p;
}

Polynomial operator+(Polynomial const& lhs, Polynomial const& rhs)
{
    Polynomial polynom{lhs};
    polynom += rhs;
    return polynom;
}

Polynomial operator-(Polynomial const& lhs, Polynomial const& rhs)
{
    Polynomial polynom{lhs};
    polynom-= rhs;
    return polynom;
}

Polynomial derive(Polynomial const& polynom)
{
    unsigned int degree = static_cast<unsigned int>(polynom.degree());
    if(degree == 0) {
        return Polynomial(0);
    }
    Polynomial derived(degree - 1);
    for(unsigned int i = 1; i <= degree; ++i)
    {
        derived[i - 1] = polynom[i] * i;
    }
    return derived;
}

double integrate(Polynomial const& polynom, double start, double end) 
{
    if (end < start) {
        return -integrate(polynom, end, start);
    }
    unsigned int degree = static_cast<unsigned int>(polynom.degree());
    double result_end{};
    double result_start{};
    for (unsigned int i = 0; i <= degree; ++i) {
        // Convert Rational to double
        double coefficient = polynom[i].value();
        // 1/(i+1) for integration
        double factor = 1.0 / (i + 1);
        result_end += coefficient * factor * std::pow(end, i + 1);
        result_start += coefficient * factor * std::pow(start, i + 1);
    }
    // Apply Fundamental Theorem of Calculu
    return result_end - result_start;                                   
}

}   // namespace algebra