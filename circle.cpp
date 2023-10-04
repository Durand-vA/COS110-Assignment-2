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

    circle* cir = new circle(*this);

    int prevNTerms = cir->numTerms;
    cir->addOrRemoveTerm(term0);
    if (cir->numTerms < prevNTerms) {
        term* nTerm0 = new term(!(*term0));
        cir->addOrRemoveTerm(nTerm0);
        delete nTerm0;
    } else {
        (*(*cir)[0])[-1]--;
    }

    prevNTerms = cir->numTerms;
    cir->addOrRemoveTerm(term1);
    if (cir->numTerms < prevNTerms) {
        term* nTerm1 = new term(!(*term1));
        cir->addOrRemoveTerm(nTerm1);
        delete nTerm1;
    } else {
        (*(*cir)[1])[-1]--;
    }

    prevNTerms = cir->numTerms;
    cir->addOrRemoveTerm(term2);
    if (cir->numTerms < prevNTerms) {
        term* nTerm2 = new term(!(*term2));
        cir->addOrRemoveTerm(nTerm2);
        delete nTerm2;
    } else {
        (*(*cir)[2])[-1]--;
    }

    // Delete the terms
    delete term0;
    delete term1;
    delete term2;

    if (!cir->isCircle()) {
        std::cout << "Not a real circle\n";
        return;
    }

    double c, f;
    c = (*(*cir)[0])[-1];
    f = (*(*cir)[2])[-1];

    delete cir;

    if (f >= 0 || c <= 0) {
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
                << " units^2.Perimeter = " << 2 * M_PI * r
                << " units.Intercepts : " << c1 << " = " << r
                << " , " << c1 << " = " << -r << " , " << c2 << " = " << r
                << " , " << c2 << " = " << -r << "\n";
}
