#include <iostream>
#include "my_math.hpp"

using namespace std;

AnswerHandler my_sin(double x) {
    double a = x-(x*x*x)/6 + (x*x*x*x*x)/120 - (x*x*x*x*x*x*x)/5040;
    cout << "sin " << x << " = " <<  a << endl;
    AnswerHandler result;
    result.x = x;
    result.fun = a;
    
}

void my_cos(double x){
    double a = 1 - (x*x)/2 + (x*x*x*x)/24 - (x*x*x*x*x*x)/720 ; 
    cout << "cos " << x << " = " <<  a << endl;
}

void my_tg(double x){
    double cos_x = 1 - (x*x)/2 + (x*x*x*x)/24 - (x*x*x*x*x*x)/720;
    double sin_x = x-(x*x*x)/6 + (x*x*x*x*x)/120 - (x*x*x*x*x*x*x)/5040;
    double a;
    if (cos_x != 0) {
        a = sin_x/cos_x;
        cout << "tg " << x << " = " <<  a << endl;}
    else {throw "Division by zero" ;}
}

void my_ctg(double x){
   double cos_x = 1 - (x*x)/2 + (x*x*x*x)/24 - (x*x*x*x*x*x)/720;
    double sin_x = x-(x*x*x)/6 + (x*x*x*x*x)/120 - (x*x*x*x*x*x*x)/5040;
    double a;
    if (sin_x != 0) {
        a = cos_x/sin_x;
        cout << "ctg " << x << " = " <<  a << endl;}
    else {throw "Division by zero" ;}
    
    
}
