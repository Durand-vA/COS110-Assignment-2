#include "univariate.h"

/**
 * @brief Checks if the polynomial is univariate
 *
 * @return true if the polynomial is univariate
 * @return false if the polynomial is not univariate
 */
bool univariate::isUnivariate() const {
    for (int i = 0; i < numTerms; i++) {
        switch (terms[i]->getNumVariables()) {
            case 0:
                break;
            case 1:
                if (terms[i]->getVariables()[0] != variable) {
                    return false;
                }
                break;
            default:
                return false;
        }
        if (terms[i]->getDegree() > degree) {
            return false;
        }
    }
    return true;
}
/**
 * @brief Clears the terms of the polynomial
 *
 */
void univariate::clearTerms() {
    for (int i = 0; i < numTerms; i++) {
        delete terms[i];
    }
    delete[] terms;
    terms = new term*[0];
    numTerms = 0;
}
/**
 * @brief Default constructor
 *
 * @param d the degree of the polynomial
 * @param c the variable of the polynomial
 */
univariate::univariate(int d, char c) : polynomial() {
    degree = d;
    variable = c;
}
/**
 * @brief Parameterized constructor
 *
 * @param t the array of terms
 * @param n the number of terms in the array
 */
univariate::univariate(term** t, int n) : polynomial(t, n) {
    variable = 'x';
    degree = 2;

    if (numTerms != 0) {
        degree = terms[0]->getDegree();
        if (terms[0]->getNumVariables() != 0) {
            variable = terms[0]->getVariables()[0];
        }
    }

    if (!isUnivariate()) {
        clearTerms();
    }
}
/**
 * @brief Parameterized constructor
 *
 * @param input The string representation of the polynomial. Format is
 * "a*x^b*y^c*z^d + e*x^f*y^g*z^h + ...", where a, b, c, d, e, f, g, and h are integers.
 */
univariate::univariate(const char* input) : polynomial(input) {
    variable = 'x';
    degree = 2;

    if (numTerms != 0) {
        degree = terms[0]->getDegree();
        if (terms[0]->getNumVariables() != 0) {
            variable = terms[0]->getVariables()[0];
        }
    }

    if (!isUnivariate()) {
        clearTerms();
    }
}
/**
 * @brief Copy constructor
 *
 * @param other The univariate to copy
 */
univariate::univariate(const univariate &other) : polynomial(other) {
    degree = other.degree;
    variable = other.variable;
}
/**
 * @brief Copy constructor
 *
 * @param other The polynomial to copy
 */
 //// Will test with other polynomial types
univariate::univariate(const polynomial &other) : polynomial(other) {
    variable = 'x';
    degree = 2;

    if (numTerms != 0) {
        degree = terms[0]->getDegree();
        if (terms[0]->getNumVariables() != 0) {
            variable = terms[0]->getVariables()[0];
        }
    }

    if (!isUnivariate()) {
        clearTerms();
    }
}
/**
 * @brief Parameterized constructor
 *
 * @param t The term to add
 */
univariate::univariate(term t) : polynomial(t) {
    variable = 'x';
    degree = 2;

    if (numTerms != 0) {
        degree = terms[0]->getDegree();
        if (terms[0]->getNumVariables() != 0) {
            variable = terms[0]->getVariables()[0];
        }
    }

    if (!isUnivariate()) {
        clearTerms();
    }
}
/**
 * @brief Assignment operator
 *
 * @param other The univariate to copy
 * @return univariate& The copied univariate
 */
univariate &univariate::operator=(const univariate &other) {
    this->polynomial::operator=(other);
    degree = other.degree;
    variable = other.variable;

    return *this;
}
/**
 * @brief Extraction operator
 *
 * @param is The input stream
 * @param u The univariate to extract to
 * @return istream& The input stream
 */
istream &operator>>(istream &is, univariate &u) {
    std::string s;
    getline(is, s);
    univariate temp = univariate(s.c_str());

    if (temp.numTerms != 0) {
        u = temp;
    }

    return is;
}
/**
 * @brief Unary negation operator
 *
 * @return polynomial* The negated polynomial
 */
polynomial* univariate::operator!() const {
    univariate* result = new univariate(degree, variable);
    for (int i = 0; i < numTerms; i++) {
        term* t = new term(!(*terms[i]));
        result->addOrRemoveTerm(t);
        delete t;
    }
    return result;
}
/**
 * @brief Evaluation operator
 *
 * @param vars The array of variables
 * @param vals The array of values
 * @param numVals The number of values
 * @return polynomial* The evaluated polynomial
 */
polynomial* univariate::operator()(char* vars, int* vals, int numVals) const {
    univariate* result = new univariate(degree, variable);
    for (int i = 0; i < numTerms; i++) {
        term* t = new term((*terms[i])(vars, vals, numVals));
        result->addOrRemoveTerm(t);
        delete t;
    }
    return result;
}
/**
 * @brief Evaluation operator
 *
 * @param inp The string representation of the variables and values
 * @return polynomial* The evaluated polynomial
 */
polynomial* univariate::operator()(string inp) const {
    univariate* result = new univariate(degree, variable);
    for (int i = 0; i < numTerms; i++) {
        term* t = new term((*terms[i])(inp));
        result->addOrRemoveTerm(t);
        delete t;
    }
    return result;
}
/**
 * @brief Addition operator
 *
 * @param other The polynomial to add
 * @return polynomial* The sum of the polynomials
 */
polynomial* univariate::operator+(const polynomial &other) const {
    univariate* result = new univariate(*this);
    for (int i = 0; i < other.getNumTerms(); i++) {
        result->addOrRemoveTerm(other.getTerms()[i]);
    }
    return result;
}
/**
 * @brief Addition assignment operator
 *
 * @param other The polynomial to add
 * @return polynomial& The current object. If the result is univariate, the current object is set to the result.
 */
polynomial &univariate::operator+=(const polynomial &other) {
    univariate* result = new univariate(*this);
    for (int i = 0; i < other.getNumTerms(); i++) {
        result->addOrRemoveTerm(other.getTerms()[i]);
    }
    if (result->isUnivariate()) {
        *this = *result;
    }
    delete result;
    return *this;
}
/**
 * @brief Subtraction operator
 *
 * @param other The polynomial to subtract
 * @return polynomial* The difference of the polynomials
 */
polynomial* univariate::operator-(const polynomial &other) const {
    univariate* result = new univariate(*this);
    for (int i = 0; i < other.getNumTerms(); i++) {
        term* t = new term(!(*other.getTerms()[i]));
        result->addOrRemoveTerm(t);
        delete t;
    }
    return result;
}
/**
 * @brief Subtraction assignment operator
 *
 * @param other The polynomial to subtract
 * @return polynomial& The current object. If the result is univariate, the current object is set to the result.
 */
polynomial &univariate::operator-=(const polynomial &other) {
    univariate* result = new univariate(*this);
    for (int i = 0; i < other.getNumTerms(); i++) {
        term* t = new term(!(*other.getTerms()[i]));
        result->addOrRemoveTerm(t);
        delete t;
    }
    if (result->isUnivariate()) {
        *this = *result;
    }
    delete result;
    return *this;
}
/**
 * @brief Multiplication operator
 *
 * @param other The polynomial to multiply
 * @return polynomial* The product of the polynomials
 */
polynomial* univariate::operator*(const polynomial &other) const {
    univariate* result = new univariate(term(0, 0, NULL, NULL));
    result->clearTerms();

    for (int i = 0; i < numTerms; i++) {
        for (int j = 0; j < other.getNumTerms(); j++) {
            term* t = new term((*terms[i]) * (*other.getTerms()[j]));
            result->addOrRemoveTerm(t);
            delete t;
        }
    }
    return result;
}
/**
 * @brief Multiplication assignment operator
 *
 * @param other The polynomial to multiply
 * @return polynomial& The current object. If the result is univariate, the current object is set to the result.
 */
polynomial &univariate::operator*=(const polynomial &other) {
    univariate* result = new univariate(term(0, 0, NULL, NULL));
    result->clearTerms();

    for (int i = 0; i < numTerms; i++) {
        for (int j = 0; j < other.getNumTerms(); j++) {
            term* t = new term((*terms[i]) * (*other.getTerms()[j]));
            result->addOrRemoveTerm(t);
            delete t;
        }
    }
    if (result->getNumTerms() != 0/* && (*result)[0]->getNumVariables() == 1*/) {
        result->degree = result->terms[0]->getDegree();
    }
    if (result->isUnivariate()) {
        *this = *result;
    }
    delete result;
    return *this;
}
