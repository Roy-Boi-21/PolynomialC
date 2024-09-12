//
// Created by Roy Boi 21 on 9/3/2024.
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

void Polynomial::hidden_display(const string& set_keyword) const {
    if (!coefficient_list.empty()) {
        if (set_keyword != "simple") {
            for (int i = 0; i < coefficient_list.size(); i++) {
                // If the user wants to see a reduced representation of the polynomial, all terms with
                // 0 as their coefficient will be hidden.
                if (coefficient_list[i] == 0 && set_keyword == "reduced") {
                    continue;
                }

                if (a == 0) {
                    cout << "(" << coefficient_list[i] << " * x^" << i << ")";
                } else if (a > 0) {
                    cout << "(" << coefficient_list[i] << " * (x - " << a << ")^" << i << ")";
                } else {
                    cout << "(" << coefficient_list[i] << " * (x + " << a * -1 << ")^" << i << ")";
                }


                if (check_ahead(i) || set_keyword != "reduced") {
                    cout << " + ";
                }

            }
        } else {
            for (int i = coefficient_list.size() - 1; i >= 0; i--) {
                // All 0 terms will be hidden in a simple display.
                if (coefficient_list[i] == 0) {
                    continue;
                }

                // If the coefficient is an integer, then it will be appended next to x instead of
                // being displayed as multiplied by x.
                if (floor(coefficient_list[i]) == ceil(coefficient_list[i])) {
                    if (coefficient_list[i] != 1 || i == 0) {
                        cout << coefficient_list[i];
                    }
                    if (i > 0) {
                        if (a == 0) {
                            cout << "x";
                        } else if (a > 0) {
                            cout << "(x - " << a << ")";
                        } else {
                            cout << "(x + " << a * -1 << ")";
                        }
                    }
                    if (i > 1) {
                        cout << "^" << i;
                    }
                } else {
                    if (coefficient_list[i] != 1 || i == 0) {
                        cout << "(" << coefficient_list[i] << ")";
                    }
                    if (i > 0) {
                        if (a == 0) {
                            cout << " * x";
                        } else if (a > 0) {
                            cout << " * (x - " << a << ")";
                        } else {
                            cout << " * (x + " << a * -1 << ")";
                        }
                    }
                    if (i > 1) {
                        cout << "^" << i;
                    }
                }

                if (check_behind(i)) {
                    cout << " + ";
                }
            }
        }
    } else {
        cout << "There are no terms in this polynomial.";
    }
}

bool Polynomial::check_behind(int index) const {
    // This function checks if there is a lesser term of the polynomial before the current one.
    for (int i = index - 1; i >= 0; i--) {
        if (coefficient_list[i] != 0) {
            return true;
        }
    }
    return false;
}

bool Polynomial::check_ahead(int index) const {
    // This function checks if there is a greater term of the polynomial before the current one.
    for (int i = index; i < coefficient_list.size() - 1; i++) {
        if (coefficient_list[i] != 0) {
            return true;
        }
    }
    return false;
}


// ===== CONSTRUCTORS =====

/* Default Constructor
 *
 * The default constructor creates a polynomial with a constant of 0.
 */
Polynomial::Polynomial() {
    coefficient_list = {0};
    a = 0;
    keyword = "";
}


/* List Constructor
 *
 * The list constructor takes a list of numbers and uses those as the constants for the polynomial.
 */
Polynomial::Polynomial(vector<double> set_coefficient_list, double set_a=0) {
    remove_top_zero_terms(set_coefficient_list);
    coefficient_list = set_coefficient_list;
    a = set_a;
    keyword = "";
}


/* Keyword Constructor
 *
 * The keyword constructor creates special sequences of polynomials that are meant to represent
 * non-polynomial functions such as sine(x) and e^x.  These approximations are accurate to 100 terms.
 *
 * Parameters: A keyword for a specific non-polynomial function.  (String)
 * - "sine" or "sin": Creates a polynomial that is a representation for sine.
 * - "cosine" or "cos": Creates a polynomial that is a representation for cosine.
 * - "euler", "e^x", or "e": Creates a polynomial that is a representation for e^x.
 * - "ln", "lnx", "log", or "logx": Creates a polynomial that is a representation for ln(x).
 */
Polynomial::Polynomial(const string& keyword) {
    bool negative = false;
    double value = 0;
    int precision = 1000;
    a = 0;

    if (keyword == "sine" || keyword == "sin") {
        this->keyword = "sine";
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
        this->keyword = "cosine";
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
        this->keyword = "euler";
        for (int i = 0; i < precision; i++) {
            value = 1.0f / factorial(i);
            coefficient_list.push_back(value);
        }
    } else if (keyword == "ln" || keyword == "lnx" || keyword == "log" || keyword == "logx") {
        this->keyword = "ln";
        coefficient_list.push_back(0);
        a = 1;
        for (int i = 1; i < precision; i++) {
            value = 1.0f / float(i);
            if (negative) {
                value *= -1;
            }
            coefficient_list.push_back(value);
            negative = !negative;
        }
    } else {
        throw invalid_argument(keyword + " is not a valid keyword.");
    }
    remove_top_zero_terms(coefficient_list);
}





// ===== CLASS GETTERS & SETTERS =====


/* Get coefficients
 *
 * Returns the coefficient list for this polynomial as a vector of doubles.
 *
 * Parameters: None.
 * Returns: The list of coefficients for the polynomial.  (Vector of doubles)
 */
vector<double> Polynomial::get_coefficients() const {
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


/* Get a
 *
 * Returns the coefficient of a for the polynomial.  [c * (x - a)^b]
 *
 * Parameters: None
 * Returns: The current value of a.  (Double)
 */
double Polynomial::get_a() const {
    return a;
}


/* Set a
 *
 * Sets the coefficient of a of the polynomial to something else.  [c * (x - a)^b]
 *
 * Parameters: The new value of a to replace the old.  (Double)
 * Returns: None.
 */
void Polynomial::set_a(double new_a) {
    a = new_a;
}


// ===== CLASS FUNCTIONS =====


/* Solve
 *
 * The solve function takes an input for x and solves the polynomial using the value for x.
 *
 * Parameters: The value for x used to solve the polynomial.  (Double)
 * Returns: The value of the polynomial.  (Long Double)
 */
long double Polynomial::solve(double x) const {
    long double result = 0;
    for (int i = 0; i < coefficient_list.size(); i++) {
        if (keyword == "ln" && x > 2) {
            result -= (coefficient_list[i] * pow((1.0 / x) - a, i));
        } else {
            result += (coefficient_list[i] * pow(x - a, i));
        }
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
 * - simple: Display all terms from descending order as orderly as possible.
 * Returns: None.
 */
void Polynomial::display(const string& set_keyword) const {
    hidden_display(set_keyword);
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
    // The function checks if the two polynomials could be added together.  If not, an error is raised.
    if (a != other.a) {
        cerr << "[PolynomialC/ERROR]" << endl <<
                "These two polynomials have different values of 'a'." << endl <<
                "Current polynomial value of a: " << a << endl <<
                "Other polynomial value of a: " << other.a << endl <<
                "Adding these two polynomials together would result in a mathematically" << endl <<
                "incorrect polynomial." << endl;
        throw invalid_argument("Polynomial a mismatch.");
    }

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
    // The function checks if the two polynomials could be added together.  If not, an error is raised.
    if (a != other.a) {
        cerr << "[PolynomialC/ERROR]" << endl <<
             "These two polynomials have different values of 'a'." << endl <<
             "Current polynomial value of a: " << a << endl <<
             "Other polynomial value of a: " << other.a << endl <<
             "Adding these two polynomials together would result in a mathematically" << endl <<
             "incorrect polynomial." << endl;
        throw invalid_argument("Polynomial a mismatch.");
    }

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
    // The function checks if the two polynomials could be subtracted.  If not, an error is raised.
    if (a != other.a) {
        cerr << "[PolynomialC/ERROR]" << endl <<
             "These two polynomials have different values of 'a'." << endl <<
             "Current polynomial value of a: " << a << endl <<
             "Other polynomial value of a: " << other.a << endl <<
             "Adding these two polynomials together would result in a mathematically" << endl <<
             "incorrect polynomial." << endl;
        throw invalid_argument("Polynomial a mismatch.");
    }

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
    // The function checks if the two polynomials could be subtracted.  If not, an error is raised.
    if (a != other.a) {
        cerr << "[PolynomialC/ERROR]" << endl <<
             "These two polynomials have different values of 'a'." << endl <<
             "Current polynomial value of a: " << a << endl <<
             "Other polynomial value of a: " << other.a << endl <<
             "Adding these two polynomials together would result in a mathematically" << endl <<
             "incorrect polynomial." << endl;
        throw invalid_argument("Polynomial a mismatch.");
    }

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
    // The function checks if the two polynomials could be multiplied.  If not, an error is raised.
    if (a != other.a) {
        cerr << "[PolynomialC/ERROR]" << endl <<
             "These two polynomials have different values of 'a'." << endl <<
             "Current polynomial value of a: " << a << endl <<
             "Other polynomial value of a: " << other.a << endl <<
             "Adding these two polynomials together would result in a mathematically" << endl <<
             "incorrect polynomial." << endl;
        throw invalid_argument("Polynomial a mismatch.");
    }

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
    // The function checks if the two polynomials could be multiplied.  If not, an error is raised.
    if (a != other.a) {
        cerr << "[PolynomialC/ERROR]" << endl <<
             "These two polynomials have different values of 'a'." << endl <<
             "Current polynomial value of a: " << a << endl <<
             "Other polynomial value of a: " << other.a << endl <<
             "Adding these two polynomials together would result in a mathematically" << endl <<
             "incorrect polynomial." << endl;
        throw invalid_argument("Polynomial a mismatch.");
    }

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
Polynomial& Polynomial::operator=(const Polynomial& other) = default;


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
double Polynomial::operator[](int i) const {
    return coefficient_list[i];
}


/* Parentheses Operator
 *
 * The parentheses operator solves the polynomial given a number x.
 *
 * Parameters: The input number, x.  (Double)
 * Returns: The result of the polynomial.  (Long Double)
 */
long double Polynomial::operator()(double x) const {
    return solve(x);
}


/* Angle Bracket Operator
 *
 * The angle bracket operator allows the polynomial to be displayed without calling the display
 * function.
 *
 * Parameters: Ofstream object, the polynomial itself.
 * Returns: Ofstream object.
 */
ostream &operator<<(ostream& out, const Polynomial& obj) {
    obj.hidden_display("simple");
    return out;
}
