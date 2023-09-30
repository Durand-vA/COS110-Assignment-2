#include "bivariate.h"
#include "univariate.h"

/**
 * @brief Clears the terms of the polynomial
 *
 */
void bivariate::clearTerms() {
    for (int i = 0; i < numTerms; i++) {
        delete terms[i];
    }
    delete[] terms;
    terms = new term*[0];
    numTerms = 0;
}
/**
 * @brief Checks if the polynomial is bivariate
 *
 * the polynomial can have at most 2 types of variables
 * All terms in the bivariate must have a degree less than or equal to the degree variable
 *
 */
bool bivariate::isBivariate() const
{
    for (int i = 0; i < numTerms; i++)
    {
        switch (terms[i]->getNumVariables())
        {
            case 0:
                break;
            case 1:
                if (terms[i]->getVariables()[0] != v1 && terms[i]->getVariables()[0] != v2) {
                    return false;
                }
                break;
            case 2:
                if (terms[i]->getVariables()[0] != v1 && terms[i]->getVariables()[0] != v2) {
                    return false;
                }
                if (terms[i]->getVariables()[1] != v1 && terms[i]->getVariables()[1] != v2) {
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
 * @brief Default constructor
 * @param d Degree
 * @param c1 Var1
 * @param c2 Var2
 */
bivariate::bivariate(int d, char c1, char c2) {
    degree = d;
    v1 = c1;
    v2 = c2;
}
/**
 * @brief Parameterized constructor
 * @param t Array of terms
 * @param n Number of terms in the array
 */
bivariate::bivariate(term** t, int n) : polynomial(t, n) {
    v1 = 'x';
    v2 = 'y';
    degree = 2;

    if (numTerms != 0) {
        degree = terms[0]->getDegree();
        if (terms[0]->getNumVariables() != 0) {
            v1 = terms[0]->getVariables()[0];
            bool found = false;
            for (int i = 0; i < numTerms && !found; i++) {
                for (int j = 0; j < terms[i]->getNumVariables() && !found; j++) {
                    if (terms[i]->getVariables()[j] != v1) {
                        v2 = terms[i]->getVariables()[j];
                        found = true;
                    }
                }
            }
        }
    }

    if (!isBivariate()) {
        clearTerms();
    }
}
/**
 * @brief Parameterized constructor
 * @param input String input
 */
bivariate::bivariate(const char* input) : polynomial(input) {
    v1 = 'x';
    v2 = 'y';
    degree = 2;

    if (numTerms != 0) {
        degree = terms[0]->getDegree();
        if (terms[0]->getNumVariables() != 0) {
            v1 = terms[0]->getVariables()[0];
            bool found = false;
            for (int i = 0; i < numTerms && !found; i++) {
                for (int j = 0; j < terms[i]->getNumVariables() && !found; j++) {
                    if (terms[i]->getVariables()[j] != v1) {
                        v2 = terms[i]->getVariables()[j];
                        found = true;
                    }
                }
            }
        }
    }

    if (!isBivariate()) {
        clearTerms();
    }
}
/**
 * @brief Copy constructor
 * @param other Other bivariate
 */
bivariate::bivariate(const bivariate &other) {
    v1 = other.v1;
    v2 = other.v2;
    degree = other.degree;
    numTerms = other.numTerms;
    delete [] terms;
    terms = new term*[numTerms];
    for (int i = 0; i < numTerms; i++) {
        terms[i] = new term(*other.terms[i]);
    }
}
/**
 * @brief Copy constructor
 * @param other Other polynomial
 */
bivariate::bivariate(const polynomial &other) : polynomial(other) {
    v1 = 'x';
    v2 = 'y';
    degree = 2;

    if (numTerms != 0) {
        degree = terms[0]->getDegree();
        if (terms[0]->getNumVariables() != 0) {
            v1 = terms[0]->getVariables()[0];
            bool found = false;
            for (int i = 0; i < numTerms && !found; i++) {
                for (int j = 0; j < terms[i]->getNumVariables() && !found; j++) {
                    if (terms[i]->getVariables()[j] != v1) {
                        v2 = terms[i]->getVariables()[j];
                        found = true;
                    }
                }
            }
        }
    }

    if (!isBivariate()) {
        clearTerms();
    }
}
/**
 * @brief Parameterized constructor
 * @param t Term
 */
bivariate::bivariate(term t) : polynomial(t) {
    v1 = 'x';
    v2 = 'y';
    degree = 2;

    if (numTerms != 0) {
        degree = terms[0]->getDegree();
        if (terms[0]->getNumVariables() != 0) {
            v1 = terms[0]->getVariables()[0];
            bool found = false;
            for (int i = 0; i < numTerms && !found; i++) {
                for (int j = 0; j < terms[i]->getNumVariables() && !found; j++) {
                    if (terms[i]->getVariables()[j] != v1) {
                        v2 = terms[i]->getVariables()[j];
                        found = true;
                    }
                }
            }
        }
    }

    if (!isBivariate()) {
        clearTerms();
    }
}
/**
 * @brief Assignment operator
 * @param other Other bivariate
 * @return This bivariate
 */
bivariate &bivariate::operator=(const bivariate &other) {
    if (this == &other) {
        return *this;
    }
    this->polynomial::operator=(other);
    degree = other.degree;
    v1 = other.v1;
    v2 = other.v2;
    return *this;
}
/**
 * @brief Insertion operator
 * @param is Input stream
 * @param u Bivariate
 * @return Input stream
 */
istream &operator>>(istream &is, bivariate &u) {
    std::string s;
    getline(is, s);
    bivariate temp = bivariate(s.c_str());
    if (temp.numTerms != 0) {
        u = temp;
    }
    return is;
}
/**
 * @brief Unary negation operator
 * @return Negated polynomial
 */
polynomial* bivariate::operator!() const {
    bivariate* result = new bivariate(degree, v1, v2);
    for (int i = 0; i < numTerms; i++) {
        term* t = new term(!(*terms[i]));
        result->addOrRemoveTerm(t);
        delete t;
    }
    return result;
}
/**
 * @brief Evaluation operator
 * @param vars Array of variables
 * @param vals Array of values
 * @param numVals Number of values
 * @return Evaluated polynomial
 */
polynomial* bivariate::operator()(char* vars, int* vals, int numVals) const {
    bivariate* result = new bivariate(degree, v1, v2);
    for (int i = 0; i < numTerms; i++) {
        term* t = new term((*terms[i])(vars, vals, numVals));
        result->addOrRemoveTerm(t);
        delete t;
    }
    return result;
}
/**
 * @brief Evaluation operator
 * @param inp String input
 * Format is "x=1 y=2 ..."
 * @return Evaluated polynomial
 */
polynomial* bivariate::operator()(string inp) const {
    bivariate* result = new bivariate(degree, v1, v2);
    for (int i = 0; i < numTerms; i++) {
        term* t = new term((*terms[i])(inp));
        result->addOrRemoveTerm(t);
        delete t;
    }
    return result;
}
/**
 * @brief Addition operator
 * @param other Other polynomial
 * @return Sum of polynomials
 */
polynomial* bivariate::operator+(const polynomial &other) const {
    bivariate* result = new bivariate(*this);
    for (int i = 0; i < other.getNumTerms(); i++) {
        result->addOrRemoveTerm(other.getTerms()[i]);
    }
    return result;
}
/**
 * @brief Addition assignment operator
 * @param other Other polynomial
 * @return This polynomial
 */
polynomial &bivariate::operator+=(const polynomial &other) {
    bivariate* result = new bivariate(*this);
    for (int i = 0; i < other.getNumTerms(); i++) {
        result->addOrRemoveTerm(other.getTerms()[i]);
    }
    if (result->isBivariate()) {
        *this = *result;
    }
    delete result;
    return *this;
}
/**
 * @brief Subtraction operator
 * @param other Other polynomial
 * @return Difference of polynomials
 */
polynomial* bivariate::operator-(const polynomial &other) const {
    bivariate* result = new bivariate(*this);
    for (int i = 0; i < other.getNumTerms(); i++) {
        term* t = new term(!(*other.getTerms()[i]));
        result->addOrRemoveTerm(t);
        delete t;
    }
    return result;
}
/**
 * @brief Subtraction assignment operator
 * @param other Other polynomial
 * @return This polynomial
 */
polynomial &bivariate::operator-=(const polynomial &other) {
    bivariate* result = new bivariate(*this);
    for (int i = 0; i < other.getNumTerms(); i++) {
        term* t = new term(!(*other.getTerms()[i]));
        result->addOrRemoveTerm(t);
        delete t;
    }
    if (result->isBivariate()) {
        *this = *result;
    }
    delete result;
    return *this;
}
/**
 * @brief Multiplication operator
 * @param other Other polynomial
 * @return Product of polynomials
 */
polynomial* bivariate::operator*(const polynomial &other) const {
    bivariate* result = new bivariate(term(0, 0, NULL, NULL));

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
 * @param other Other polynomial
 * @return This polynomial
 */
polynomial &bivariate::operator*=(const polynomial &other) {
    bivariate* result = new bivariate(term(0, 0, NULL, NULL));

    for (int i = 0; i < numTerms; i++) {
        for (int j = 0; j < other.getNumTerms(); j++) {
            term* t = new term((*terms[i]) * (*other.getTerms()[j]));
            result->addOrRemoveTerm(t);
            delete t;
        }
    }
    if (result->getNumTerms() != 0 && (*result)[0]->getNumVariables() == 2) {
        result->degree = result->terms[0]->getDegree();
    }
    if (result->isBivariate()) {
        *this = *result;
    }
    delete result;
    return *this;
}
