
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
    char* inp = new char[4];
    inp[0] = v1;
    inp[1] = '^';
    inp[2] = '2';
    inp[3] = '\0';

    term* term0 = new term(inp);
    inp[0] = v2;
    term* term1 = new term(inp);
    term* term2 = new term("1");

    delete [] inp;

    ellipse* ell = new ellipse(*this);

    int prevNTerms = ell->numTerms;
    ell->addOrRemoveTerm(term0);
    if (ell->numTerms < prevNTerms) {
        term* nTerm0 = new term(!(*term0));
        ell->addOrRemoveTerm(nTerm0);
        delete nTerm0;
    } else {
        (*(*ell)[0])[-1]--;
    }

    prevNTerms = ell->numTerms;
    ell->addOrRemoveTerm(term1);
    if (ell->numTerms < prevNTerms) {
        term* nTerm1 = new term(!(*term1));
        ell->addOrRemoveTerm(nTerm1);
        delete nTerm1;
    } else {
        (*(*ell)[1])[-1]--;
    }

    prevNTerms = ell->numTerms;
    ell->addOrRemoveTerm(term2);
    if (ell->numTerms < prevNTerms) {
        term* nTerm2 = new term(!(*term2));
        ell->addOrRemoveTerm(nTerm2);
        delete nTerm2;
    } else {
        (*(*ell)[2])[-1]--;
    }

    // Delete the terms
    delete term0;
    delete term1;
    delete term2;

    if (!ell->isEllipse()) {
        std::cout << "Not a real ellipse\n";
        return;
    }

    double c, d, f;
    c = (*(*ell)[0])[-1];
    d = (*(*ell)[1])[-1];
    f = (*(*ell)[2])[-1];

    delete ell;

    if (f >= 0 || c <= 0 || d <= 0) {
        std::cout << "Not a real ellipse\n";
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
              << " units^2.Perimeter = " << 2 * M_PI * sqrt((a*a + b*b)/2)
              << " units.Intercepts : " << c1 << " = " << a
              << " , " << c1 << " = " << -a << " , " << c2 << " = " << b
              << " , " << c2 << " = " << -b << "\n";

}
