#include <iostream>

template <typename T>
void print(double v0) {

}

template <typename HEAD, typename... TAIL>
void print(HEAD head, TAIL... tail) {
    std::cout << head << std::endl;
    print(tail...);
}

template <typename T> 
class unique_ptr {
    private:
        T* m_ptr;
    public:
        unique_ptr<T>(T& obj);
        unique_ptr<T>(my_unique_ptr<T>&& other);
        unique_ptr(unique_ptr<T> const&) = delete;
        unique_ptr<T> operator=(unique_ptr<T> const&) = delete;
        unique_ptr<T>  operator=(unique_ptr<T>&& other) = delete;
        ~my_unique_ptr
};


int main(){

}