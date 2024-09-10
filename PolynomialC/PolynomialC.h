//
// Created by Roy Boi 21 on 9/3/2024.
//

#ifndef POLYNOMIALC_POLYNOMIALC_H
#define POLYNOMIALC_POLYNOMIALC_H

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Polynomial {
    // The Polynomial's coefficient list is a series of x's raised to the power of the ith element.
    // A coefficient list of [1, 2, 3] would equal (1 * x^0) + (2 * x^1) + (3 * x^2) = 3x^2 + 2x + 1.
    vector<double> coefficient_list;
    double a;
    string keyword;

public:
    // Class Constructors
    Polynomial();
    Polynomial(vector<double> set_coefficient_list, double set_a);
    explicit Polynomial(const string& keyword);

    // Class Getters & Setters
    vector<double> get_coefficients() const;
    void set_coefficients(vector<double> new_coefficients);
    double get_a() const;
    void set_a(double new_a);

    // Class Functions
    long double solve(double x) const;
    Polynomial differentiate();
    Polynomial integrate(double c=0);
    Polynomial power(unsigned int x);
    void display(const string& keyword="all") const;

    // Class Interactions with other polynomials
    Polynomial operator+(const Polynomial& other);
    void operator+=(const Polynomial& other);
    Polynomial operator-(const Polynomial& other);
    void operator-=(const Polynomial& other);
    Polynomial operator*(const Polynomial& other);
    void operator*=(const Polynomial& other);
    Polynomial& operator=(const Polynomial& other);

    // Class Interactions with other data types
    Polynomial operator+(float x);
    void operator+=(float x);
    Polynomial operator-(float x);
    void operator-=(float x);
    Polynomial operator*(float x);
    void operator*=(float x);
    Polynomial operator/(float x);
    void operator/=(float x);

    // Miscellaneous Operations
    double operator[](int i) const;
    long double operator()(double x) const;
    friend ostream& operator<<(ostream& out, const Polynomial& obj);
};


#endif //POLYNOMIALC_POLYNOMIALC_H
