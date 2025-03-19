#include "algebra/polynomial.hpp"
#include <cassert>
#include <cmath>

namespace algebra {

Polynomial::Polynomial(int n_degree)
: degree_ {n_degree}
, coefficients_{ new basic::Rational[n_degree + 1]{} }
{
    assert(n_degree >= 0);
}

Polynomial::Polynomial(basic::Rational* start, basic::Rational* end)
: degree_ {static_cast<int>(end - start - 1)}
, coefficients_{ new basic::Rational[degree_ + 1]{} }
{
    assert(degree_ >= 0);
    for(int i = 0; i <= degree_; ++i) {
        coefficients_[i] = start[degree_ - i];
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

std::ostream& Polynomial::print(std::ostream& os) const {
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
            if (i > 0) os << " X" << (i > 1 ? "^" + std::to_string(i) : "");
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p)
{
    return p.print(os);
}

basic::Rational& Polynomial::operator[](unsigned int index)
{
    assert(static_cast<int>(index) <= degree_);
    return coefficients_[index];
}

basic::Rational Polynomial::operator[](unsigned int index) const
{
    basic::Rational r_cpy{coefficients_[index]};
    assert(static_cast<int>(index) <= degree_);
    return r_cpy;
}

basic::Rational Polynomial::operator()(basic::Rational const& r)
{
    basic::Rational result{}; 
    for(int i = 0; i <= degree_; ++i) {
        result += (coefficients_[i]) * (r ^ i);
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

Polynomial& Polynomial::operator*=(basic::Rational const& other) 
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
    Polynomial temp = -other;
    return (*this) += temp;
}

Polynomial Polynomial::operator-() const
{
    basic::Rational r{-1};
    Polynomial p{*this};
    for(int i = 0; i < degree_ + 1; ++i) {
        p.coefficients_[i] *= r;
    }
    return p;
}

Polynomial Polynomial::operator*(Polynomial const& other) const {
    Polynomial result(degree_ + other.degree_);
    for (int i = 0; i <= degree_; ++i) {
        for (int j = 0; j <= other.degree_; ++j) {
            result.coefficients_[i + j] += coefficients_[i] * other.coefficients_[j];
        }
    }
    return result;
}

Polynomial operator*(Polynomial const& p, int scalar)
{
    Polynomial cpy_p{p};
    cpy_p *= scalar;
    return cpy_p;
}

Polynomial operator+(Polynomial const& lhp, Polynomial const& rhp)
{
    Polynomial p{lhp};
    p += rhp;
    return p;
}

Polynomial operator-(Polynomial const& lhp, Polynomial const& rhp)
{
    Polynomial p{lhp};
    p -= rhp;
    return p;
}

Polynomial derive(Polynomial const& p)
{
    unsigned int degree = static_cast<unsigned int>(p.degree());
    if(degree == 0) {
        return Polynomial(0);
    }
    Polynomial derived(degree - 1);
    for(unsigned int i = 1; i <= degree; ++i)
    {
        derived[i - 1] = p[i] * i;
    }
    return derived;
}

double integrate(Polynomial const& p, double start, double end) 
{
    assert(end >= start);
    unsigned int degree = static_cast<unsigned int>(p.degree());
    double result_end{};
    double result_start{};
    for (unsigned int i = 0; i <= degree; ++i) {
        // Convert Rational to double
        double coefficient = p[i].value();
        // 1/(i+1) for integration
        double factor = 1.0 / (i + 1);
        result_end += coefficient * factor * std::pow(end, i + 1);
        result_start += coefficient * factor * std::pow(start, i + 1);
    }
    // Apply Fundamental Theorem of Calculu
    return result_end - result_start;                                   
}

}   // namespace algebra