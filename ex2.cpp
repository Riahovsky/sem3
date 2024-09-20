#include <iostream>


int main() {
    struct Point {
    float const x, y;
    
    Point(float x, float y);
};

struct Triangle {
    Point const A, B, C;
    
    Triangle(Point A, Point B, Point C);
    
    float area() const;
};


    return 0;
}