#ifndef AISD_VAR6_3_VOLGOV_PICTURE_H
#define AISD_VAR6_3_VOLGOV_PICTURE_H

#include <iostream>
#include <vector>

template <typename T>
class picture {
private:
    std::vector<T>matrix;
    int _maxX{}, _maxY{};
public:
    // constructor
    picture(int x, int y);
    // copy constructor
    picture(const picture &pic) = default;
    // destructor
    ~picture() = default;

    // set the value of a pixel
    void set(int x, int y, T value);
    // get the value of a pixel
    T get(int x, int y);

    // operator +
    picture<T> operator+(const picture<T> &pic);
    // operator *
    picture<T> operator*(const picture<T> &pic);
    // operator + but with value
    picture<T> operator+(T value);
    // operator * but with value
    picture<T> operator*(T value);

    // operator !
    picture<T> operator!();
    // operator =
    picture<T> &operator=(const picture<T> &pic) = default;

    // operator <<
    friend std::ostream &operator<<(std::ostream &out, const picture &pic){
        for (int i = 0; i < pic._maxX; ++i) {
            for (int j = 0; j < pic._maxY; ++j) {
                out << pic.matrix[i * pic._maxY + j] << " ";
            }
            out << std::endl;
        }
        return out;
    }
    // operator >>
    friend std::istream &operator>>(std::istream &in, picture &pic){
        for (int i = 0; i < pic._maxX; ++i) {
            for (int j = 0; j < pic._maxY; ++j) {
                in >> pic.matrix[i * pic._maxY + j];
            }
        }
        return in;
    }

    // fill ratio
    double fill_ratio();
    // draw a circle
    static void draw_circle(picture<T> &pic, int x, int y, int radius, T value);

    // const call operator
    T operator()(int x, int y) const;

    // call operator
    T &operator()(int x, int y);

    auto begin() {
        return matrix.begin();
    }
    auto end() {
        return matrix.end();
    }
};

// constructor
template<typename T>
picture<T>::picture(int x, int y) {
    _maxX = x;
    _maxY = y;

    matrix.resize(x * y);
}
template<>
picture<char>::picture(int x, int y) {
    _maxX = x;
    _maxY = y;

    matrix.resize(x * y);
}

// set the value of a pixel
template<typename T>
void picture<T>::set(int x, int y, T value) {
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");
    if(value != 0 && value != 1 && value != '0' && value != '1')
        throw std::invalid_argument("Invalid argument");
    matrix[x * _maxY + y] = value;
}

// get the value of a pixel
template<typename T>
T picture<T>::get(int x, int y) {
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");
    else
        return matrix[x * _maxY + y];
}

// operator +
template<typename T>
picture<T> picture<T>::operator+(const picture<T> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Invalid argument");
    picture<T> result(_maxX, _maxY);
    for (int i = 0; i < _maxX; ++i) {
        for (int j = 0; j < _maxY; ++j) {
            result.matrix[i * _maxY + j] = matrix[i * _maxY + j] + pic.matrix[i * _maxY + j];
        }
    }
    return result;
}

// operator *
template<typename T>
picture<T> picture<T>::operator*(const picture<T> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Invalid argument");
    picture<T> result(_maxX, _maxY);
    for (int i = 0; i < _maxX; ++i) {
        for (int j = 0; j < _maxY; ++j) {
            result.matrix[i * _maxY + j] = matrix[i * _maxY + j] * pic.matrix[i * _maxY + j];
        }
    }
    return result;
}

// operator + with value
template<typename T>
picture<T> picture<T>::operator+(T value) {
    if(value != 0 && value != 1)
        throw std::invalid_argument("Invalid argument");
    picture<T> result(_maxX, _maxY);
    for (int i = 0; i < _maxX; ++i) {
        for (int j = 0; j < _maxY; ++j) {
            result.matrix[i * _maxY + j] = matrix[i * _maxY + j] + value;
        }
    }
    return result;
}

// operator * with value
template<typename T>
picture<T> picture<T>::operator*(T value) {
    if(value != 0 && value != 1)
        throw std::invalid_argument("Invalid argument");
    picture<T> result(_maxX, _maxY);
    for (int i = 0; i < _maxX; ++i) {
        for (int j = 0; j < _maxY; ++j) {
            result.matrix[i * _maxY + j] = matrix[i * _maxY + j] * value;
        }
    }
    return result;
}

// operator !
template<typename T>
picture<T> picture<T>::operator!() {
    picture<T> result(_maxX, _maxY);
    for (int i = 0; i < _maxX; ++i) {
        for (int j = 0; j < _maxY; ++j) {
            result.matrix[i * _maxY + j] = !matrix[i * _maxY + j];
        }
    }
    return result;
}

// fill ratio of the picture
template<typename T>
double picture<T>::fill_ratio() {
    int count = 0;
    for (int i = 0; i < _maxX; ++i) {
        for (int j = 0; j < _maxY; ++j) {
            if(matrix[i * _maxY + j] == 1)
                count++;
        }
    }
    return (double)count / (_maxX * _maxY);
}

// draw a circle
template<typename T>
void picture<T>::draw_circle(picture<T> &pic, int x, int y, int radius, T value) {
    if(x < 0 || x >= pic._maxX || y < 0 || y >= pic._maxY)
        throw std::invalid_argument("Invalid argument");
    for (int i = 0; i < pic._maxX; ++i) {
        for (int j = 0; j < pic._maxY; ++j) {
            if((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius)
                pic.matrix[i * pic._maxY + j] = value;
        }
    }
}

// const call operator
template<typename T>
T picture<T>::operator()(int x, int y) const {
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::invalid_argument("Invalid argument");
    return matrix[x * _maxY + y];
}

// call operator
template<typename T>
T &picture<T>::operator()(int x, int y) {
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::invalid_argument("Invalid argument");
    return matrix[x * _maxY + y];
}


#endif //AISD_VAR6_3_VOLGOV_PICTURE_H
