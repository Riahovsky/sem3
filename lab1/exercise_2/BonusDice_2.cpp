#include  "classes_2.cpp"
#include <fstream>




int main() {
  Dice d1 = Dice(100,1);
  Dice d2 = Dice(100,1);

  BonusDice bonus = BonusDice(d1,d2);
  int i = 0;
  double arg_BonusDice[101];

std::ofstream file( "BonusDice.txt" );
for (i = 0; i < 101;++i) {
  arg_BonusDice[i] = value_probability(i,bonus);
}
for( i=0; i<101; ++i ) 
    {
        file << arg_BonusDice[i] << std::endl; 
       
    }
    file.close(); 


  return 0;
}