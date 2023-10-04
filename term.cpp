#include "term.h"
#include <sstream>

void swap(char* var, int* pow, int index1, int index2) {
    char temp = var[index1];
    var[index1] = var[index2];
    var[index2] = temp;

    int temp1 = pow[index1];
    pow[index1] = pow[index2];
    pow[index2] = temp1;
}

int partition(char* var, int* pow, int start, int end) {
    int pivotIndex = start;
    char pivotValue = var[end];
    for (int i = start; i < end; i++) {
        if (var[i] < pivotValue) {
            swap(var, pow, i, pivotIndex);
            pivotIndex++;
        }
    }
    swap(var, pow, pivotIndex, end);
    return pivotIndex;
}
/**
 *
 * @param var array of variables
 * @param pow array of powers
 * @param start start index
 * @param end end index
 */
void quickSort(char* var, int* pow, int start, int end) {
    if (start >= end) return;

    int index = partition(var, pow, start, end);
    quickSort(var, pow, start, index-1);
    quickSort(var, pow, index+1, end);
}
/**
 * Add variable to term
 * @param var variable to add
 * @param pow power of variable
 */
void term::addVariable(char var, int pow) {
    if (coefficient == 0 || pow <= 0) {
        return;
    }

    /** Check if the value is already in the array.
        * If it is, add the powers together.
        * If it isn't, add it to the array.
        */
    for (int i = 0; i < numVariables; i++) {
        if (variables[i] == var) {
            powers[i] += pow;
            return;
        }
    }

    /**
     * Add the variable to the array.
     */
    char* newVars = new char[numVariables+1];
    int* newPows = new int[numVariables+1];

    for (int i = 0; i < numVariables; i++) {
        newVars[i] = variables[i];
        newPows[i] = powers[i];
    }

    newVars[numVariables] = var;
    newPows[numVariables] = pow;
    numVariables++;

    delete [] variables;
    delete [] powers;

    variables = newVars;
    powers = newPows;

    quickSort(variables, powers, 0, numVariables-1);
}
/**
 * Remove variable from term
 * @param var variable to remove
 */
void term::removeVariable(char var) {
    int index = getVarIndex(var);
    if (index == -1) {
        return;
    }
    char* newVars = new char[numVariables - 1];
    int* newPows = new int[numVariables - 1];

    int count = 0;
    for (int i = 0; i < numVariables; i++) {
        if (i != index) {
            newVars[count] = variables[i];
            newPows[count] = powers[i];
            count++;
        }
    }

    delete [] variables;
    delete [] powers;

    numVariables--;

    variables = newVars;
    powers = newPows;

    quickSort(variables, powers, 0, numVariables-1);
}
/**
 * Default Constructor
 */
term::term() {
    coefficient = 1;
    numVariables = 0;
    variables = new char[numVariables];
    powers = new int[numVariables];
}
//void nullify(term& term) {
//    if (term[-1] == 0) {
//        delete [] term.getVariables();
//        delete [] term.get;
//    }
//}
/**
 * Copy Constructor
 * @param other term to copy
 */
term::term(const term &other) {
    coefficient = other.coefficient;
    numVariables = other.numVariables;

    if (coefficient == 0) {
        numVariables = 0;
    }

    variables = new char[numVariables];
    powers = new int[numVariables];

    for (int i = 0; i < numVariables; i++) {
        variables[i] = other.variables[i];
        powers[i] = other.powers[i];
    }
}
/**
 * Parameterized Constructor
 * @param c coefficient
 * @param n number of variables
 * @param v array of variables
 * @param p array of powers
 */
term::term(int c, int n, char* v, int* p) {
    coefficient = c;
    numVariables = n;

    if (coefficient == 0) {
        numVariables = 0;
    }

    variables = new char[numVariables];
    powers = new int[numVariables];

    for (int i = 0; i < numVariables; i++) {
        variables[i] = v[i];
        powers[i] = p[i];
    }

    quickSort(variables, powers, 0, numVariables-1);
}

bool isalpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isSign(char c) {
    return c == '+' || c == '-';
}
/**
 * Parameterized Constructor taking string
 * @param input string representation of term. Format is "coeff*var1^pow1*var2^pow2*...*varn^pown"
 */
term::term(const char* input) {
    std::stringstream ss;
    ss << input;

    bool b, coeff = true;

    coefficient = 1;
    numVariables = 0;

    variables = new char[numVariables];
    powers = new int[numVariables];

    std::string s;
    while (std::getline(ss, s, '*')) {
        b = true;

        // check for coefficient
        if (coeff) {
            if (!isalpha(s[0])) {
                if (isSign(s[0])) {
                    if (s[0] == '-') {
                        coefficient = -1;
                    }

                    s.erase(0, 1);

                    if (!isalpha(s[0])) {
                        std::stringstream ss1;
                        ss1 << s;
                        int n;
                        ss1 >> n;
                        coefficient *= n;
                        b = false;
                    }
                } else {
                    // multiply coefficient with s and skip the rest
                    std::stringstream ss1;
                    ss1 << s;
                    int n;
                    ss1 >> n;
                    coefficient *= n;
                    b = false;
                }
            }

            coeff = false;
        }

        if (b) {
            int pow;
            char var;
            if (s.find('^') != std::string::npos) {
                std::stringstream ss1;
                ss1 << s.substr(s.find('^') + 1);
                ss1 >> pow;
                var = s[0];
            } else {
                pow = 1;
                var = s[0];
            }
            addVariable(var, pow);
        }
    }

    if (coefficient == 0) {
        numVariables = 0;
        delete [] variables;
        delete [] powers;
        variables = new char[0];
        powers = new int[0];
    }

}
/**
 * Assignment operator
 * @param other term to copy
 * @return this term
 */
term &term::operator=(const term &other) {
    if (this == &other) {
        return *this;
    }

    coefficient = other.coefficient;
    numVariables = other.numVariables;

    if (coefficient == 0) {
        numVariables = 0;
    }

    delete [] variables;
    delete [] powers;

    variables = new char[numVariables];
    powers = new int[numVariables];

    for (int i = 0; i < numVariables; i++) {
        variables[i] = other.variables[i];
        powers[i] = other.powers[i];
    }

    quickSort(variables, powers, 0, numVariables-1);
    return *this;
}

term::~term() {
    delete [] variables;
    delete [] powers;
}

char* term::getVariables() const {
    return variables;
}

int term::getNumVariables() const {
    return numVariables;
}
/**
 * Get sum of powers of all variables
 * @return sum of powers of all variables
 */
int term::getDegree() const {
    int sum = 0;
    for (int i = 0; i < numVariables; i++) {
        sum += powers[i];
    }
    return sum;
}
/**
 * Get index of variable in term
 * @param var char representing var in array
 * @return Index of variable. -1 if var is not in term
 */
int term::getVarIndex(char var) const {
    for (int i = 0; i < numVariables; i++) {
        if (variables[i] == var) {
            return i;
        }
    }
    return -1;
}
/**
 * Output term to string
 * @return string representation of term. Format is "coeff*var1^pow1*var2^pow2*...*varn^pown"
 */
string term::operator~() const {
    std::stringstream ss;
    if (coefficient != 1) {
        if (coefficient == -1) {
            ss << "-";
        } else {
            ss << coefficient;
        }
    }
    if (numVariables == 0) {
        if (coefficient == 1 || coefficient == -1)
            ss << 1;
        return ss.str();
    }
    for (int i = 0; i < numVariables; i++) {
        if (i != 0 || !(coefficient == 1 || coefficient == -1))
            ss << '*';

        ss << variables[i];
        if (powers[i] != 1) {
            ss << '^';
            ss << powers[i];
        }
    }

    return ss.str();
}
/**
 * Output term to output stream
 * @param os output stream
 * @param t term to output
 * @return output stream
 */
ostream &operator<<(ostream &os, const term &t) {
    os << ~t << std::endl;
    return os;
}
/**
 * Read term from input stream
 * @param is input stream. Format is "coeff*var1^pow1*var2^pow2*...*varn^pown"
 * @param t term to read into
 * @return input stream
 */
istream &operator>>(istream &is, term &t) {
    std::stringstream ss;
    std::string temp;
    is >> temp;
    ss << temp;

    bool b, coeff = true;


    t.coefficient = 1;
    t.numVariables = 0;

    delete [] t.variables;
    t.variables = new char[0];
    delete [] t.powers;
    t.powers = new int[0];

    std::string s;
    while (std::getline(ss, s, '*')) {
        b = true;

        // check for coefficient
        if (coeff) {
            if (!isalpha(s[0])) {
                if (isSign(s[0])) {
                    if (s[0] == '-') {
                        t.coefficient = -1;
                    }

                    s.erase(0, 1);

                    if (!isalpha(s[0])) {
                        std::stringstream ss1;
                        ss1 << s;
                        int n;
                        ss1 >> n;
                        t.coefficient *= n;
                        b = false;
                    }
                } else {
                    // multiply coefficient with s and skip the rest
                    std::stringstream ss1;
                    ss1 << s;
                    int n;
                    ss1 >> n;
                    t.coefficient *= n;
                    b = false;
                }
            }

            coeff = false;
        }

        if (b) {
            int pow;
            char var;
            if (s.find('^') != std::string::npos) {
                std::stringstream ss1;
                ss1 << s.substr(s.find('^') + 1);
                ss1 >> pow;
                var = s[0];
            } else {
                pow = 1;
                var = s[0];
            }
            t.addVariable(var, pow);
        }
    }

    if (t.coefficient == 0) {
        t.numVariables = 0;
        delete [] t.variables;
        delete [] t.powers;
        t.variables = new char[0];
        t.powers = new int[0];
    }

    return is;
}

//int max(int n, int m) {
//    return n > m ? n : m;
//}
int min(int n, int m) {
    return n < m ? n : m;
}
/**
 * Multiply this term by other term
 * @param other term to multiply with
 * @return this term multiplied by other term
 */
const term term::operator*(const term &other) const {
    term out;
    for (int i = 0; i < numVariables; i++) {
        out.addVariable(variables[i], powers[i]);
    }
    for (int i = 0; i < other.numVariables; i++) {
        out.addVariable(other.variables[i], other.powers[i]);
    }
    out.coefficient = coefficient * other.coefficient;
    return term(out);
}
/**
 * Multiply this term by other term
 * @param other term to multiply with
 * @return this term multiplied by other term
 */
term &term::operator*=(const term &other) {
    term out;
    for (int i = 0; i < numVariables; i++) {
        out.addVariable(variables[i], powers[i]);
    }
    for (int i = 0; i < other.numVariables; i++) {
        out.addVariable(other.variables[i], other.powers[i]);
    }
    out.coefficient = coefficient * other.coefficient;

    *this = out;

    return *this;
}

int pow(int val, int power) {
    int out = 1;
    for (int i = 0; i < power; i++) {
        out *= val;
    }
    return out;
}
/**
 * Substitute values for variables
 * @param vars array of variables
 * @param vals array of values
 * @param numVals number of values
 * @return term with variables replaced with values
 */
const term term::operator()(char* vars, int* vals, int numVals) const {
    int coeff = coefficient;
    term temp(*this);
    for (int i = 0; i < numVals; i++) {
        int varIndex = temp.getVarIndex(vars[i]);
        if (varIndex != -1) {
            coeff *= pow(vals[i], temp[varIndex]);
            temp.removeVariable(vars[i]);
        }
    }
    temp.coefficient = coeff;

    return term(temp);
    // expected 864*b^5*w^4
    // actual 48*b^5*w^4
}
/**
 * Substitute values for variables
 * @param inp string of variables and values. Format is "var1=val1 var2=val2 ..."
 * @return term with variables replaced with values
 */
const term term::operator()(string inp) const {
    int coeff = coefficient;
    term temp = *this;

    std::stringstream ss;
    ss << inp;
    std::string s;
    while (std::getline(ss, s, ' ')) {
        char var = s[0];
        int index = temp.getVarIndex(var);
        if (index != -1) {
            s.erase(0, 2);
            std::stringstream st;
            int n;
            st << s;
            st >> n;
            coeff *= pow(n, temp[index]);
            temp.removeVariable(var);
        }
    }
    temp.coefficient = coeff;

    return term(temp);
}
/**
 * Equality operator
 * @param other term to compare to
 * @return true if variables and powers are equal (i.e. can be added)
 */
bool term::operator==(const term &other) const {
    if (numVariables != other.numVariables)
        return false;
    for (int i = 0; i < numVariables; i++) {
        if (variables[i] != other.variables[i]) {
            return false;
        }
        if (powers[i] != other.powers[i]) {
            return false;
        }
    }
    return true;
}
/**
 * Less than operator
 * @param other term to compare to
 * @return true if this term is less than other term
 */
bool term::operator<(const term &other) const {
    if (*this == other)
        return false;

    if (numVariables == 0)
        return false;

    if (other.numVariables == 0)
        return true;

    int minIndex = min(numVariables, other.numVariables);
    for (int i = 0; i < minIndex; i++) {
        if (variables[i] == other.variables[i]) {
            if (powers[i] != other.powers[i])
                return powers[i] > other.powers[i];
        } else {
            return variables[i] < other.variables[i];
        }
    }

    return numVariables < other.numVariables;
}
/**
 * Greater than operator
 * @param other term to compare to
 * @return true if this term is greater than other
 */
bool term::operator>(const term &other) const {
    if (*this == other)
        return false;

    if (numVariables == 0)
        return true;

    if (other.numVariables == 0)
        return false;

    int minIndex = min(numVariables, other.numVariables);
    for (int i = 0; i < minIndex; i++) {
        if (variables[i] == other.variables[i]) {
            if (powers[i] != other.powers[i])
                return powers[i] < other.powers[i];
        } else {
            return variables[i] > other.variables[i];
        }
    }

    return numVariables > other.numVariables;
}
/**
 * Get coefficient or Power of variable at index idx
 * @param idx index of variable
 * @return power of variable at index idx.
 *      If idx is out of bounds, return coefficient
 */
int& term::operator[](int idx) {
    if (idx < 0 || idx >= numVariables)
        return coefficient;

    return powers[idx];
}
/**
 * Negate coefficient
 * @return term with coefficient negated
 */
const term term::operator!() const {
    term out = *this;
    out.coefficient *= -1;
    return out;
}
