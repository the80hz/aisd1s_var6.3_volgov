#ifndef AISD_VAR6_3_VOLGOV_PICTURE_H
#define AISD_VAR6_3_VOLGOV_PICTURE_H

#include <iostream>
#include <vector>

template <typename T>
class picture {
private:
    std::vector<std::vector<T>> matrix;
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
        for(auto i : pic.matrix){
            for(auto j : i){
                out << j << " ";
            }
            out << std::endl;
        }
        return out;
    }
    // operator >>
    friend std::istream &operator>>(std::istream &in, picture &pic){
        for(auto &i : pic.matrix){
            for(auto &j : i){
                in >> j;
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
    matrix.resize(x);
    for(auto &i : matrix){
        i.resize(y);
    }
}
template<>
picture<char>::picture(int x, int y) {
    _maxX = x;
    _maxY = y;
    matrix.resize(x);
    for(auto &i : matrix){
        i.resize(y);
    }
    for(auto &i : matrix){
        for(auto &j : i){
            j = '0';
        }
    }
}

// set the value of a pixel
template<typename T>
void picture<T>::set(int x, int y, T value) {
    matrix[x][y] = value;
}

// output the picture
template<typename T>
T picture<T>::get(int x, int y) {
    return matrix[x][y];
}

// operator +
template<typename T>
picture<T> picture<T>::operator+(const picture<T> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY){
        throw std::invalid_argument("The pictures must be the same size");
    }
    picture<T> result(_maxX, _maxY);
    for(auto &i : result.matrix){
        for(auto &j : i){
            result.matrix[i][j] = matrix[i][j] + pic.matrix[i][j];
        }
    }
    return result;
}
template<>
picture<char> picture<char>::operator+(const picture<char> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY){
        throw std::invalid_argument("The pictures must be the same size");
    }
    picture<char> result(_maxX, _maxY);
    for(auto &i : result.matrix){
        for(auto &j : i){
            if(matrix[i][j] == '1' || pic.matrix[i][j] == '1'){
                result.matrix[i][j] = '1';
            }
            else{
                result.matrix[i][j] = '0';
            }
        }
    }
    return result;
}

// operator *
template<typename T>
picture<T> picture<T>::operator*(T value) {
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Different sizes");
    picture<T> result(_maxX, _maxY);
    for(int i = 0; i < _maxX; i++){
        for(int j = 0; j < _maxY; j++){
            result.matrix[i][j] = matrix[i][j] * value;
        }
    }
    return result;
}
template<>
picture<char> picture<char>::operator*(T value) {
    picture<char> result(_maxX, _maxY);
    for(int i = 0; i < _maxX; i++){
        for(int j = 0; j < _maxY; j++){
            if(matrix[i][j] == '1'){
                result.matrix[i][j] = '1';
            }
            else{
                result.matrix[i][j] = '0';
            }
        }
    }
    return result;
}


template<typename T>
T &picture<T>::operator()(int x, int y) {
    return matrix[x][y];
}

template<typename T>
T picture<T>::operator()(int x, int y) const {
    return matrix[x][y];
}

template<typename T>
void picture<T>::draw_circle(picture<T> &pic, int x, int y, int radius, T value) {
    for(int i = 0; i < pic._maxX; i++){
        for(int j = 0; j < pic._maxY; j++){
            if((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius){
                pic.set(i, j, value);
            }
        }
    }

}

template<typename T>
double picture<T>::fill_ratio() {
    int count = 0;
    for(auto i : matrix){
        for(auto j : i){
            if(j != 0){
                count++;
            }
        }
    }
    return (double)count / (double)(_maxX * _maxY);
}

template<typename T>
picture<T> picture<T>::operator!() {
    picture<T> res(_maxX, _maxY);
    for(int i = 0; i < _maxX; i++){
        for(int j = 0; j < _maxY; j++){
            res.matrix[i][j] = !matrix[i][j];
        }
    }
    return res;
}


template<typename T>
picture<T> picture<T>::operator+(T value) {
    picture<T> result(_maxX, _maxY);
    for(int i = 0; i < _maxX; i++){
        for(int j = 0; j < _maxY; j++){
            result.matrix[i][j] = matrix[i][j] + value;
        }
    }
    return result;
}

template<typename T>
picture<T> picture<T>::operator*(const picture<T> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY){
        throw std::invalid_argument("The pictures must be the same size");
    }
    picture<T> result(_maxX, _maxY);
    for(int i = 0; i < _maxX; i++){
        for(int j = 0; j < _maxY; j++){
            result.matrix[i][j] = matrix[i][j] * pic.matrix[i][j];
        }
    }
    return result;
}


#endif //AISD_VAR6_3_VOLGOV_PICTURE_H
