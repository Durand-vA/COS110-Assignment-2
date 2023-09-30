#include "polynomial.h"

void swap(term** t, int index1, int index2) {
    term* temp = t[index1];
    t[index1] = t[index2];
    t[index2] = temp;
}

int partition(term** t, int start, int end) {
    int pivotIndex = start;
    term* pivotValue = t[end];
    for (int i = start; i < end; i++) {
        if (*t[i] < *pivotValue) {
            swap(t, i, pivotIndex);
            pivotIndex++;
        }
    }
    swap(t, pivotIndex, end);
    return pivotIndex;
}
/**
 * Sorts the array of terms using quicksort.
 * @param t the array of terms
 * @param start the starting index
 * @param end the ending index
 */
void quickSort(term** t, int start, int end) {
    if (start >= end) return;

    int index = partition(t, start, end);
    quickSort(t, start, index-1);
    quickSort(t, index+1, end);
}
/**
 * Removes the term at the given index from the array of terms.
 * @param terms the array of terms
 * @param numTerms the number of terms in the array
 * @param idx the index of the term to remove
 */
void removeTerm(term**& terms, int& numTerms, int idx) {
    term** newTerms = new term*[numTerms-1];
    for (int i = 0; i < idx; i++) {
        newTerms[i] = terms[i];
    }
    for (int i = idx + 1; i < numTerms; i++) {
        newTerms[i-1] = terms[i];
    }
    delete terms[idx];
    delete[] terms;
    terms = newTerms;
    numTerms--;
}
/**
 * Adds the given term to the array of terms.
 * @param terms the array of terms
 * @param numTerms the number of terms in the array
 * @param t the term to add
 */
void addTerm(term**& terms, int& numTerms, term* t) {
    term** newTerms = new term*[numTerms + 1];
    for (int i = 0; i < numTerms; i++) {
        newTerms[i] = terms[i];
        terms[i] = NULL;
    }
    newTerms[numTerms] = new term(*t);
    delete[] terms;
    terms = newTerms;
    numTerms++;
}
/**
 * Adds the coefficient of the given term to an equal term,
 * or adds the term to the array. If the coefficient is zero after
 * addition, it removes the term from the array.
 * @param t the term to add or remove
 */
void polynomial::addOrRemoveTerm(term* t) {
    int idx = termIndex(t);
    if (idx != -1) {
        int coefficient = (*t)[-1] + (*terms[idx])[-1];
        if (coefficient == 0) {
            removeTerm(terms, numTerms, idx);
            quickSort(terms, 0, numTerms-1);
            return;
        }
        (*terms[idx])[-1] = coefficient;
//        int numVars = t->getNumVariables();
//        char* vars = t->getVariables();
//        int* vals = new int[numVars];
//        for (int x = 0; x < numVars; x++) {
//            vals[x] = (*t)[x];
//        }
//        delete terms[idx];
//        terms[idx] = new term(coefficient, numVars, vars, vals);
//        delete [] vals;
//        quickSort(terms, 0, numTerms-1);
        return;
    }
    addTerm(terms, numTerms, t);
    quickSort(terms, 0, numTerms-1);
}
/**
 * Returns the index of the given term in the array of terms.
 * @param t the term to find
 * @return the index of the term, or -1 if not found
 */
int polynomial::termIndex(term* t) const {
    for (int i = 0; i < numTerms; i++) {
        if (*terms[i] == *t) {
            return i;
        }
    }
    return -1;
}
/**
 * Default constructor.
 */
polynomial::polynomial() {
    numTerms = 0;
    terms = new term*[0];
}
/**
 * Parameterized constructor.
 * @param t the array of terms
 * @param n the number of terms in the array
 */
polynomial::polynomial(term** t, int n) {
    numTerms = 0;
    terms = new term*[0];
    for (int i = 0; i < n; i++) {
        addOrRemoveTerm(t[i]);
    }
}

bool sign(char c) {
    return c == '+' || c == '-';
}
/**
 * Parameterized constructor.
 * @param input the string representation of the polynomial. Format is
 * "a*x^b*y^c*z^d + e*x^f*y^g*z^h + ...", where a, b, c, d, e, f, g, and h are integers.
 */
polynomial::polynomial(const char* input) {
    numTerms = 0;
    terms = new term*[0];
    std::stringstream ss;
    ss << input;
    std::string s;
    bool negate = false;
    while (std::getline(ss, s, ' ')) {
        if (sign(s[0]) && s.length() == 1) {
            negate = s[0] == '-';
        } else {
            term* t = new term(s.c_str());
            term* nt = new term(!(*t));
            if (negate) {
                addOrRemoveTerm(nt);
            } else {
                addOrRemoveTerm(t);
            }
            delete t;
            delete nt;
        }
    }
}
/**
 * Copy constructor.
 * @param other the polynomial to copy
 */
polynomial::polynomial(const polynomial &other) {
    numTerms = 0;
    terms = new term*[0];
    for (int i = 0; i < other.numTerms; i++) {
        addOrRemoveTerm(other.terms[i]);
    }
}
/**
 * Parameterized constructor.
 * @param t the term to add
 */
polynomial::polynomial(term t) {
    numTerms = 0;
    terms = new term*[0];
    addOrRemoveTerm(&t);
}
/**
 * Deletes the array of terms. Sets the array to NULL and the number of terms to 0.
 * @param terms the array of terms
 * @param numTerms the number of terms in the array
 */
void deleteTerms(term**& terms, int& numTerms) {
    for (int i = 0; i < numTerms; i++) {
        delete terms[i];
    }
    delete[] terms;
    terms = NULL;
    numTerms = 0;
}
/**
 * Assignment operator.
 * @param other the polynomial to copy
 * @return the copied polynomial
 */
polynomial &polynomial::operator=(const polynomial &other) {
    if (this == &other) {
        return *this;
    }
    deleteTerms(terms, numTerms);
    terms = new term*[0];
    for (int i = 0; i < other.numTerms; i++) {
        addOrRemoveTerm(other.terms[i]);
    }
    return *this;
}
/**
 * Destructor.
 */
polynomial::~polynomial() {
    deleteTerms(terms, numTerms);
}
/**
 * Returns the array of terms.
 * @return the array of terms
 */
term** polynomial::getTerms() const {
    return terms;
}
/**
 * Returns the number of terms in the array.
 * @return the number of terms in the array
 */
int polynomial::getNumTerms() const {
    return numTerms;
}

ostream &operator<<(ostream &os, const polynomial &p) {
    if (p.numTerms == 0) {
        os << '0';
    }
    for (int i = 0; i < p.numTerms; i++) {
        std::string s;
        os << ~(*p.terms[i]);
        if (i < p.numTerms - 1) {
            os << " + ";
        }
    }
    os << "\n";
    return os;
}
/**
 * Returns the term at the given index.
 * @param idx the index of the term
 * @return Pointer to the term at the given index (const). NULL if index is out of bounds.
 */
term* polynomial::operator[](int idx) const {
    if (idx < 0 || idx > numTerms)
        return NULL;

    return terms[idx];
}
/**
 * Returns the term at the given index.
 * @param idx the index of the term
 * @return Pointer to the term at the given index. NULL if index is out of bounds.
 */
term* polynomial::operator[](int idx) {
    if (idx < 0 || idx > numTerms)
        return NULL;

    return terms[idx];
}
