#include <random>
#include <iostream>
#include <fstream>


 class Abstract_Dice {
  public:
  virtual unsigned roll() = 0;

};

class Dice: public Abstract_Dice {
  public:
    Dice(unsigned max, unsigned seed): max(max), dstr(1, max), reng(seed) { }
    unsigned roll()  {
      return dstr(reng);
    }
  private:
    unsigned max;
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};
class ThreeDicePool : public Abstract_Dice{
public: 
    Dice& d1;
    Dice& d2;
    Dice& d3;
ThreeDicePool(Dice& d1, Dice& d2, Dice& d3) :d1(d1), d2(d2), d3(d3) {}
unsigned roll() override{
  return d1.roll() +d2.roll() +d3.roll() ;
}

};

double expected_value(Abstract_Dice &d, unsigned number_of_rolls = 100) {
  auto accum = 0llu;
  for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
    accum += d.roll();
  return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

class  PenaltyDice : virtual public Abstract_Dice {
  public:
  Dice& d11;
  Dice& d21;
  PenaltyDice(Dice& d11, Dice& d21): d11(d11),d21(d21) {}
  unsigned roll() override{
    unsigned A1 = d11.roll();
    unsigned A2 = d21.roll();
    return A1 <= A2 ? A1 : A2 ;
  }
};

class BonusDice : virtual public Abstract_Dice {
  public:
   Dice& d12;
   Dice& d22;
   BonusDice(Dice& d12, Dice& d22): d12(d12),d22(d22) {}
  unsigned roll() override{
    unsigned B1 = d12.roll();
    unsigned B2 = d22.roll();
    return B1 >= B2 ? B1 : B2 ;
  }

};


double value_probability(unsigned value,Abstract_Dice &d, unsigned number_of_rolls = 1000) {
  auto accum = 0llu;
  int k = 0;
  for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
    accum = d.roll();
    if (accum == value) {
      ++k;
    }
  }
  return static_cast<double>(k) / static_cast<double>(number_of_rolls);
}

class DoubleDice: public PenaltyDice, public BonusDice {
    public:
    DoubleDice(Dice& d): PenaltyDice(d,d) , BonusDice(d,d) { }
    unsigned roll() override {
        return PenaltyDice::roll() + BonusDice::roll();
    }

};


class Another_DoubleDice: public Abstract_Dice {
    public:
    Dice& d;
    BonusDice bonus = BonusDice(d,d);
    PenaltyDice penalty = PenaltyDice(d,d);
    
    Another_DoubleDice(Dice& d): d(d) { }
    unsigned roll() override {
        return bonus.roll() + penalty.roll();
    }

};



int main() {
  int i = 0;
  Dice d = Dice(100,1); 
  
  DoubleDice dd = DoubleDice(d); 
  Another_DoubleDice a_dd = Another_DoubleDice(d);

  for(i = 0; i < 5;++i) {
  std::cout << "Expected value " << expected_value(dd) << std::endl;
  }

std:: ofstream fin("DoubleDice.txt");
   for (i = 0; i <= 201; ++i) {
    fin << value_probability(i, dd) ;
    fin << std::endl;
  }
fin.close();

std::cout << std::endl;
for(i = 0; i < 5;++i) {
std::cout << "Expected value (2) " << expected_value(a_dd) << std::endl;
}


  return 0;
}
