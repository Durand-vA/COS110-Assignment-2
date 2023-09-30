
#include "ellipse.h"

bool ellipse::isEllipse() const {
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
    return true;
}

ellipse::ellipse(char c1, char c2) : bivariate(2, c1, c2) {
    degree = 2;
}

ellipse::ellipse(term** t, int n) : bivariate(t, n) {
    degree = 2;
    if (numTerms != 0) {
        if (!isEllipse()) {
            clearTerms();
        }
    }
}

ellipse::ellipse(const char* input) : bivariate(input) {
    degree = 2;
    if (numTerms != 0) {
        if (!isEllipse()) {
            clearTerms();
        }
    }
}

ellipse::ellipse(const ellipse &other) : bivariate(other) {
    degree = 2;
}

ellipse::ellipse(const polynomial &other) : bivariate(other) {
    degree = 2;
    if (numTerms != 0) {
        if (!isEllipse()) {
            clearTerms();
        }
    }
}

ellipse::ellipse(term t) : bivariate(t) {
    degree = 2;
    if (numTerms != 0) {
        if (!isEllipse()) {
            clearTerms();
        }
    }
}

void ellipse::printStats() const {
    if (numTerms == 0) {
        std::cout << "Not a real ellipse\n";
        return;
    }
    double c, d, f;
    c = (*(*this)[0])[-1];
    d = (*(*this)[1])[-1];
    f = (*(*this)[2])[-1];

    if (f >= 0) {
        std::cout << "Not a real circle\n";
        return;
    }

    double a = sqrt(-f/c);
    double b = sqrt(-f/d);

    char c1, c2;

    if (v1 < v2) {
        c1 = v1;
        c2 = v2;
    } else {
        c1 = v2;
        c2 = v1;
    }

    std::cout << "Area = " << std::setprecision(2) << std::fixed << M_PI * a * b
              << "units^2.Perimeter = " << 2 * M_PI * sqrt((a*a + b*b)/2)
              << "units.Intercepts : " << c1 << " = " << a
              << " , " << c1 << " = " << -a << " , " << c2 << " = " << b
              << " , " << c2 << " = " << -b << "\n";

}
