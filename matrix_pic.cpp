#include "matrix_pic.h"

template<typename T>
matrix_pic<T>::matrix_pic(int x, int y){
    _maxX = x;
    _maxY = y;

    matrix = new T*[_maxX];
    for(int i = 0; i < _maxX; i++)
        matrix[i] = new T[_maxY];

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            matrix[i][j] = 0;
}

template<typename T>
matrix_pic<T>::matrix_pic(const matrix_pic &pic){
    _maxX = pic._maxX;
    _maxY = pic._maxY;

    matrix = new T*[_maxX];
    for(int i = 0; i < _maxX; i++)
        matrix[i] = new T[_maxY];

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            matrix[i][j] = pic.matrix[i][j];
}

template<typename T>
matrix_pic<T>::~matrix_pic(){
    for(int i = 0; i < _maxX; i++)
        delete[] matrix[i];

    delete[] matrix;
}

template<typename T>
void matrix_pic<T>::set(int x, int y, T value){
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");
    else
        matrix[x][y] = value;
}

template<typename T>
T matrix_pic<T>::get(int x, int y) {
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");
    else
        return matrix[x][y];
}

template<typename T>
void matrix_pic<T>::print() {
    for(int i = 0; i < _maxX; i++){
        for(int j = 0; j < _maxY; j++)
            std::cout << matrix[i][j] << " ";

        std::cout << std::endl;
    }
}

template<typename T>
matrix_pic<T> matrix_pic<T>::operator+(const matrix_pic<T> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Different sizes");

    matrix_pic<T> result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = matrix[i][j] + pic.matrix[i][j];

    return result;
}

template<typename T>
matrix_pic<T> matrix_pic<T>::operator*(const matrix_pic<T> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Different sizes");

    matrix_pic<T> result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = matrix[i][j] * pic.matrix[i][j];

    return result;
}

template<typename T>
matrix_pic<T> matrix_pic<T>::operator!() {
    matrix_pic<T> result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = !matrix[i][j];

    return result;
}

template<typename T>
matrix_pic<T> &matrix_pic<T>::operator=(const matrix_pic<T> &pic) {
    if(this == &pic)
        return *this;

    for(int i = 0; i < _maxX; i++)
        delete[] matrix[i];

    delete[] matrix;

    _maxX = pic._maxX;
    _maxY = pic._maxY;

    matrix = new T*[_maxX];
    for(int i = 0; i < _maxX; i++)
        matrix[i] = new T[_maxY];

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            matrix[i][j] = pic.matrix[i][j];

    return *this;
}

template<typename T>
matrix_pic<T> matrix_pic<T>::operator+(T value) {
    matrix_pic<T> result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = matrix[i][j] + value;

    return result;
}

template<typename T>
matrix_pic<T> matrix_pic<T>::operator*(T value) {
    matrix_pic<T> result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = matrix[i][j] * value;

    return result;
}

template<typename T>
double matrix_pic<T>::fill_ratio() {
    int count = 0;

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            if(matrix[i][j] != 0)
                count++;

    return (double)count / (_maxX * _maxY);
}

template<typename T>
void matrix_pic<T>::draw_circle(matrix_pic<T> &pic, int x, int y, int r, T value){
    if(x < 0 || x >= pic._maxX || y < 0 || y >= pic._maxY)
        throw std::out_of_range("Out of range");

    for(int i = 0; i < pic._maxX; i++)
        for(int j = 0; j < pic._maxY; j++)
            if((i - x) * (i - x) + (j - y) * (j - y) <= r * r)
                pic.matrix[i][j] = value;
}

template<typename T>
T matrix_pic<T>::operator()(int x, int y) const {
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");
    return matrix[x][y];
}

template<typename T>
T &matrix_pic<T>::operator()(int x, int y) {
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");
    return matrix[x][y];
}


template class matrix_pic<float>;
template class matrix_pic<short>;
template class matrix_pic<char>;
template class matrix_pic<bool>;