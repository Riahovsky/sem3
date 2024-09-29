#include <random>
#include <iostream>

class Abstract_Dice {
  public:
  virtual unsigned roll() = 0;

};

class Dice: public Abstract_Dice {
  public:
    Dice(unsigned max, unsigned seed): max(max), dstr(1, max), reng(seed) { }
    unsigned roll() override{
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
unsigned roll() override{
  return d1.Dice::roll() +d2.Dice::roll() +d3.Dice::roll() ;
}

};

double expected_value(Abstract_Dice &d, unsigned number_of_rolls = 10) {
  auto accum = 0llu;
  for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
    accum += d.roll();
  return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}


