
#include "quadratic.h"
#include "linear.h"

/**
 * @brief Default constructor
 *
 * @param d the degree of the polynomial
 * @param c the variable of the polynomial
 */
quadratic::quadratic(char c) : univariate(2, c) {
}
/**
 * @brief Parameterized constructor
 *
 * @param t the array of terms
 * @param n the number of terms in the array
 */
quadratic::quadratic(term** t, int n) : univariate(t, n) {
    degree = 2;
    if (numTerms != 0) {
        if (!isUnivariate()) {
            clearTerms();
        }
    }
}
/**
 * @brief Parameterized constructor
 *
 * @param input the string input
 * Format is "a*x^b + c*x^d + ...", where a, b, c, and d are integers.
 */
quadratic::quadratic(const char* input) : univariate(input) {
    degree = 2;
    if (numTerms != 0) {
        if (!isUnivariate()) {
            clearTerms();
        }
    }
}

quadratic::quadratic(const quadratic &other) : univariate(other) {
    degree = 2;
//    if (numTerms != 0) {
//        if (!isUnivariate()) {
//            clearTerms();
//        }
//    }
}

quadratic::quadratic(const polynomial &other) : univariate(other) {
    degree = 2;
    if (numTerms != 0) {
        if (!isUnivariate()) {
            clearTerms();
        }
    }
}

quadratic::quadratic(term t) : univariate(t) {
    degree = 2;
    if (numTerms != 0) {
        if (!isUnivariate()) {
            clearTerms();
        }
    }
}

void quadratic::printRoots() const {
    if (getNumTerms() == 0) {
        std::cout << "No roots" << endl;
        return;
    }
    linear l(*this);
    if (l.getNumTerms() != 0) {
        l.printRoots();
        return;
    }

    char* inp = new char[4];
    inp[0] = variable;
    inp[1] = '^';
    inp[2] = '2';
    inp[3] = '\0';

    term* term0 = new term(inp);
    inp[2] = '1';
    term* term1 = new term(inp);
    term* term2 = new term("0");

    delete [] inp;

    bool decFirst = true, decSecond = true;
    quadratic* q = new quadratic(*this);
    q->addOrRemoveTerm(term0);
    if (q->numTerms < numTerms) {
        q->addOrRemoveTerm((*this)[0]);
        decFirst = false;
    }
    q->addOrRemoveTerm(term1);
    if (q->numTerms < numTerms) {
        q->addOrRemoveTerm((*this)[1]);
        decSecond = false;
    }
    q->addOrRemoveTerm(term2);

    // Delete the terms
    delete term0;
    delete term1;
    delete term2;

    double a, b, c;
    a = (*(*q)[0])[-1];
    b = (*(*q)[1])[-1];
    c = (*(*q)[2])[-1];

    delete q;

    if (decFirst) {
        a--;
    }
    if (decSecond) {
        b--;
    }

    double d = b * b - 4 * a * c;

    if (d < 0) {
        std::cout << "No roots" << endl;
        return;
    }

    double r1 = (-b + sqrt(d)) / (2 * a);
    double r2 = (-b - sqrt(d)) / (2 * a);

    std::cout << "Roots : " << variable << " = "
                << std::setprecision(2) << r1 << " , "
                << variable << " = "
                << r2 << endl;
}
