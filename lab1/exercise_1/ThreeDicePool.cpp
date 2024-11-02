#include "ThreeDicePool.h"



class ThreeDicePool : public Abstract_Dice{
public: 
    Dice& d1;
    Dice& d2;
    Dice& d3;
ThreeDicePool(Dice &d1, Dice &d2, Dice &d3) :d1(d1), d2(d2), d3(d3) {}
unsigned roll() {
  return d1.roll() +d2.roll() +d3.roll() ;
}

};
