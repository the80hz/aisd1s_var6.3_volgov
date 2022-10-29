//
// Created by Даниил Вольгов on 16.10.2022.
//

#include "bin_pic.h"


// constructor
bin_pic::bin_pic(int x, int y){
    matrix = new bool*[x];
    for(int i = 0; i < x; i++)
        matrix[i] = new bool[y];

    _maxX = x;
    _maxY = y;
}
// copy constructor
bin_pic::bin_pic(const bin_pic &pic) : bin_pic(pic._maxX, pic._maxY){
    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            matrix[i][j] = pic.matrix[i][j];
}
// destructor
bin_pic::~bin_pic(){
    for(int i = 0; i < _maxX; i++)
        delete[] matrix[i];

    delete[] matrix;
}

// set the value of a pixel and exception
void bin_pic::set(int x, int y, bool value){
    if(x < 0 || x >= _maxX || y < 0 || y >= _maxY)
        throw MyException("Index out of range");

    matrix[x][y] = value;
}
// get the value of a pixel
bool bin_pic::get(int x, int y){
    if(x >= _maxX || y >= _maxY)
        throw MyException("Index out of bounds");

    return matrix[x][y];
}

// output the picture
void bin_pic::print(){
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
bin_pic bin_pic::operator+(bin_pic &pic){
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw MyException("Different sizes");

    bin_pic result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = matrix[i][j] || pic.matrix[i][j];

    return result;
}
// operator *
bin_pic bin_pic::operator*(bin_pic &pic){
    if(_maxX != pic._maxX || _maxY != pic._maxY)
        throw MyException("Different sizes");

    bin_pic result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = matrix[i][j] && pic.matrix[i][j];

    return result;
}
// operator !
bin_pic bin_pic::operator!(){
    bin_pic result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = !matrix[i][j];

    return result;
}
// operator =
bin_pic& bin_pic::operator=(const bin_pic &pic){
    if(this == &pic)
        return *this;

    for(int i = 0; i < _maxX; i++)
        delete[] matrix[i];

    delete[] matrix;

    _maxX = pic._maxX;
    _maxY = pic._maxY;

    matrix = new bool*[_maxX];
    for(int i = 0; i < _maxX; i++)
        matrix[i] = new bool[_maxY];

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            matrix[i][j] = pic.matrix[i][j];

    return *this;
}

// operator + but binary
bin_pic bin_pic::operator+(bool value){
    bin_pic result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = value || matrix[i][j];

    return result;
}
// operator * but binary
bin_pic bin_pic::operator*(bool value){
    bin_pic result(_maxX, _maxY);

    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            result.matrix[i][j] = value && matrix[i][j];

    return result;
}

// operator <<
std::ostream& operator<<(std::ostream &out, bin_pic &pic){
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
std::istream& operator>>(std::istream &in, bin_pic &pic){
    for(int i = 0; i < pic._maxX; i++)
        for(int j = 0; j < pic._maxY; j++)
            in >> pic.matrix[i][j];

    return in;
}

// fill ratio
double bin_pic::fill_ratio(){
    if(_maxX == 0 || _maxY == 0)
        throw MyException("Dimensions are 0");

    int count = 0;
    for(int i = 0; i < _maxX; i++)
        for(int j = 0; j < _maxY; j++)
            if(matrix[i][j])
                count++;

    return (double)count / (_maxX * _maxY);
}
// draw a circle
void bin_pic::draw_circle(bin_pic &pic, int x, int y, int radius){
    if (x < 0 || y < 0 || radius < 0 || x > pic._maxX || y > pic._maxY || radius * 2 > pic._maxX ||
    radius * 2 > pic._maxY)
        throw MyException("Invalid input");

    for (int i = 0; i < pic._maxX; i++)
        for (int j = 0; j < pic._maxY; j++)
            if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius)
                pic.matrix[i][j] = true;
}
