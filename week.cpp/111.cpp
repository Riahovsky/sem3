#include <iostream>

class  Class {
    public:
        // noexept
    Class() {
    throw std::runtime_error("My own throw")
    }
};

int main() {

    return 0;
}