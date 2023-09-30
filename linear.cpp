#include "linear.h"
/**
 * @brief Default constructor
 *
 */
linear::linear(char c) : univariate(1, c) {
}
/**
 * @brief Parameterized constructor
 *
 * @param t the array of terms
 * @param n the number of terms in the array
 */
linear::linear(term** t, int n) : univariate(t, n) {
    degree = 1;
    if (numTerms != 0) {
        if (!isUnivariate()) {
            clearTerms();
        }
    }
}
/**
 * @brief Parameterized constructor
 *
 * @param input the input string
 */
linear::linear(const char* input) : univariate(input) {
    degree = 1;
    if (numTerms != 0) {
        if (!isUnivariate()) {
            clearTerms();
        }
    }
}
/**
 * @brief Copy constructor
 *
 * @param other the other polynomial
 */
linear::linear(const linear &other) : univariate(other) {
    degree = 1;
    if (numTerms != 0) {
        if (!isUnivariate()) {
            clearTerms();
        }
    }
}
/**
 * @brief Copy constructor
 *
 * @param other the other polynomial
 */
linear::linear(const polynomial &other) : univariate(other) {
    degree = 1;
    if (numTerms != 0) {
        if (!isUnivariate()) {
            clearTerms();
        }
    }
}
/**
 * @brief Parameterized constructor
 *
 * @param t the term
 */
linear::linear(term t) : univariate(t) {
    degree = 1;
    if (numTerms != 0) {
        if (!isUnivariate()) {
            clearTerms();
        }
    }
}
/**
 * @brief Prints the roots of the polynomial
 *
 */
void linear::printRoots() const {
    if (numTerms == 0) {
        cout << "No roots" << endl;
        return;
    }
    char* inp = new char[2];
    inp[0] = variable;
    inp[1] = '\0';

    term* term0 = new term(inp);
    term* term1 = new term("0");

    delete [] inp;

    bool decFirst = true;
    linear* q = new linear(*this);
    q->addOrRemoveTerm(term0);
    if (q->numTerms < numTerms) {
        q->addOrRemoveTerm((*this)[0]);
        decFirst = false;
    }
    q->addOrRemoveTerm(term1);

    // Delete the terms
    delete term0;
    delete term1;

    int m, c;
    m = (*(*q)[0])[-1];
    c = (*(*q)[0])[-1];

    delete q;

    if (decFirst) {
        m--;
    }

    if (m == 0) {
        cout << "No roots" << endl;
        return;
    }
    double r = -static_cast<double>(c)/m;
    cout << "Roots : " << variable << " = " << std::setprecision(2) << std::fixed << r << endl;
}
