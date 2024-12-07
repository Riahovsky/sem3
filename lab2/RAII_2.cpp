#include <iostream>

template <typename T>
class Grid final {
public:
	using size_type = unsigned ;
    using value_type = T ;


	// // // // //
	Grid() : data(nullptr), y_size(0), x_size(0) {}

	// // // // // Grid(T const &t)
	Grid(T const& t) : Grid<T>(t, 1, 1) { std::cout << "One" << std::endl; }

	// // // // // Grid(size_type y_size, size_typex_size)
	Grid(size_type y_size, size_type x_size) : Grid<T>(T(), y_size, x_size) { std::cout << "Two" << std::endl; }

	// // // // // Grid(size_type y_size, size_typex_size, T const &t) 
	Grid(size_type y_size, size_type x_size, T const& t) : data(new T[y_size * x_size]), y_size(y_size), x_size(x_size) {
		for (size_type i = 0; i < y_size * x_size; i++) {
			data[i] = t;
		}
		std::cout << "Three" << std::endl;
	}

	// // // // //
	Grid(T* data, size_type y_size, size_type x_size) : data(data), y_size(y_size), x_size(x_size) {}

	// // // // //
	Grid(Grid<T> const& other) : data(new T[other.y_size * other.x_size]), y_size(other.y_size), x_size(other.x_size) {
		for (size_type i = 0; i < y_size * x_size; i++) {
			data[i] = other.data[i];
		}
		std::cout << "Copy" << std::endl;
	}

	// // // // // 
	Grid(Grid<T> const&& other) : data(other.data), y_size(other.y_size), x_size(other.x_size) {
		other.data = nullptr;
        other.y_size = 0;
        other.x_size = 0;
		std::cout << "Move" << std::endl;
	}

	// // // // // 
	~Grid() {
		delete[] data;
		std::cout << "Destructor" << std::endl;
	}

	/// /// /// /// /// 
	Grid<T>& operator=(Grid<T>& other) {
		if (this != other) {
			data = other._data;
			y_size = other._y_size;
			x_size = other._x_size;
		}
		return *this;
		std::cout << "=Copy" << std::endl;
	}

	/// /// /// /// /// 
	Grid<T>& operator=(Grid<T>&& other)  {
		if (this != other) {
			delete[] data;
			data = other._data;
			y_size = other._y_size;
			x_size = other._x_size;
			other.data = nullptr;
            other._y_size = 0;
            other._x_size = 0;
		}
		std::cout << "=Move" << std::endl;
		return *this;
	}

	//// //// //// //// ////
	class Proxy {
	    T* ptr;
        size_type size;
	public:
		Proxy(T* ptr, size_type size) : ptr(ptr), size(size) {}

		T& operator[](size_type idx) {
			return ptr[idx];
		}

		const T& operator[](size_type idx) const {
			return ptr[idx];
		}
	};

	//// //// //// //// ////
	Proxy operator[](size_type idx) {
		return Proxy(data + idx * x_size, x_size);
	}

	const Proxy operator[](size_type idx) const {
		return Proxy(data + idx * x_size, x_size);
	}

	// // // // // (lector's code)
	T operator()(size_type y_idx, size_type x_idx) const {
		return data[y_idx * x_size + x_idx];
	}

	T& operator()(size_type y_idx, size_type x_idx) {
		return data[y_idx * x_size + x_idx];
	}

	// // // // // (for Grid<>)
	Grid<T> operator=(T const& t) {
		for (size_type i = 0; i < y_size * x_size; i++)
			data[i] = t;
		return *this;
	}

	// // // // // //
	size_type get_y_size() const { return y_size; }
	size_type get_x_size() const { return x_size; }
    private:
        T* const data;
        size_type const y_size, x_size;
};
