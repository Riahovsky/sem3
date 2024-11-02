#include <iostream>

template <typename T>
class Grid final
{
public:
    using value_type = T;
    using size_type = unsigned;

    // private:
    size_type const y_size;
    size_type const x_size;
     T *data;

    Grid(T *data, size_type y_size, size_type x_size) : data(data), y_size(y_size), x_size(x_size) { }

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
        data = new T[1];
        data[0] = t;
    }
    Grid(size_type y_size, size_type x_size) : y_size(y_size), x_size(x_size), data(static_cast<T*>(::operator new (x_size * y_size * sizeof(T)))) {}

    Grid(size_type y_size, size_type x_size, T const &t) : y_size(y_size), x_size(x_size), data(static_cast<T*>(::operator new (x_size * y_size * sizeof(T))))
    {   
    
        for (int i = 0; i <= ((int)(x_size)-1)*((int)(y_size)-1); ++i)
        {   
                data[i] = t;
            
        }
    }


    Grid()
    {
        Grid(nullptr, 0, 0);
    }



    class GridProxy {
        public:
        T* data_proxy;
        size_type const y_size_p;
        size_type const x_size_p;
        unsigned int y;
        GridProxy(T* data_zero, size_type ysize, size_type xsize, unsigned int y0): data_proxy(data),y_size_p(ysize), x_size_p(xsize),y(y0) {

        }
        T operator[](unsigned int id_x) {
            if (id_x * y < (int)y_size_p*(int)x_size_p){
            return data_proxy[id_x * y];
            }
            else {
                return 0;
            }
        }
        ~GridProxy() {
            delete[] data_proxy;
        }
        };

    GridProxy operator[](unsigned int id_y) {
        return GridProxy(data, y_size, x_size, id_y);
    }
    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }

    ~Grid()
    {
        delete[] data;
    }

};
