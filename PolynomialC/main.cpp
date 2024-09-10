#include <iostream>
#include "PolynomialC.h"

int main() {
    // PolynomialC Demonstration
    cout << "PolynomialC Demonstration" << endl;

    // A polynomial is created that will only produce odd values.  (2x + 1)
    Polynomial odd({1, 2}, 0);
    cout << "What is " << odd << " if x = 6?" << endl;
    cout << odd(6) << endl << endl;

    Polynomial quadratic({1, 2, 1}, 0);
    cout << "What is " << quadratic << " if x = -1?" << endl;
    cout << quadratic.solve(-1) << endl << endl;

    Polynomial poly_a({3, 1}, 0);
    Polynomial poly_b({5, 2}, 0);
    cout << "What is the product of (" << poly_a << ") and (" << poly_b << ")?" << endl;
    poly_a *= poly_b;
    cout << poly_a << endl;
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
