#include "base_classes.cpp"

class  PenaltyDice : public Abstract_Dice {
  public:
  Dice d1;
  Dice d2;
  PenaltyDice(Dice &d1, Dice &d2): d1(d1),d2(d2) {}
  unsigned roll() override{
    unsigned A1 = d1.Dice::roll();
    unsigned A2 = d2.Dice::roll();
    return A1 <= A2 ? A1 : A2 ;
  }
};

class BonusDice : public Abstract_Dice {
  public:
   Dice d1;
   Dice d2;
   BonusDice(Dice &d1, Dice &d2): d1(d1),d2(d2) {}
  unsigned roll() override{
    unsigned B1 = d1.Dice::roll();
    unsigned B2 = d2.Dice::roll();
    return B1 >= B2 ? B1 : B2 ;
  }

};


double value_probability(unsigned value, Abstract_Dice &d, unsigned number_of_rolls = 1000) {
  double probability ;
  int k = 0; unsigned int rl= 0;
  for (int i = number_of_rolls; i > 0; --i) {
    rl = d.roll();
    if (rl == value) {
      ++k;
      }
  }
  probability = static_cast<double>(k) / static_cast<double>(number_of_rolls);
  return probability;
}


