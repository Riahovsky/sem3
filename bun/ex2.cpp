#include <iostream> 

class MyOwnClass {};

//void print (MyOwnClass&);

template <typename T>
void print(T obj ) {
    std::cout << obj << std::endl;
}

int main() {
    print<int>(12);
}



































