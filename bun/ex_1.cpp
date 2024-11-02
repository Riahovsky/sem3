#include <iostream>

using namespace std;

int main() {
    
    class Segment {
        public:
        int a;
        int b;
        Segment();
        Segment(int beging, int end) {
            if (a <= b) {
            a = beging;
            b = end;
            }
            else {
                Segment();
            }
        }
        Segment(int o){
            Segment(0,0);
        }

        bool contains(int p) {
            bool q = false;
            if (a <= p and p >= b) {
                q = true;
            }
            return q;
        }

        void shift(int m) {
            a += m;
            b += m;
        }
    };

    return 0;
}