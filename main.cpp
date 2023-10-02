#include <iostream>

#include "term.h"
#include "polynomial.h"
#include "univariate.h"
#include "bivariate.h"
#include "quadratic.h"
#include "linear.h"
#include "circle.h"
#include "ellipse.h"

void termTest() {
    //// Term test
    term term1("2*x^2*y^3*z^4");
    std::cout << term1;
    std::cout << "\n";

    //// Initialize variables and values for operator() overload
    char* vars = new char[2];
    int* vals = new int[2];

    vars[0] = 'x';
    vars[1] = 'a';

    vals[0] = 2;
    vals[1] = 0;

    //// Test operator() using char* and int*
    std::cout << term1(vars, vals, 2);
    std::cout << term1("x=2 a=0");
    std::cout << "\n";

    std::string inputs[] = {"+8*x*x^1*x^0*x^-1", "1*x^2",
                            "-x^2", "0*x^2", "+z^-3"};
    //// Test parameterized constructor using string
    term term2 = term(inputs[0].c_str());
    std::cout << term2;
    term2 = term(inputs[1].c_str());
    std::cout << term2;
    term2 = term(inputs[2].c_str());
    std::cout << term2;
    term2 = term(inputs[3].c_str());
    std::cout << term2;
    term2 = term(inputs[4].c_str());
    std::cout << term2;
    std::cout << "\n";

    //// Test default constructor
    term term3;

    //// Test parameterized constructor
    term term4(10, 2, vars, vals);

    //// Text self assignment
    term4 = term4;

    //// Test getters
    char* v = term4.getVariables();
    int n = term4.getNumVariables();
    for (int i = 0; i < n; i++) {
        std::cout << v[i];
    }
    std::cout << "\n";

    std::cout << term4.getDegree() << "\n";
    std::cout << "\n";

    term term5;


    term term6;
    for (int i = 0; i < 5; i++) {
        std::cout << "Insertion operator " << inputs[i] << ": \n";

        std::stringstream ss;
        ss << inputs[i];
        ss >> term6;
        std::cout << term6;
    }

    std::cout << "\n";

    std::stringstream ss;
    ss << "+8*x*x^1*x^0*x^-1";
    ss >> term5;

    std::cout << "*\n";
    std::cout << term5 * term4 << "\n";

    std::cout << "*=\n";
    term5 *= term4;
    std::cout << term5;

    term5 == term4;
    term5 < term4;
    term5 > term4;

    term() < term5;
    term() > term5;
    term5 < term();
    term5 > term();
    term5 > term5;
    term5 < term5;

    std::cout << term5[0] << "\n";
    std::cout << term5[-1] << "\n";

    std::cout << !term5;

    std::cout << "\n Multiplication Test\n";

    term multi1("2*x^2*y*z");
    term multi2("2*x^2*y^5*a*b");

    term multi = (multi1 * multi2);

    std::cout << "2*x^2*y*z * 2*x^2*y^5*a*b = \n"
                << multi;

    std::cout << "Substitution:\n" << multi(vars, vals, 2);


    //// Delete all dynamic memory
    delete[] vars;
    delete[] vals;
}

void univariateTest() {
    //// Univariate test
    term** terms1 = new term*[5];
    terms1[0] = new term("2*x^2");
    terms1[1] = new term("3*x^0");
    terms1[2] = new term("4*x^1");
    terms1[3] = new term("5*x^4");
    terms1[4] = new term("6*x^3");
    term** terms2 = new term*[5];
    terms2[0] = new term("2*x^3");
    terms2[1] = new term("3*x^4");
    terms2[2] = new term("4*x^3");
    terms2[3] = new term("5*x^5");
    terms2[4] = new term("6*x^6");
    term** terms3 = new term*[5];
    terms3[0] = new term("2*y^2");
    terms3[1] = new term("3*y^0");
    terms3[2] = new term("4*y^1");
    terms3[3] = new term("5*y^4");
    terms3[4] = new term("6*y^3");
    term** terms4 = new term*[5];
    terms4[0] = new term("2*y^2");
    terms4[1] = new term("3*x^0");
    terms4[2] = new term("4*z^1");
    terms4[3] = new term("5*a^4");
    terms4[4] = new term("6*y^3");

    //// Test default constructor
    univariate defaultcon(1, 'c');

    //// Test parameterized constructor
    univariate uni1(terms1, 5);
    std::cout << "uni1: \n";
    std::cout << uni1;
    univariate uni2(terms2, 5);
    std::cout << "uni2: \n";
    std::cout << uni2;
    univariate uni3(terms3, 5);
    std::cout << "uni3: \n";
    std::cout << uni3;
    univariate uni4(terms4, 5);
    std::cout << "uni4: \n";
    std::cout << uni4 << '\n';


    //// Test copy constructor
    univariate uni5(uni1);
    std::cout << "uni5: \n";
    std::cout << uni5 << '\n';

    //// Test parameterized constructor taking a string
    univariate uni6("2*x^2 + -3*x^0 - 4*x^1 + 5*x^4 + 6*x^3");
    std::cout << "uni6: \n";
    std::cout << uni6;

    //// Test parameterized constructor taking an empty string
    univariate uni7("");
    std::cout << "uni7: \n";
    std::cout << uni7 << '\n';

    //// Test parameterized constructor taking a single term
    univariate uni8(*terms1[0]);
    std::cout << "uni8: \n";
    std::cout << uni8 << '\n';

    //// Test assignment operator
    uni5 = uni5;
    univariate temp1 = uni5;
    uni5 = uni3;
    std::cout << "uni5 (uni3): \n";
    std::cout << uni5;
    uni5 = temp1;
    std::cout << "uni5: \n";
    std::cout << uni5 << '\n';

    //// Test extraction operator
    stringstream ss("2*x^2 + -3*x^0 + 4*x^1 - 5*x^4 - 6*x^-3");
    ss >> uni7;
    std::cout << "uni7: \n";
    std::cout << uni7 << '\n';

    //// Test removing term from polynomial
    univariate uni9("2*x^3 + -3*x^0 + 2*x^1 - 2*x^1 + 4*x^2 + 5*x^5 + 6*x^4");
    std::cout << "uni9: \n";
    std::cout << uni9;

    uni9.getTerms();
    uni9.getNumTerms();

    uni9[0];
    uni9[-1];
    *uni6[1] = *terms1[0];

    univariate uni10("2*x^3*y + -3*x^0 + 2*x^1 - 2*x^1 + 4*x^2 + 5*x^5 + 6*x^4");
    std::cout << "uni10: \n";
    std::cout << uni10;

    univariate uni11((term("2*x^3*y")));
    std::cout << "uni11: \n";
    std::cout << uni11;

    polynomial* temp;

    std::cout << "Negation: \n";
    temp = !uni9;
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    char* vars = new char[2];
    int* vals = new int[2];

    vars[0] = 'x';
    vars[1] = 'a';

    vals[0] = 2;
    vals[1] = 0;

    std::cout << "Substitution with char and int arrays: \n";
    temp = uni9(vars, vals, 2);
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    // Delete dynamic memory
    delete[] vars;
    delete[] vals;

    std::cout << "Substitution with string: \n";
    temp = uni9("x=2 a=0");
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    std::cout << "Addition: \n";
    temp = (uni9 + uni1);
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    uni9 += uni1;
    std::cout << "Addition assignment: \n";
    std::cout << uni9 << '\n';

    std::cout << "Subtraction: \n";
    temp = (uni9 - uni1);
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    uni9 -= uni1;
    std::cout << "Subtraction assignment: \n";
    std::cout << uni9 << '\n';

    std::cout << "Multiplication: \n";
    temp = (uni9 * uni1);
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    univariate uni9Copy(uni9);
    uni9Copy *= uni1;
    std::cout << "Multiplication assignment: \n";
    std::cout << uni9Copy << '\n';

    std::cout << "Multiplication with multiple variables: \n";
    temp = (uni9 * uni3);
    std::cout << *temp << '\n';
    delete temp;

    uni9 *= uni3;
    std::cout << "Multiplication assignment with multiple variables: \n";
    std::cout << uni9 << '\n';

    // Delete all dynamic memory
    for (int i = 0; i < 5; i++) {
        delete terms1[i];
        delete terms2[i];
        delete terms3[i];
        delete terms4[i];
    }
    delete[] terms1;
    delete[] terms2;
    delete[] terms3;
    delete[] terms4;

    univariate multi1("2*x^2 + 3*x - 4");
    univariate multi2("2*x^2 + 3*x - 4");
    univariate multi3("5*y^2 + 4*y - 2");
    univariate multi4("5");

    polynomial* m12 = multi1 * multi2;
    polynomial* m13 = multi1 * multi3;
    polynomial* m14 = multi1 * multi4;
    polynomial* m34 = multi3 * multi4;

    std::string s12, s13, s14, s34;
    std::stringstream ss1;
    ss1 << *m12;
    std::getline(ss1, s12);

    ss1 << *m13;
    std::getline(ss1, s13);

    ss1 << *m14;
    std::getline(ss1, s14);

    ss1 << *m34;
    std::getline(ss1, s34);

    if (s12 != "4*x^4 + 12*x^3 + -7*x^2 + -24*x + 16") {
        std::cout << "Error in multiplication of m1 and m2\n";
        std::cout << s12 << '\n';
    }
    if (s13 != "-4*x^2 + 10*x^2*y^2 + 8*x^2*y + -6*x + 15*x*y^2 + 12*x*y + -20*y^2 + -16*y + 8") {
        std::cout << "Error in multiplication of m1 and m3\n";
        std::cout << s13 << '\n';
    }
    if (s14 != "10*x^2 + 15*x + -20") {
        std::cout << "Error in multiplication of m1 and m4\n";
        std::cout << s14 << '\n';
    }
    if (s34 != "25*y^2 + 20*y + -10") {
        std::cout << "Error in multiplication of m3 and m4\n";
        std::cout << s34 << '\n';
    }

    delete m12;
    delete m13;
    delete m14;
    delete m34;
}

void bivariateTest() {
    //// Bivariate test
    term** terms1 = new term*[5];
    terms1[0] = new term("2*x^2*y^2");
    terms1[1] = new term("3*x^0*y^0");
    terms1[2] = new term("4*x^1*y^1");
    terms1[3] = new term("5*x^4*y^4");
    terms1[4] = new term("6*x^3*y^3");
    term** terms2 = new term*[5];
    terms2[0] = new term("2*x^3*y^3");
    terms2[1] = new term("3*x^4*y^4");
    terms2[2] = new term("4*x^3*y^3");
    terms2[3] = new term("5*x^5*y^5");
    terms2[4] = new term("6*x^6*y^6");
    term** terms3 = new term*[5];
    terms3[0] = new term("2*y^2*z^2");
    terms3[1] = new term("3*y^0*z^0");
    terms3[2] = new term("4*y^1*z^1");
    terms3[3] = new term("5*y^4*z^4");
    terms3[4] = new term("6*y^3*z^3");
    term** terms4 = new term*[5];
    terms4[0] = new term("2*y^2*z^2");
    terms4[1] = new term("3*x^0*y^0");
    terms4[2] = new term("4*z^1*y^1");
    terms4[3] = new term("5*a^4*y^4");
    terms4[4] = new term("6*y^3*z^3");

    //// Test default constructor
    bivariate defaultcon(1, 'c', 'a');

    //// Test parameterized constructor
    bivariate biv1(terms1, 5);
    std::cout << "biv1: \n";
    std::cout << biv1;
    bivariate biv2(terms2, 5);
    std::cout << "biv2: \n";
    std::cout << biv2;
    bivariate biv3(terms3, 5);
    std::cout << "biv3: \n";
    std::cout << biv3;
    bivariate biv4(terms4, 5);
    std::cout << "biv4: \n";
    std::cout << biv4 << '\n';


    //// Test copy constructor
    bivariate biv5(biv1);
    std::cout << "biv5: \n";
    std::cout << biv5 << '\n';

    //// Test parameterized constructor taking a string
    bivariate biv6("2*x^2 + -3*x^0 - 4*x^1 + 5*x^4 + 6*x^3");
    std::cout << "biv6: \n";
    std::cout << biv6;

    //// Test parameterized constructor taking an empty string
    bivariate biv7("");
    std::cout << "biv7: \n";
    std::cout << biv7 << '\n';

    //// Test parameterized constructor taking a single term
    bivariate biv8(*terms1[0]);
    std::cout << "biv8: \n";
    std::cout << biv8 << '\n';

    //// Test assignment operator
    biv5 = biv5;
    bivariate tempBi = biv5;
    biv5 = biv3;
    std::cout << "biv5 (biv3): \n";
    std::cout << biv5;
    biv5 = tempBi;
    std::cout << "biv5: \n";
    std::cout << biv5 << '\n';

    //// Test extraction operator
    stringstream ss("2*x^2*y^2 + -3*x^0 + 4*x^1 - 5*x^4 - 6*x^-3");
    ss >> biv7;
    std::cout << "biv7: \n";
    std::cout << biv7 << '\n';

    //// Test removing term from polynomial
    bivariate biv9("2*x^3 + -3*x^0 + 2*x^1 - 2*x^1 + 4*x^2 + 5*x^5 + 6*x^4");
    std::cout << "biv9: \n";
    std::cout << biv9;

    biv9.getTerms();
    biv9.getNumTerms();

    biv9[0];
    biv9[-1];
    *biv6[1] = *terms1[0];

    bivariate biv10("2*x^3*y + -3*x^0 + 2*x^1 - 2*x^1 + 4*x^2 + 5*x^5 + 6*x^4");
    std::cout << "biv10: \n";
    std::cout << biv10;

    bivariate biv11((term("2*x^3*y")));
    std::cout << "biv11: \n";
    std::cout << biv11;

    polynomial* temp;

    std::cout << "Negation: \n";
    temp = !biv9;
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    char* vars = new char[2];
    int* vals = new int[2];

    vars[0] = 'x';
    vars[1] = 'a';

    vals[0] = 2;
    vals[1] = 0;

    std::cout << "Substitution with char and int arrays: \n";
    temp = biv9(vars, vals, 2);
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    // Delete dynamic memory
//    for (int i = 0; i < 2; i++) {
//        delete vars[i];
//        delete vals[i];
//    }
    delete [] vars;
    delete [] vals;


    std::cout << "Substitution with string: \n";
    temp = biv9("x=2 a=0");
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    std::cout << "Addition: \n";
    temp = (biv9 + biv1);
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    biv9 += biv1;
    std::cout << "Addition assignment: \n";
    std::cout << biv9 << '\n';

    std::cout << "Subtraction: \n";
    temp = (biv9 - biv1);
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    biv9 -= biv1;
    std::cout << "Subtraction assignment: \n";
    std::cout << biv9 << '\n';

    std::cout << "Multiplication: \n";
    temp = (biv9 * biv1);
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    bivariate biv9Copy(biv9);
    biv9Copy *= biv1;
    std::cout << "Multiplication assignment: \n";
    std::cout << biv9Copy << '\n';

    std::cout << "Multiplication with multiple variables: \n";
    temp = (biv9 * biv3);
    std::cout << *temp << '\n';
    delete temp;
    temp = NULL;

    biv9 *= biv3;
    std::cout << "Multiplication assignment with multiple variables: \n";
    std::cout << biv9 << '\n';

    // Delete all dynamic memory
    for (int i = 0; i < 5; i++) {
        delete terms1[i];
        delete terms2[i];
        delete terms3[i];
        delete terms4[i];
    }
    delete[] terms1;
    delete[] terms2;
    delete[] terms3;
    delete[] terms4;

}

void quadraticTest() {
    quadratic quad('c');

    term** terms = new term*[3];
    terms[0] = new term("2*x^2");
    terms[1] = new term("3*x^1");
    terms[2] = new term("-10");

    quadratic quad1(terms, 3);

    term** term2 = new term*[3];
    term2[0] = new term("2*x^2");
    term2[1] = new term("3*x^3");
    term2[2] = new term("4");

    quadratic quad2(terms, 3);
    quadratic quad2Not(term2, 3);

    quadratic quad4("1*x^2 + -2*x^1");
    quadratic quad4Not("1*x^2 + -2*x^3 + 1");

    quadratic quad5(quad4);

    univariate uni6("1*x^2 + -2*x^1 + 1");
    univariate uni6Not("1*x^2 + -2*x^3 + 1");

    quadratic quad6(uni6);
    quadratic quad6Not(uni6Not);

    term t("1*x^2");
    term tNot("-2*x^3");

    quadratic quad7(t);
    quadratic quad7Not(tNot);

    std::cout << "quad1: " << quad1;
    quad1.printRoots();

    std::cout << "quad4: " << quad4;
    quad4.printRoots();

    quadratic lin("1*x^1 + 2");

    std::cout << "lin: " << lin;
    lin.printRoots();

    std::cout << '\n';

    // Delete dynamic memory
    for (int i = 0; i < 3; i++) {
        delete terms[i];
        delete term2[i];
    }
    delete [] terms;
    delete [] term2;

}

void linearTest() {
    linear lin('c');

    term** terms = new term*[2];
    terms[0] = new term("3*x^1");
    terms[1] = new term("1");

    linear lin1(terms, 2);

    term** term2 = new term*[2];
    term2[0] = new term("3*x^3");
    term2[1] = new term("4");

    linear lin2(terms, 2);
    linear lin2Not(term2, 2);

    linear lin4("-2*x^1 + 2");
    linear lin4Not("-2*x^3 + 1");

    linear lin5(lin4);

    univariate uni6("-2*x^1 + 1");
    univariate uni6Not("-2*x^3 + 1");

    linear lin6(uni6);
    linear lin6Not(uni6Not);

    term t("1*x^1");
    term tNot("-2*x^3");

    linear lin7(t);
    linear lin7Not(tNot);

    std::cout << lin1;
    lin1.printRoots();

    std::cout << lin4;
    lin4.printRoots();

    std::cout << lin;
    lin.printRoots();

    term t0(0, 0, NULL, NULL);

    linear lin8(t0);

    std::cout << lin8;
    lin8.printRoots();

    linear lin9("2*x - 1");
    lin9.printRoots();

    // Delete dynamic memory
    for (int i = 0; i < 2; i++) {
        delete terms[i];
        delete term2[i];
    }
    delete [] terms;
    delete [] term2;

}

void circleTest() {
    circle cir('c', 'y');

    //// Valid circle
    term** terms = new term*[3];
    terms[0] = new term("2*x^2");
    terms[1] = new term("2*y^2");
    terms[2] = new term("-1");

    circle cir1(terms, 3);

    std::cout << "Circle 1:\n" << cir1 << '\n';

    //// Invalid circle
    term** termsNot = new term*[3];
    termsNot[0] = new term("2*x^1");
    termsNot[1] = new term("3*y^1");
    termsNot[2] = new term("4");

    circle cir1Not(termsNot, 3);

    circle cir4("1*x^2 + 1*y^2 + -2");
    circle cir4Not("1*x^3 + 2*y^2 + 1");

    circle cir5(cir4);

    bivariate bi6("1*x^2 + 2*y^3");
    std::cout << bi6;
    bivariate bi6Not("1*x^2 + 2*y^2 + 1*x");
    bivariate bi6Not2("1*x^2 + -2*x^3 + 1 + 2*y^2");
    bivariate bi6Not3("1*x^2 + -2*y^2 + 1");

    circle cir6(bi6);
    circle cir6Not(bi6Not);
    circle cir6Not2(bi6Not2);
    circle cir6Not3(bi6Not3);

    term t("1*x^2");
    term tNot("-2*x^3");

    circle cir7(t);
    circle cir7Not(tNot);
    //// Done testing constructors


    std::cout << '\n' << "Circle 1:\n" << cir1;
    cir1.printStats();

    std::cout << '\n' << "Circle 4:\n" << cir4;
    cir4.printStats();

    std::cout << '\n' << "Circle:\n" << cir;
    cir.printStats();

    term t0(0, 0, NULL, NULL);

    circle cir8(t0);

    std::cout << "Circle 8:\n" << cir8 << '\n';
    cir8.printStats();

    // Delete dynamic memory
    for (int i = 0; i < 3; i++) {
        delete terms[i];
        delete termsNot[i];
    }
    delete [] terms;
    delete [] termsNot;

}

void ellipseTest() {
    ellipse ell('c', 'y');

    //// Valid ellipse
    term** terms = new term*[3];
    terms[0] = new term("2*x^2");
    terms[1] = new term("3*y^2");
    terms[2] = new term("-1");

    ellipse ell1(terms, 3);

    std::cout << "ellipse 1:\n" << ell1 << '\n';

    //// Invalid ellipse
    term** termsNot = new term*[3];
    termsNot[0] = new term("2*x^1");
    termsNot[1] = new term("3*y^1");
    termsNot[2] = new term("4");

    ellipse ell1Not(termsNot, 3);

    ellipse ell4("1*x^2 + 1*y^2 + -2");
    ellipse ell4Not("1*x^3 + 2*y^2 + 1");

    ellipse ell5(ell4);

    bivariate bi6("1*x^2 + 2*y^3");
    std::cout << bi6;
    bivariate bi6Not("1*x^2 + 2*y^2 + 1*x");
    bivariate bi6Not2("1*x^2 + -2*x^3 + 1 + 2*y^2");
    bivariate bi6Not3("1*x^2 + -2*y^2 + 1");

    ellipse ell6(bi6);
    ellipse ell6Not(bi6Not);
    ellipse ell6Not2(bi6Not2);
    ellipse ell6Not3(bi6Not3);

    term t("1*x^2");
    term tNot("-2*x^3");

    ellipse ell7(t);
    ellipse ell7Not(tNot);
    //// Done testing constructors


    std::cout << '\n' << "ellipse 1:\n" << ell1;
    ell1.printStats();

    std::cout << '\n' << "ellipse 4:\n" << ell4;
    ell4.printStats();

    std::cout << '\n' << "ellipse:\n" << ell;
    ell.printStats();

    term t0(0, 0, NULL, NULL);

    ellipse ell8(t0);

    std::cout << "ellipse 8:\n" << ell8 << '\n';
    ell8.printStats();

    // Delete dynamic memory
    for (int i = 0; i < 3; i++) {
        delete terms[i];
        delete termsNot[i];
    }
    delete [] terms;
    delete [] termsNot;

}

int main() {
//    termTest();
    univariateTest();
//    bivariateTest();
//    quadraticTest();
//    linearTest();
//    circleTest();
//    ellipseTest();
    return 0;
}
