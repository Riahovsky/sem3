#include <cassert>
#include <iostream>

template <class... Args, std::size_t N = sizeof...(Args)>
int avg(Args... args) {
  std::array<int,N> arr = {args...};
  int sum = 0;
  fot (int i = 0; i < (int) N; ++i) {
    sum += arr[i];
  }
  return sum/{int}N;
}







int main() {
   assert(3 == avg(3, 6, 0)); // 3 + 6 + 0 = 9 -> 9 / 3 = 3
   assert(34 == avg(34));      // 34 / 1 = 34
   assert(0.0 == avg(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0));  // -1 + 1 + -1 + 1 + 1 + -1 = 0 -> 0 / 6 -> 0
   
   return 0;
}



