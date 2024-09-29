#include "classes_1.cpp" 


int main() {
  Dice d1 = Dice(2,3);
  Dice d2 = Dice(8,5);
  Dice d3 = Dice(2,9);

ThreeDicePool pool = ThreeDicePool(d1, d2, d3);

  Dice t = Dice(5,9);
  int j;
  for (j = 0; j < 3; ++j) {
   std::cout << "Random Dice " << t.roll() << std::endl;
  }
  std::cout << std::endl; 
  for (j = 0; j < 3; ++j) {
   std::cout << "Random ThreeDicePool " << pool.roll() << std::endl;
  }
  std::cout << std::endl; 
std::cout <<"Expected value for Dice " << expected_value(t) << std::endl;
std::cout <<"Expected value for ThreeDicePool " << expected_value(pool) << std::endl;


  return 0;
}