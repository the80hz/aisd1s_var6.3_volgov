#include "bin_pic.h"

// constructor
template<typename T>
bin_pic<T>::bin_pic(int x, int y){
    _maxX = x;
    _maxY = y;

    matrix = new T*[_maxX];
    for(int i = 0; i < _maxX; i++)
        matrix[i] = new T[_maxY];

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            matrix[i][j] = 0;
}
template<>
bin_pic<char>::bin_pic(int x, int y){
    _maxX = x;
    _maxY = y;

    matrix = new char*[_maxX];
    for(int i = 0; i < _maxX; i++)
        matrix[i] = new char[_maxY];

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            matrix[i][j] = '0';
}

// copy constructor
template<typename T>
bin_pic<T>::bin_pic(const bin_pic &pic){
    _maxX = pic._maxX;
    _maxY = pic._maxY;

    matrix = new T*[_maxX];
    for(int i = 0; i < _maxX; i++)
        matrix[i] = new T[_maxY];

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            matrix[i][j] = pic.matrix[i][j];
}

// destructor
template<typename T>
bin_pic<T>::~bin_pic(){
    for(int i = 0; i < _maxX; i++)
        delete[] matrix[i];

    delete[] matrix;
}

// set the value of a pixel
template<typename T>
void bin_pic<T>::set(int x, int y, T value){
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");
    if(value != 0 && value != 1 && value != '0' && value != '1')
        throw std::invalid_argument("Invalid argument");
    else
        matrix[x][y] = value;
}

// get the value of a pixel
template<typename T>
T bin_pic<T>::get(int x, int y) {
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");
    else
        return matrix[x][y];
}

// output the picture
template<typename T>
void bin_pic<T>::print() {
    for(int i = 0; i < _maxX; i++){
        for(int j = 0; j < _maxY; j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }
}

// operator +
template<typename T>
bin_pic<T> bin_pic<T>::operator+(const bin_pic<T> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Different sizes");

    bin_pic<T> result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = matrix[i][j] || pic.matrix[i][j];

    return result;
}
template<>
bin_pic<char> bin_pic<char>::operator+(const bin_pic<char> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Different sizes");

    bin_pic<char> result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            if(matrix[i][j] == '0' && pic.matrix[i][j] == '0')
                result.matrix[i][j] = '0';
            else
                result.matrix[i][j] = '1';

    return result;
}

// operator *
template<typename T>
bin_pic<T> bin_pic<T>::operator*(const bin_pic<T> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Different sizes");

    bin_pic<T> result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = matrix[i][j] * pic.matrix[i][j];

    return result;
}
template<>
bin_pic<char> bin_pic<char>::operator*(const bin_pic<char> &pic) {
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Different sizes");

    bin_pic<char> result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            if(matrix[i][j] == '1' && pic.matrix[i][j] == '1')
                result.matrix[i][j] = '1';
            else
                result.matrix[i][j] = '0';

    return result;
}

// operator + with bool
template<typename T>
bin_pic<T> bin_pic<T>::operator+(T value) {
    bin_pic<T> result(_maxX, _maxY);

    if(value != 0 && value != 1 && value != '0' && value != '1')
        throw std::invalid_argument("Invalid argument");

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = matrix[i][j] || value;

    return result;
}
template<>
bin_pic<char> bin_pic<char>::operator+(char value) {
    bin_pic<char> result(_maxX, _maxY);

    if(value != 0 && value != 1 && value != '0' && value != '1')
        throw std::invalid_argument("Invalid argument");

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            if(matrix[i][j] == '0' && value == '0')
                result.matrix[i][j] = '0';
            else
                result.matrix[i][j] = '1';

    return result;
}


// operator * with bool
template<typename T>
bin_pic<T> bin_pic<T>::operator*(T value) {
    bin_pic<T> result(_maxX, _maxY);

    if(value != 0 && value != 1 && value != '0' && value != '1')
        throw std::invalid_argument("Invalid argument");

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = matrix[i][j] * value;

    return result;
}
template<>
bin_pic<char> bin_pic<char>::operator*(char value) {
    bin_pic<char> result(_maxX, _maxY);

    if(value != 0 && value != 1 && value != '0' && value != '1')
        throw std::invalid_argument("Invalid argument");

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            if(matrix[i][j] == '1' && value == '1')
                result.matrix[i][j] = '1';
            else
                result.matrix[i][j] = '0';

    return result;
}

// operator !
template<typename T>
bin_pic<T> bin_pic<T>::operator!() {
    bin_pic<T> result(_maxX, _maxY);
    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            if(matrix[i][j] == 0)
                result.matrix[i][j] = 1;
            else if(matrix[i][j] == 1)
                result.matrix[i][j] = 0;
            else if(matrix[i][j] == '0')
                result.matrix[i][j] = '1';
            else if(matrix[i][j] == '1')
                result.matrix[i][j] = '0';


            //result.matrix[i][j] = !matrix[i][j];
    return result;
}

// operator =
template<typename T>
bin_pic<T> &bin_pic<T>::operator=(const bin_pic<T> &pic) {
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

// fill ratio of the picture
template<typename T>
double bin_pic<T>::fill_ratio() {
    int count = 0;

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            if(matrix[i][j] != 0)
                count++;

    return (double)count / (_maxX * _maxY);
}

// draw a circle
template<typename T>
void bin_pic<T>::draw_circle(bin_pic<T> &pic, int x, int y, int r, T value){
    if(x < 0 || x >= pic._maxX || y < 0 || y >= pic._maxY)
        throw std::out_of_range("Out of range");

    for(int i = 0; i < pic._maxX; i++)
        for(int j = 0; j < pic._maxY; j++)
            if((i - x) * (i - x) + (j - y) * (j - y) <= r * r)
                pic.matrix[i][j] = value;
}

// const call operator
template<typename T>
T bin_pic<T>::operator()(int x, int y) const {
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");
    return matrix[x][y];
}

// call operator
template<typename T>
T &bin_pic<T>::operator()(int x, int y) {
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");
    return matrix[x][y];
}


template class bin_pic<float>;
template class bin_pic<short>;
template class bin_pic<char>;
template class bin_pic<bool>;