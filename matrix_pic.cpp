#include "matrix_pic.h"


// constructor
template <typename T>
matrix_pic<T>::matrix_pic(int x, int y){
    matrix = new T*[x];
    for(int i = 0; i < x; i++)
        matrix[i] = new T[y];

    _maxX = x;
    _maxY = y;
}
// copy constructor
template <typename T>
matrix_pic<T>::matrix_pic(const matrix_pic<T> &pic) : matrix_pic(pic._maxX, pic._maxY){
    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            matrix[i][j] = pic.matrix[i][j];
}
// destructor
template <typename T>
matrix_pic<T>::~matrix_pic(){
    for(int i = 0; i < _maxX; i++)
        delete[] matrix[i];

    delete[] matrix;
}

// set the value of a pixel and exception
template <typename T>
void matrix_pic<T>::set(int x, int y, T value){
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw std::out_of_range("Out of range");

    matrix[x][y] = value;
}
// get the value of a pixel
template <typename T>
T matrix_pic<T>::get(int x, int y){
    if(x >= _maxX || y >= _maxY)
        throw std::out_of_range("Out of range");

    return matrix[x][y];
}

// output the picture
template <typename T>
void matrix_pic<T>::print(){
     for(int i = 0; i < _maxX; i++){
         for(int j = 0; j < _maxY; j++){
             if(matrix[i][j])
                 std::cout << "■  ";
             else
                 std::cout << "□  ";
         }
         std::cout << std::endl;
     }
}

// operator +
template <typename T>
matrix_pic<T> matrix_pic<T>::operator+(matrix_pic<T> &pic){
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Different sizes");

    matrix_pic result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = matrix[i][j] || pic.matrix[i][j];

    return result;
}
// operator *
template <typename T>
matrix_pic<T> matrix_pic<T>::operator*(matrix_pic<T> &pic){
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw std::invalid_argument("Invalid argument");

    matrix_pic result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = matrix[i][j] && pic.matrix[i][j];

    return result;
}
// operator !
template <typename T>
matrix_pic<T> matrix_pic<T>::operator!(){
    matrix_pic result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = !matrix[i][j];

    return result;
}
// operator =
template <typename T>
matrix_pic<T>& matrix_pic<T>::operator=(const matrix_pic<T> &pic){
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

// operator + but binary
template <typename T>
matrix_pic<T> matrix_pic<T>::operator+(T value){
    matrix_pic result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = value || matrix[i][j];

    return result;
}
// operator * but binary
template <typename T>
matrix_pic<T> matrix_pic<T>::operator*(T value){
    matrix_pic result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = value && matrix[i][j];

    return result;
}

// operator <<
template <typename T>
std::ostream& operator<<(std::ostream &out, matrix_pic<T> &pic){
    for(int i = 0; i < pic._maxX; i++){
        for(int j = 0; j < pic._maxY; j++){
            if(pic.matrix[i][j])
                out << "■  ";

            else
                out << "□  ";
        }
        out << std::endl;
    }

    return out;
}
// operator >>
template <typename T>
std::istream& operator>>(std::istream &in, matrix_pic<T> &pic){
    for(int i = 0; i < pic._maxX; i++)
        for(int j = 0; j < pic._maxY; j++)
            in >> pic.matrix[i][j];

    return in;
}

// fill ratio
template <typename T>
double matrix_pic<T>::fill_ratio(){
    if(_maxX == 0 || _maxY == 0)
        return 0;

    int count = 0;
    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            if(matrix[i][j])
                count++;

    return (double)count / (_maxX * _maxY);
}
// draw a circle
template <typename T>
void matrix_pic<T>::draw_circle(matrix_pic<T> &pic, int x, int y, int radius){
    if (x < 0 || y < 0 || radius < 0 || x > pic._maxX || y > pic._maxY || radius * 2 > pic._maxX ||
    radius * 2 > pic._maxY)
        throw std::invalid_argument("Invalid argument");

    for (int i = 0; i < pic._maxX; i++)
        for (int j = 0; j < pic._maxY; j++)
            if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius)
                pic.matrix[i][j] = true;
}

// const call operator
template <typename T>
T matrix_pic<T>::operator()(int x, int y) const{
    if(x >= _maxX || y >= _maxY)
        throw std::out_of_range("Out of range");

    return matrix[x][y];
}

// call operator
template <typename T>
T &matrix_pic<T>::operator()(int x, int y) {
    if(x >= _maxX || y >= _maxY)
        throw std::out_of_range("Out of range");

    return matrix[x][y];
}
