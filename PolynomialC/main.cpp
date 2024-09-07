#include <iostream>
#include "PolynomialC.h"

int main() {
    // PolynomialC Intro splash text
    cout << "Thank you for using PolynomialC!" << endl;
    cout << "Created by Roy Boi 21." << endl;
    cout << endl;
    cout << "This is a open-source class designed to make Calculus easier to implement in C++." << endl;
    cout << "PolynomialC's polynomials can do the following." << endl;
    cout << "- ALGEBRA" << endl;
    cout << "--- Addition with constants and other polynomials." << endl;
    cout << "--- Subtraction with constants and other polynomials." << endl;
    cout << "--- Multiplication with constants and other polynomials." << endl;
    cout << "--- Division with constants." << endl;
    cout << "--- Raise polynomials to powers of constants." << endl;
    cout << "--- Solve the polynomial and return one number." << endl;
    cout << "- CALCULUS" << endl;
    cout << "--- Integrate polynomials with respect to x." << endl;
    cout << "--- Differentiate polynomials with respect to x." << endl;
    cout << "--- Approximate values for sine, cosine, e^x, and ln(x) with 1000 terms." << endl;
    cout << "----- The ln(x) function may produce inaccurate values with added with other " << endl;
    cout << "----- non-logarithmic polynomials." << endl;
    cout << "----- I must emphasize, these are approximations.  Inaccurate results may be" << endl;
    cout << "----- produced for high values of x." << endl;
    cout << endl;
    cout << "This class is available for all to use.  I only ask for credit if you use this" << endl;
    cout << "code." << endl;
    cout << endl;


    // PolynomialC Demonstration
    cout << "PolynomialC Demonstration" << endl;

    // A polynomial is created that will only produce odd values.  (2x + 1)
    Polynomial odd({1, 2}, 0);
    odd.display();
    cout << "What is 2x + 1 if x = 6?" << endl;
    cout << odd(6) << endl << endl;

    Polynomial quadratic({1, 2, 1}, 0);
    quadratic.display();
    cout << "What is x^2 + 2x + 1 if x = -1?" << endl;
    cout << quadratic.solve(-1) << endl << endl;

    Polynomial poly_a({3, 1}, 0);
    Polynomial poly_b({5, 2}, 0);
    poly_a.display();
    poly_b.display();
    cout << "What is the product of (x + 3) * (2x + 5)?" << endl;
    poly_a *= poly_b;
    poly_a.display();
    cout << endl;

    double pi = 3.14159265359;
    double e = 2.71828182846;

    Polynomial sine("sine");
    Polynomial cosine("cosine");
    cout << "What is the value of sin(pi/3) and cos(pi/3)?" << endl;
    cout << sine(pi / 3.0) << endl;
    cout << cosine(pi / 3.0) << endl;
    cout << "What is the value of (sin(e))^2 + (cos(e))^2?" << endl;
    sine = sine.power(2);
    cosine = cosine.power(2);
    cout << sine(e) + cosine(e) << endl << endl;

    Polynomial ln("ln");
    cout << "What is the value of ln(e^5)?" << endl;
    cout << ln(e * e * e * e * e) << endl;

    return 0;
}
