#include "Dice.h"

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