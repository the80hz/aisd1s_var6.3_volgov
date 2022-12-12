#ifndef AISD_VAR6_3_VOLGOV_PICTURE_H
#define AISD_VAR6_3_VOLGOV_PICTURE_H

#include <iostream>
#include <vector>

template <typename T>
class picture {
private:
    std::vector<T>matrix;
    int _maxX{}, _maxY{};

    auto begin() {
        return matrix.begin();
    }
    auto end() {
        return matrix.end();
    }
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
    T get(int x, int y) const;

    // operator +
    picture<T> operator+(const picture<T> &pic) const;
    // operator *
    picture<T> operator*(const picture<T> &pic) const;
    // operator + but with value
    picture<T> operator+(T value) const;
    // operator * but with value
    picture<T> operator*(T value) const;

    // operator !
    picture<T> operator!() const;
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

    // fill ratio
    double fill_ratio() const;
    // draw a circle
    static void draw_circle(picture<T> &pic, int x, int y, int radius, T value);

    // const call operator
    T operator()(int x, int y) const;

    // call operator
    T &operator()(int x, int y);
};

// constructor
template<typename T>
picture<T>::picture(int x, int y) {
    _maxX = x;
    _maxY = y;
    matrix.resize(x * y); // заполнен нулями
}
template<>
picture<char>::picture(int x, int y) {
    _maxX = x;
    _maxY = y;
    matrix.resize(x * y);
    auto it = matrix.begin();
    for(int i = 0; it != matrix.end(); ++i, ++it)
        *it = '0';
}

// set the value of a pixel
template<typename T>
void picture<T>::set(int x, int y, T value) {
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");
    matrix[x * _maxY + y] = value;
}

// const get the value of a pixel
template<typename T>
T picture<T>::get(int x, int y) const{
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");
    return matrix[x * _maxY + y];
}

// operator +
template<typename T>
picture<T> picture<T>::operator+(const picture<T> &pic) const{
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Invalid argument");
    picture<T> result(_maxX, _maxY);
    auto it1 = matrix.begin();
    auto it2 = pic.matrix.begin();
    auto it3 = result.matrix.begin();
    for(; it1 != matrix.end(); ++it1, ++it2, ++it3)
        *it3 = *it1 + *it2;

    return result;
}
/*
template<>
picture<char> picture<char>::operator+(const picture<char> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Invalid argument");
    picture<char> result(_maxX, _maxY);
    auto it1 = matrix.begin();
    auto it2 = pic.matrix.begin();
    auto it3 = result.matrix.begin();
    for (int i = 0; i < _maxX; ++i) {
        for (int j = 0; j < _maxY; ++j) {
            if(*it1 == '1' || *it2 == '1')
                *it3 = '1';
            else
                *it3 = '0';
            ++it1;
            ++it2;
            ++it3;
        }
    }
    return result;
}*/

// operator *
template<typename T>
picture<T> picture<T>::operator*(const picture<T> &pic) const{
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Invalid argument");
    picture<T> result(_maxX, _maxY);
    auto it1 = matrix.begin();
    auto it2 = pic.matrix.begin();
    auto it3 = result.matrix.begin();
    for (; it1 != matrix.end(); ++it1, ++it2, ++it3)
        *it3 = *it1 * *it2;
    return result;
}
/*
template<>
picture<char> picture<char>::operator*(const picture<char> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Invalid argument");
    picture<char> result(_maxX, _maxY);
    auto it1 = matrix.begin();
    auto it2 = pic.matrix.begin();
    auto it3 = result.matrix.begin();
    for (int i = 0; i < _maxX; ++i) {
        for (int j = 0; j < _maxY; ++j) {
            if(*it1 == '1' && *it2 == '1')
                *it3 = '1';
            else
                *it3 = '0';
            ++it1;
            ++it2;
            ++it3;
        }
    }
    return result;
}*/

// operator + with value
template<typename T>
picture<T> picture<T>::operator+(T value) const{
    picture<T> result(_maxX, _maxY);
    auto it1 = matrix.begin();
    auto it2 = result.matrix.begin();
    for (; it1 != matrix.end(); ++it1, ++it2)
        *it2 = *it1 + value;
    return result;
}
/*
template<>
picture<char> picture<char>::operator+(char value) {
    if(value != '0' && value != '1')
        throw std::invalid_argument("Invalid argument");
    picture<char> result(_maxX, _maxY);
    auto it1 = matrix.begin();
    auto it2 = result.matrix.begin();
    for (int i = 0; i < _maxX; ++i) {
        for (int j = 0; j < _maxY; ++j) {
            if(*it1 == '1' || value == '1')
                *it2 = '1';
            else
                *it2 = '0';
            ++it1;
            ++it2;
        }
    }
    return result;
}*/

// operator * with value
template<typename T>
picture<T> picture<T>::operator*(T value) const{
    picture<T> result(_maxX, _maxY);
    auto it1 = matrix.begin();
    auto it2 = result.matrix.begin();
    for (; it1 != matrix.end(); ++it1, ++it2)
        *it2 = *it1 * value;
    return result;
}
/*
template<>
picture<char> picture<char>::operator*(char value) {
    if(value != '0' && value != '1')
        throw std::invalid_argument("Invalid argument");
    picture<char> result(_maxX, _maxY);
    auto it1 = matrix.begin();
    auto it2 = result.matrix.begin();
    for (int i = 0; i < _maxX; ++i) {
        for (int j = 0; j < _maxY; ++j) {
            if(*it1 == '1' && value == '1')
                *it2 = '1';
            else
                *it2 = '0';
            ++it1;
            ++it2;
        }
    }
    return result;
}*/

// operator !
template<typename T>
picture<T> picture<T>::operator!() const{
    picture<T> result(_maxX, _maxY);
    auto it1 = matrix.begin();
    auto it2 = result.matrix.begin();
    for (int i = 0; i < _maxX; ++i) {
        for (int j = 0; j < _maxY; ++j) {
            if(*it1 == 1)
                *it2 = 0;
            else
                *it2 = 1;
            ++it1;
            ++it2;
        }
    }
    return result;
}
template<>
picture<char> picture<char>::operator!() const{
    picture<char> result(_maxX, _maxY);
    auto it1 = matrix.begin();
    auto it2 = result.matrix.begin();
    for (int i = 0; i < _maxX; ++i) {
        for (int j = 0; j < _maxY; ++j) {
            if(*it1 == '1')
                *it2 = '0';
            else
                *it2 = '1';
            ++it1;
            ++it2;
        }
    }
    return result;
}

// fill ratio of the picture
template<typename T>
double picture<T>::fill_ratio() const{
    int count = 0;
    auto it = matrix.begin();
    for (int i = 0; i < _maxX; ++i)
        for (int j = 0; j < _maxY; ++j) {
            if(*it != 0 && *it != '0')
                ++count;
            ++it;
        }
    return (double)count / (_maxX * _maxY);
}

// draw a circle
template<typename T>
void picture<T>::draw_circle(picture<T> &pic, int x, int y, int radius, T value) {
    if(x < 0 || x >= pic._maxX || y < 0 || y >= pic._maxY)
        throw std::invalid_argument("Invalid argument");
    auto it = pic.matrix.begin();
    for (int i = 0; i < pic._maxX; ++i)
        for (int j = 0; j < pic._maxY; ++j) {
            if((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius)
                *it = value;
            ++it;
        }
}

// const call operator
template<typename T>
T picture<T>::operator()(int x, int y) const{
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
