#include <iostream>

double mean(std::unique_ptr<int[]>& ptr) {
    double mean = 0;
    return 0;
}

double mean(std::shared_ptr<int[12]> ptr) {
    double mean = 0;
    return 0;
}
int main() {
    auto std::make_unique<int[]>(10);
    //auto shared_ptr = std::make_shared<std::unique_ptr<int[]>>(ptr);
    auto shared_ptr = std::make_shared<int[12]>();
    auto 
    void* ptr = ::operator new(12);
    std::cout << sizeof(ptr) <<  std::endl;
    // reinterept_cast<int*>(ptr+idx)
    ptr[0] =12;
    return 0;
}