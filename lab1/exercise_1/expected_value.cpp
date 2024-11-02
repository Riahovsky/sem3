#include "expected_value.h"





double expected_value(Abstract_Dice &d, unsigned number_of_rolls = 1000) {
  auto accum = 0llu;
  for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
    accum += d.roll();
  }
  return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}