
#include  "classes_2.cpp"
#include <fstream>


int main() {
  int i = 0;
  Dice t = Dice(100,1);
  std::ofstream file( "Dice.txt" );

double arg_Dice[101] = {0};
arg_Dice[0] = 0;
for (i = 0; i <101;++i) {
  arg_Dice[i] = value_probability(i,t); 

}
for( i=0; i<101; ++i ) 
    {
        file << arg_Dice[i] << std::endl; 
       
    }
    file.close(); 

  return 0;
}

