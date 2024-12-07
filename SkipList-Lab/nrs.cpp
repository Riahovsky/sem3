#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <ostream>
#include <random>
#include <type_traits>
#include <utility>
#include <vector>

using namespace std;

template<typename Key,typename T>

class Skip_list {
private:
        struct Skip_node;                                          
        std::vector<Skip_node*> head = std::vector<Skip_node*>(1, nullptr); 
};





