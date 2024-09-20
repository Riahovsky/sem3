#include <iostream>
#include <cmath>
using namespace std;

struct vec3 {
    double x = 0;
    double y = 0;
    double z = 0;
    vec3() {};
    vec3(double X, double Y, double Z) {
        x = X;
        y = Y;
        z = Z;
    }
    void get() {
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "z = " << z << endl;
    }
    double get( int a) {
        if (a == 1) {
            return x;
        }
        else if (a == 2) {
            return y;
        }
        else if (a == 3) {
            return z;
        }
        else {
            return 0;
        }

    }

    void add(double xx, double yy, double zz) {
        
        cout << x+xx << ' ' << y+yy << ' ' << z+zz << endl;
    }

    void sub(double x1, double y1, double z1) {
        cout << x-x1 << ' ' << y-y1 << ' ' << z-z1 << endl;;
    }

    void scale(double q) {
        x *= q;
        y *= q;
        z *= q;
        cout << x << ' ' << y << ' ' << z << endl;;
    }

    double dot(double x2, double y2, double z2) {
        double d = x*x2 +y*y2 + z*z2;
        return d;
        
         }

    void cross(double x3, double y3, double z3) {
        double k1 = y*z3-z*y3;
        double k2 = x3*z - x*z3;
        double k3 = x*y3 - x3*y;
        cout << k1 << ' ' << k2 << ' ' << k3 << endl;
        
         }
    void pint() {
        cout << x << ' ' << y  << ' ' << z << endl;
    }
    void lenght() {
        cout << sqrt(x*x + y*y + z*z)  << endl;
    }

    void length_squared() {
        cout << x*x + y*y + z*z  << endl;
    }
  

};