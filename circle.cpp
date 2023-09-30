#include "circle.h"

bool circle::isCircle() const {
    if (!this->isBivariate()) {
        return false;
    }
    if (this->getNumTerms() != 3) {
        return false;
    }
    if ((*this)[0]->getDegree() != 2) {
        return false;
    }
    if ((*this)[1]->getDegree() != 2) {
        return false;
    }
    if ((*this)[2]->getDegree() != 0) {
        return false;
    }
    if ((*(*this)[0])[-1] != (*(*this)[1])[-1]) {
        return false;
    }
    return true;
}

circle::circle(char c1, char c2) : bivariate(2, c1, c2) {
}

circle::circle(term** t, int n) : bivariate(t, n) {
    degree = 2;
    if (numTerms != 0) {
        if (!isCircle()) {
            clearTerms();
        }
    }
}

circle::circle(const char* input) : bivariate(input) {
    degree = 2;
    if (numTerms != 0) {
        if (!isCircle()) {
            clearTerms();
        }
    }
}

circle::circle(const circle &other) : bivariate(other) {
    degree = 2;
//    if (numTerms != 0) {
//        if (!isCircle()) {
//            clearTerms();
//        }
//    }
}

circle::circle(const polynomial &other) : bivariate(other) {
    degree = 2;
    if (numTerms != 0) {
        if (!isCircle()) {
            clearTerms();
        }
    }
}

circle::circle(term t) : bivariate(t) {
    degree = 2;
    if (numTerms != 0) {
        if (!isCircle()) {
            clearTerms();
        }
    }
}

void circle::printStats() const {
    if (numTerms == 0) {
        std::cout << "Not a real circle\n";
        return;
    }
    double c, d, f;
    c = (*(*this)[0])[-1];
    f = (*(*this)[2])[-1];

    if (f >= 0) {
        std::cout << "Not a real circle\n";
        return;
    }

    double r = sqrt(-f/c);

    char c1, c2;

    if (v1 < v2) {
        c1 = v1;
        c2 = v2;
    } else {
        c1 = v2;
        c2 = v1;
    }

    std::cout << "Area = " << std::setprecision(2) << std::fixed << M_PI * r * r
                << "units^2.Perimeter = " << 2 * M_PI * r
                << "units.Intercepts : " << c1 << " = " << r
                << " , " << c1 << " = " << -r << " , " << c2 << " = " << r
                << " , " << c2 << " = " << -r << "\n";
}
