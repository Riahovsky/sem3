class Function {
public:
    virtual double operator()(double) const = 0;
    virtual ~Function() { }
};
double dichotomy_sqr(double left, double right, double a, double tolerance) {
    while (right - left > tolerance) {
        auto c = left + (right - left) / 2.;
        if (c * c - a > 0)
            right = c;
        else 
            left = c;
    }
    return (right + left) / 2.;
}

double dichotomy_any(double left, double right, Function const &f, double tolerance) {

}

class  LinearFunction : public Function {
public:
double A = 0;
double B = 0;

LinearFunction(double A, double B): A(A),B(B) {}

virtual double operator()(double x) {
    return A*x + B;
}


};

class QuadraticFunction : public Function {
public:
double A = 0;
double B = 0;
double C = 0;

QuadraticFunction(double A, double B, double C):A(A), B(B), C(C) {}
virtual double operator()(double x ) {
    return A*x*x + B*x + C ;

};

Function* make_linear_function(double a, double b) {
Function* k;

 }

Function* make_quadratic_function(double a, double b, double c) {

}

void delete_function(Function *f) {

}





bool close(double a, double b, double tolerance) {
    return a - tolerance < b and a + tolerance > b;
}

#include<cassert>

int main() {
    Function *f1 = make_linear_function(1., 1.);
    auto f1_root = dichotomy_any(-10., 10., *f1, 0.001);
    assert(close(f1_root, -1., 0.001));
    delete_function(f1);
    
    Function *f2 = make_quadratic_function(1., 0., -1.);
    auto f2_root = dichotomy_any(0., 2., *f2, 0.001);
    assert(close(f2_root, 1., 0.001));
    delete_function(f2);
    
    return 0;
}

