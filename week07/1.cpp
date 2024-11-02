#include <iostream>

class DummyArray {
    private:
    size_t size = 0;
    double* ptr = nullptr;
    public:
    DummyArray(size_t size): size(size), ptr(other.ptr) {}
    DummyArray(DummyArray const&& other):size(other.size), ptr(other.ptr) {
        
        
        
    }
    DummyArray& operator = (DummyArray const&& other) {
        DummyArray tmp = DummyArray(other);
        
        return tmp;
    }
    double& operator[](size_t idx) {
        return ptr[idx];
    }
    virtual ~DummyArray() {
        delete[] ptr; 
    }
};

class DerivedDummyArray: public DummyArray {
    private:
    size_t size = 0;
    double* inner_ptr = 0;
    public:
    DerivedDummyArray(size_t size): DummyArray(size), inner_size(size), inner_ptr(new double[size]) {

    }
    virtual ~DerivedDummyArray {

    }
};

int main() {
    int x = 42;
    int&& ref_x  = 2;
    DummyArray arr0{10}; // arr0 = DummyArray(10)
arr0 = std::move(     );
DerivedDummyArray* derived_arr = new DerivedDummyArray(100);
DerivedDummyArray* ptr_derived_arr = derived_arr;
    return 0;
}