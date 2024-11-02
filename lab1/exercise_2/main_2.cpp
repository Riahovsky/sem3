#include <random>
#include <iostream>
#include <fstream>

class Abstract_Dice
{
public:
  virtual unsigned roll() = 0;
};

class Dice : public Abstract_Dice
{
public:
  Dice(unsigned max, unsigned seed) : max(max), dstr(1, max), reng(seed) {}
  unsigned roll()
  {
    return dstr(reng);
  }

private:
  unsigned max;
  std::uniform_int_distribution<unsigned> dstr;
  std::default_random_engine reng;
};
class ThreeDicePool : public Abstract_Dice
{
public:
  Dice &d1;
  Dice &d2;
  Dice &d3;
  ThreeDicePool(Dice &d1, Dice &d2, Dice &d3) : d1(d1), d2(d2), d3(d3) {}
  unsigned roll() override
  {
    return d1.roll() + d2.roll() + d3.roll();
  }
};

double expected_value(Abstract_Dice &d, unsigned number_of_rolls = 10)
{
  auto accum = 0llu;
  for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
    accum += d.roll();
  return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

class PenaltyDice : public Abstract_Dice
{
public:
  Dice &d1;
  Dice &d2;
  PenaltyDice(Dice &d1, Dice &d2) : d1(d1), d2(d2) {}
  unsigned roll() override
  {
    unsigned A1 = d1.roll();
    unsigned A2 = d2.roll();
    return A1 <= A2 ? A1 : A2;
  }
};

class BonusDice : public Abstract_Dice
{
public:
  Dice &d1;
  Dice &d2;
  BonusDice(Dice &d1, Dice &d2) : d1(d1), d2(d2) {}
  unsigned roll() override
  {
    unsigned B1 = d1.roll();
    unsigned B2 = d2.roll();
    return B1 >= B2 ? B1 : B2;
  }
};

double value_probability(unsigned value, Abstract_Dice &d, unsigned number_of_rolls = 1000000)
{
  auto accum = 0llu;
  int k = 0;
  for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
  {
    accum = d.roll();
    if (accum == value)
    {
      ++k;
    }
  }
  return static_cast<double>(k) / static_cast<double>(number_of_rolls);
}

int main()
{
  int i = 0;
  Dice d1 = Dice(100, 1);
  Dice d2 = Dice(100, 1);

  Dice d11 = Dice(6, 1);
  Dice d22 = Dice(6, 1);
  Dice d33 = Dice(6, 1);
  Dice t = Dice(100, 1);

  BonusDice bonus = BonusDice(d1, d2);
  PenaltyDice penalty = PenaltyDice(d1, d2);
  ThreeDicePool pool = ThreeDicePool(d11, d22, d33);

  std::ofstream fin1("DiceNew.txt");
  for (i = 0; i <= 100; ++i)
  {
    fin1 << value_probability(i, t);
    fin1 << std::endl;
  }
  fin1.close();

  std::ofstream fin2("BonusDiceNew.txt");
  for (i = 0; i <= 100; ++i)
  {
    fin2 << value_probability(i, bonus);
    fin2 << std::endl;
  }
  fin2.close();

  std::ofstream fin3("PenaltyDiceNew.txt");
  for (i = 0; i <= 100; ++i)
  {
    fin3 << value_probability(i, penalty);
    fin3 << std::endl;
  }
  fin3.close();

  std::ofstream fin4("ThreeDicePoolNew.txt");
  for (i = 0; i <= 18; ++i)
  {
    fin4 << value_probability(i, pool);
    fin4 << std::endl;
  }
  fin4.close();

  return 0;
}
