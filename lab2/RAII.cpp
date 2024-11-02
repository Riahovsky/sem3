#include <iostream>

template <typename T>
class Grid final
{
public:
    using value_type = T;
    using size_type = unsigned;

    // private:
    T **data;
    size_type const y_size;
    size_type const x_size;

    Grid(T **data, size_type y_size, size_type x_size) : data(data), y_size(y_size), x_size(x_size) { }

    Grid(Grid<T> const &src) : Grid(src.data, src.y_size, src.x_size) {}
    Grid(Grid<T> &&src) : data(src.data)
    {
        src.data = nullptr;
    }
    Grid<T> &operator=(Grid<T> const &scr)
    {
        Grid<T> tmp(scr);
        std::swap(this->data, tmp.data);
        this->x_size = tmp.x_size;
        this->y_size = tmp.y_size;
    }
    Grid<T> &operator=(Grid<T> &&src)
    {
        Grid<T> tmp(std::move(src));
        std::swap(this->data, src.data);
    }

    Grid<T> &operator()(size_type y_idx, size_type x_idx) const
    {
        return data[y_idx * x_size + x_idx];
    }

    T &operator()(size_type y_idx, size_type x_idx)
    {
        return data[y_idx * x_size + x_idx];
    }

    Grid<T> &operator=(T const &t)
    {
        for (
            auto it = data, end = data + x_size * y_size;
            it != end; ++it)
            *it = t;
        return *this;
    }

    Grid(T const &t) : y_size{1}, x_size{1}
    {
        data = new T*[1];
        data[0] = new T[1];
        data[0][0] = t;
    }
    Grid(size_type y_size, size_type x_size) : y_size(y_size), x_size(x_size)
    {
        data = new T *[x_size];
        for (int k = 0; k < (int)x_size; ++k)
        {
            data[k] = new T[y_size];
        }
        for (int i = 0; i < x_size; ++i)
        {
            for (int j = 0; j < y_size; ++j)
            {
                data[i][j] = T{};
            }
        }
    }

    Grid(size_type y_size, size_type x_size, T const &t) : y_size(y_size), x_size(x_size)
    {
        data = new T *[x_size];
        for (int k = 0; k < (int)x_size; ++k)
        {
            data[k] = new T[y_size];
        }
        // data = data_zero;
        // delete[] data_zero;
        for (int i = 0; i < x_size; ++i)
        {
            for (int j = 0; j < y_size; ++j)
            {
                data[i][j] = t;
            }
        }
    }
    Grid()
    {
        Grid(0, 0, 0);
    }

    T* operator[](unsigned int index) 
    {
        return data[index];
    }


    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }

    ~Grid()
    {
        delete[] data;
    }
};
