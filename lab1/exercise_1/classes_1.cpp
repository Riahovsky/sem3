#include <random>
#include <iostream>

class Abstract_Dice {
  public:
  virtual unsigned roll() = 0;

};

class Dice: public Abstract_Dice {
  public:
    Dice(unsigned max, unsigned seed): max(max), dstr(1, max), reng(seed) { }
    unsigned roll() {
      return dstr(reng);
    }
  private:
    unsigned max;
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};
class ThreeDicePool : public Abstract_Dice{
public: 
    Dice d1;
    Dice d2;
    Dice d3;
ThreeDicePool(Dice &d1, Dice &d2, Dice &d3) :d1(d1), d2(d2), d3(d3) {}
unsigned roll() {
  return d1.roll() +d2.roll() +d3.roll() ;
}

};

double expected_value(Abstract_Dice &d, unsigned number_of_rolls = 1000) {
  auto accum = 0llu;
  for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
    accum += d.roll();
  }
  return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}


