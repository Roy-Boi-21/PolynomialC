//
// Created by roybo on 9/3/2024.
//

#include "PolynomialC.h"

// ===== HELPER FUNCTIONS =====

double factorial(int x) {
    double result = 1;

    for (int i = 1; i <= x; i++) {
        result *= i;
    }

    return result;
}

void remove_top_zero_terms(vector<double>& coefficient_list) {
    // If the constants for the upper terms are 0, they are dropped from the constant list.
    while (coefficient_list[coefficient_list.size() - 1] == 0) {
        coefficient_list.erase(coefficient_list.end() - 1);
    }
}





// ===== CONSTRUCTORS =====

/* Default Constructor
 *
 * The default constructor creates a polynomial with a constant of 0.
 */
Polynomial::Polynomial() {
    coefficient_list = {0};
}


/* List Constructor
 *
 * The list constructor takes a list of numbers and uses those as the constants for the polynomial.
 */
Polynomial::Polynomial(vector<double> set_coefficient_list) {
    remove_top_zero_terms(set_coefficient_list);
    coefficient_list = set_coefficient_list;
}


/* Keyword Constructor
 *
 * The keyword constructor creates special sequences of polynomials that are meant to represent
 * non-polynomial functions such as sine(x) and e^x.
 *
 * Parameters: A keyword for a specific non-polynomial function.  (String)
 * - "sine" or "sin": Creates a polynomial that is a representation for sine.
 * - "cosine" or "cos": Creates a polynomial that is a representation for cosine.
 * - "euler", "e^x", or "e": Creates a polynomial that is a representation for e^x.
 * Precision: The amount of terms to be used for the preciseness of the function.  (Integer)  [Optional]
 */
Polynomial::Polynomial(const string& keyword, int precision=40) {
    bool negative = false;
    double value = 0;

    if (keyword == "sine" || keyword == "sin") {
        for (int i = 0; i < precision; i++) {
            if (i % 2 == 1) {
                value = 1.0f / factorial(i);
                if (negative) {
                    value *= -1;
                }
                coefficient_list.push_back(value);
                negative = !negative;
            } else {
                coefficient_list.push_back(0);
            }
        }
    } else if (keyword == "cosine" || keyword == "cos") {
        for (int i = 0; i < precision; i++) {
            if (i % 2 == 0) {
                value = 1.0f / factorial(i);
                if (negative) {
                    value *= -1;
                }
                coefficient_list.push_back(value);
                negative = !negative;
            } else {
                coefficient_list.push_back(0);
            }
        }
    } else if (keyword == "euler" || keyword == "e^x" || keyword == "e") {
        for (int i = 0; i < precision; i++) {
            value = 1.0f / factorial(i);
            coefficient_list.push_back(value);
        }
    } else {
        throw invalid_argument(keyword + " is not a valid keyword.");
    }
}





// ===== CLASS GETTERS & SETTERS =====


/* Get coefficients
 *
 * Returns the coefficient list for this polynomial as a vector of doubles.
 *
 * Parameters: None.
 * Returns: The list of coefficients for the polynomial.  (Vector of doubles)
 */
vector<double> Polynomial::get_coefficients() {
    return coefficient_list;
}


/* Set coefficients
 *
 * Sets a new coefficient list for this polynomial.
 *
 * Parameters: The new list of coefficients to replace the current coefficient list.  (Vector of doubles)
 * Returns: None.
 */
void Polynomial::set_coefficients(vector<double> new_coefficients) {
    coefficient_list = new_coefficients;
}



// ===== CLASS FUNCTIONS =====


/* Solve
 *
 * The solve function takes an input for x and solves the polynomial using the value for x.
 *
 * Parameters: The value for x used to solve the polynomial.  (Double)
 * Returns: The value of the polynomial.  (Long Long)
 */
long long Polynomial::solve(double x) {
    long long result = 0;
    for (int i = 0; i < coefficient_list.size(); i++) {
        result += (coefficient_list[i] * pow(x, i));
    }
    return result;
}


/* Differentiate
 *
 * The differentiate function creates a new polynomial that is a derivative of the current polynomial.
 *
 * Parameters: None.
 * Returns: The derivative of the current polynomial.  (Polynomial)
 */
Polynomial Polynomial::differentiate() {
    vector<double> diff_coefficient_list;
    for (int i = 1; i < coefficient_list.size(); i++) {
        diff_coefficient_list.push_back(coefficient_list[i] * i);
    }

    Polynomial derivative(diff_coefficient_list);
    return derivative;
}


/* Integrate
 *
 * The integrate function creates a new polynomial which is an integral of the old with respect to x.
 *
 * Parameters: The constant value of C.  (Double)
 * Returns: The integral of the current polynomial.  (Polynomial)
 */
Polynomial Polynomial::integrate(double c) {
    vector<double> int_coefficient_list = {c};
    for (int i = 0; i < coefficient_list.size(); i++) {
        int_coefficient_list.push_back(coefficient_list[i] / (i + 1));
    }

    remove_top_zero_terms(int_coefficient_list);

    Polynomial integral(int_coefficient_list);
    return integral;
}


/* Power
 *
 * The power function raises the entire polynomial to a power.
 *
 * Parameters: The power to raise the polynomial.  (Unsigned Integer)
 * Returns: The raised polynomial.  (Polynomial)
 */
Polynomial Polynomial::power(unsigned int x) {
    if (x == 0) {
        vector<double> null_coefficient = {1};
        Polynomial null_polynomial(null_coefficient);
        return null_polynomial;
    }

    Polynomial self(coefficient_list);
    auto duplicate = self;

    for (int i = 0; i < (x - 1); i++) {
        self *= duplicate;
    }

    return self;
}


/* Display
 *
 * The display function displays the polynomial in a more human-friendly format.
 *
 * Parameters: A keyword for how the terms should be displayed.  (String)
 * - all: Display all terms from ascending order, even those with 0 as their coefficient.
 * - reduced: Display all terms from ascending order excluding those with 0 as their coefficient.
 * Returns: None.
 */
void Polynomial::display(const string& keyword) {
    if (!coefficient_list.empty()) {
        for (int i = 0; i < coefficient_list.size(); i++) {
            // If the user wants to see a reduced representation of the polynomial, all terms with
            // 0 as their coefficient will be hidden.
            if (coefficient_list[i] == 0 && keyword == "reduced") {
                continue;
            }

            cout << "(" << coefficient_list[i] << " * x^" << i << ")";

            if (i != coefficient_list.size() - 1) {
                if (coefficient_list[i] != 0 || keyword != "reduced") {
                    cout << " + ";
                }
            }
        }
    } else {
        cout << "There are no terms in this polynomial.";
    }
    cout << endl;
}





// ===== CLASS INTERACTIONS WITH OTHER POLYNOMIALS =====


/* Polynomial + Polynomial operator
 *
 * The sum of two polynomials will result in a polynomial with the sum of the constants in both
 * polynomials.
 *
 * Parameters: Another polynomial.  (Polynomial)
 * Returns: The summed-up polynomial.  (Polynomial)
 */
Polynomial Polynomial::operator+(const Polynomial &other) {
    auto new_coefficient_list = coefficient_list;
    int constant_count = new_coefficient_list.size();
    int other_constant_count = other.coefficient_list.size();

    // If the other polynomial has more terms than the current polynomial, empty terms are added to
    // the polynomial.
    if (constant_count < other_constant_count) {
        for (int i = other_constant_count - constant_count + 1; i < other_constant_count; i++) {
            new_coefficient_list.push_back(0);
        }
    }

    // The constants from the other polynomial is added to the current polynomial.
    for (int i = 0; i < new_coefficient_list.size(); i++) {
        new_coefficient_list[i] += other.coefficient_list[i];
    }

    // If the constants for the upper terms are 0, they are dropped from the constant list.
    remove_top_zero_terms(new_coefficient_list);

    Polynomial new_polynomial(new_coefficient_list);
    return new_polynomial;
}

void Polynomial::operator+=(const Polynomial &other) {
    int constant_count = coefficient_list.size();
    int other_constant_count = other.coefficient_list.size();

    // If the other polynomial has more terms than the current polynomial, empty terms are added to
    // the polynomial.
    if (constant_count < other_constant_count) {
        for (int i = other_constant_count - constant_count + 1; i < other_constant_count; i++) {
            coefficient_list.push_back(0);
        }
    }

    // The constants from the other polynomial is added to the current polynomial.
    for (int i = 0; i < coefficient_list.size(); i++) {
        coefficient_list[i] += other.coefficient_list[i];
    }

    // If the constants for the upper terms are 0, they are dropped from the constant list.
    remove_top_zero_terms(coefficient_list);
}


/* Polynomial - Polynomial operator
 *
 * The difference of two polynomials will result in a polynomial with the difference of the constants
 * in both polynomials.
 *
 * Parameters: Another polynomial.  (Polynomial)
 * Returns: The subtracted polynomial.  (Polynomial)
 */
Polynomial Polynomial::operator-(const Polynomial &other) {
    auto new_coefficient_list = coefficient_list;
    int constant_count = new_coefficient_list.size();
    int other_constant_count = other.coefficient_list.size();

    // If the other polynomial has more terms than the current polynomial, empty terms are added to
    // the polynomial.
    if (constant_count < other_constant_count) {
        for (int i = other_constant_count - constant_count + 1; i < other_constant_count; i++) {
            new_coefficient_list.push_back(0);
        }
    }

    // The constants from the other polynomial is added to the current polynomial.
    for (int i = 0; i < new_coefficient_list.size(); i++) {
        new_coefficient_list[i] -= other.coefficient_list[i];
    }

    // If the constants for the upper terms are 0, they are dropped from the constant list.
    remove_top_zero_terms(new_coefficient_list);

    Polynomial new_polynomial(new_coefficient_list);
    return new_polynomial;
}

void Polynomial::operator-=(const Polynomial &other) {
    int constant_count = coefficient_list.size();
    int other_constant_count = other.coefficient_list.size();

    // If the other polynomial has more terms than the current polynomial, empty terms are added to
    // the polynomial.
    if (constant_count < other_constant_count) {
        for (int i = other_constant_count - constant_count + 1; i < other_constant_count; i++) {
            coefficient_list.push_back(0);
        }
    }

    // The constants from the other polynomial is added to the current polynomial.
    for (int i = 0; i < coefficient_list.size(); i++) {
        coefficient_list[i] -= other.coefficient_list[i];
    }

    // If the constants for the upper terms are 0, they are dropped from the constant list.
    remove_top_zero_terms(coefficient_list);
}


/* Polynomial * Polynomial Operator
 *
 * The product of two polynomials will result in a polynomial with more powers of x than the individual
 * two polynomials.
 *
 * Parameters: Another polynomial.  (Polynomial)
 * Returns: The product of the two polynomials.  (Polynomial)
 */
Polynomial Polynomial::operator*(const Polynomial& other) {
    // Space is allocated for the new polynomial.
    vector<double> new_coefficient_list;
    int new_size = coefficient_list.size() + other.coefficient_list.size() - 1;
    new_coefficient_list.reserve(new_size);
    for (int i = 0; i < new_size; i++) {
        new_coefficient_list.push_back(0);
    }

    // The content from the other polynomials is multiplied to the new polynomial.
    for (int i = 0; i < coefficient_list.size(); i++) {
        for (int j = 0; j < other.coefficient_list.size(); j++) {
            new_coefficient_list[i + j] += (coefficient_list[i] * other.coefficient_list[j]);
        }
    }

    // The polynomial is created and returned.
    Polynomial new_polynomial(new_coefficient_list);
    return new_polynomial;
}

void Polynomial::operator*=(const Polynomial& other) {
    // Space is allocated for the new polynomial.
    vector<double> temp;
    int new_size = coefficient_list.size() + other.coefficient_list.size() - 1;
    temp.reserve(new_size);
    for (int i = 0; i < new_size; i++) {
        temp.push_back(0);
    }

    // The content from the other polynomials is multiplied to the new polynomial.
    for (int i = 0; i < coefficient_list.size(); i++) {
        for (int j = 0; j < other.coefficient_list.size(); j++) {
            temp[i + j] += (coefficient_list[i] * other.coefficient_list[j]);
        }
    }

    // The old coefficient list is overwritten by the new coefficient list.
    coefficient_list = temp;
}


/* Polynomial Copy Operator
 *
 * When a polynomial is copied to another polynomial, the constant list is transferred from the old
 * polynomial to the new polynomial.
 *
 * Parameters: Another polynomial.  (Polynomial)
 * Returns: The parameter polynomial.  (Polynomial)
 */
Polynomial& Polynomial::operator=(const Polynomial& other) {
    coefficient_list = other.coefficient_list;
    return *this;
}





// ===== CLASS INTERACTIONS WITH NON-POLYNOMIAL OBJECTS =====


/* Polynomial + Constant Operation
 *
 * When a constant is added to a polynomial, the constant is added to the 0th power of the polynomial.
 *
 * Parameters: The constant to add.  (Float)
 * Returns: A new polynomial with an added constant.  (Polynomial)
 */
Polynomial Polynomial::operator+(const float x) {
    auto new_coefficient_list = coefficient_list;
    if (new_coefficient_list.empty()) {
        new_coefficient_list.push_back(x);
    } else {
        new_coefficient_list[0] += x;
    }
    Polynomial new_polynomial(new_coefficient_list);
    return new_polynomial;
}

void Polynomial::operator+=(const float x) {
    if (coefficient_list.empty()) {
        coefficient_list.push_back(x);
    } else {
        coefficient_list[0] += x;
    }
}


/* Polynomial - Constant Operation
 *
 * When a constant is subtracted to a polynomial, the constant is subtracted from the 0th power of
 * the polynomial.
 *
 * Parameters: The constant to add.  (Float)
 * Returns: A new polynomial with an added constant.  (Polynomial)
 */
Polynomial Polynomial::operator-(const float x) {
    auto new_coefficient_list = coefficient_list;
    if (new_coefficient_list.empty()) {
        new_coefficient_list.push_back(-x);
    } else {
        new_coefficient_list[0] -= x;
    }
    Polynomial new_polynomial(new_coefficient_list);
    return new_polynomial;
}

void Polynomial::operator-=(const float x) {
    if (coefficient_list.empty()) {
        coefficient_list.push_back(-x);
    } else {
        coefficient_list[0] -= x;
    }
}


/* Polynomial * Constant Operation
 *
 * When a polynomial is multiplied by a constant, every constant in the polynomial is multiplied
 * by the magnitude of the constant.
 *
 * Parameters: The multiplicative constant.  (Float)
 * Returns: A new polynomial increased by the magnitude of the constant.
 */
Polynomial Polynomial::operator*(const float x) {
    auto new_coefficient_list = coefficient_list;
    for (auto& constant : new_coefficient_list) {
        constant *= x;
    }
    Polynomial new_polynomial(new_coefficient_list);
    return new_polynomial;
}

void Polynomial::operator*=(const float x) {
    for (auto& constant : coefficient_list) {
        constant *= x;
    }
}


/* Polynomial / Constant Operation
 *
 * When a polynomial is divided by a constant, every constant in the polynomial is divided
 * by the magnitude of the constant.
 *
 * Parameters: The divisor constant.  (Float)
 * Returns: A new polynomial decreased by the magnitude of the constant.
 */
Polynomial Polynomial::operator/(const float x) {
    auto new_coefficient_list = coefficient_list;
    for (auto& constant : new_coefficient_list) {
        constant /= x;
    }
    Polynomial new_polynomial(new_coefficient_list);
    return new_polynomial;
}

void Polynomial::operator/=(const float x) {
    for (auto& constant : coefficient_list) {
        constant /= x;
    }
}





// ===== MISCELLANEOUS OPERATIONS =====


/* Square Bracket Operator
 *
 * The square bracket operator returns the coefficient at a given power of x.
 *
 * Parameters: The ith power of x.  (Integer)
 * Returns: The coefficient at the specified ith power of x.  (Double)
 */
double Polynomial::operator[](int i) {
    return coefficient_list[i];
}


/* Parentheses Operator
 *
 * The parentheses operator solves the polynomial given a number x.
 *
 * Parameters: The input number, x.  (Double)
 * Returns: The result of the polynomial.  (Long Long)
 */
long long Polynomial::operator()(double x) {
    return solve(x);
}
