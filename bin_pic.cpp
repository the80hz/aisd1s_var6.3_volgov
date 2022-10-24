//
// Created by Даниил Вольгов on 16.10.2022.
//

#include "bin_pic.h"


// constructor
bin_pic::bin_pic(int x, int y){
    matrix = new bool*[x];
    for(int i = 0; i < x; i++)
        matrix[i] = new bool[y];

    maxX = x;
    maxY = y;
}
// copy constructor
bin_pic::bin_pic(const bin_pic &pic) : bin_pic(pic.maxX, pic.maxY){
    for(int i = 0; i < maxX; i++)
        for(int j = 0; j < maxY; j++)
            matrix[i][j] = pic.matrix[i][j];
}
// destructor
bin_pic::~bin_pic(){
    for(int i = 0; i < maxX; i++)
        delete[] matrix[i];

    delete[] matrix;
}
// set the value of a pixel and exception
void bin_pic::set(int x, int y, bool value){
    if(x < 0 || x >= maxX || y < 0 || y >= maxY)
        throw MyException("Index out of range");

    matrix[x][y] = value;
}
// get the value of a pixel
bool bin_pic::get(int x, int y){
    if(x >= maxX || y >= maxY)
        throw MyException("Index out of bounds");

    return matrix[x][y];
}
// output the picture
void bin_pic::print(){
     for(int i = 0; i < maxX; i++){
         for(int j = 0; j < maxY; j++){
             if(matrix[i][j])
                 std::cout << "■  ";

             else
                 std::cout << "□  ";

         }
         std::cout << std::endl;
     }
}
// invert the picture
bin_pic bin_pic::invert(){
    bin_pic pic(maxX, maxY);
    for (int i = 0; i < maxX; i++)
        for (int j = 0; j < maxY; j++)
            pic.set(i, j, !matrix[i][j]);

    return pic;
}
// add two pictures
bin_pic bin_pic::operator+(const bin_pic &pic){
    if(pic.maxX != maxX || pic.maxY != maxY)
        throw MyException("Dimensions do not match");

    bin_pic newPic(maxX, maxY);
    for(int i = 0; i < maxX; i++)
        for(int j = 0; j < maxY; j++)
            newPic.set(i, j, matrix[i][j] || pic.matrix[i][j]);

    return newPic;
}
// multiply two pictures
bin_pic bin_pic::operator*(const bin_pic &pic){
    if(pic.maxX != maxX || pic.maxY != maxY)
        throw MyException("Dimensions do not match");

    bin_pic newPic(maxX, maxY);
    for(int i = 0; i < maxX; i++)
        for(int j = 0; j < maxY; j++)
            newPic.set(i, j, matrix[i][j] && pic.matrix[i][j]);

    return newPic;
}
// subtract two pictures
bin_pic bin_pic::operator-(const bin_pic &pic){
    if(pic.maxX != maxX || pic.maxY != maxY)
        throw MyException("Dimensions do not match");

    bin_pic newPic(maxX, maxY);
    for(int i = 0; i < maxX; i++)
        for(int j = 0; j < maxY; j++)
            newPic.set(i, j, matrix[i][j] && !pic.matrix[i][j]);

    return newPic;
}
// copy assignment
bin_pic& bin_pic::operator=(const bin_pic &pic){
    if(this != &pic){
        for(int i = 0; i < maxX; i++)
            delete[] matrix[i];

        delete[] matrix;
        matrix = new bool*[pic.maxX];
        for(int i = 0; i < pic.maxX; i++)
            matrix[i] = new bool[pic.maxY];
        


        maxX = pic.maxX;
        maxY = pic.maxY;
    }
    return *this;
}
// commutativity of addition
 bin_pic operator+(const bin_pic &pic1, const bin_pic &pic2){
    if(pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY)
        throw MyException("Dimensions do not match");

    bin_pic newPic(pic1.maxX, pic1.maxY);
    for(int i = 0; i < pic1.maxX; i++)
        for(int j = 0; j < pic1.maxY; j++)
            newPic.set(i, j, pic1.matrix[i][j] || pic2.matrix[i][j]);

    return newPic;
}
// commutativity of multiplication
bin_pic operator*(const bin_pic &pic1, const bin_pic &pic2){
    if(pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY)
        throw MyException("Dimensions do not match");

    bin_pic newPic(pic1.maxX, pic1.maxY);
    for(int i = 0; i < pic1.maxX; i++)
        for(int j = 0; j < pic1.maxY; j++)
            newPic.set(i, j, pic1.matrix[i][j] && pic2.matrix[i][j]);

    return newPic;
}
// fill ratio
double bin_pic::fill_ratio(){
    if(maxX == 0 || maxY == 0)
        throw MyException("Dimensions are 0");

    int count = 0;
    for(int i = 0; i < maxX; i++)
        for(int j = 0; j < maxY; j++)
            if(matrix[i][j])
                count++;

    return (double)count / (maxX * maxY);
}
// overloaded output operator
std::ostream& operator<<(std::ostream &out, const bin_pic &pic){
    if(pic.maxX == 0 || pic.maxY == 0)
        throw MyException("Dimensions are 0");

    for(int i = 0; i < pic.maxX; i++){
        for(int j = 0; j < pic.maxY; j++)
            out << pic.matrix[i][j];

        out << std::endl;
    }

    return out;
}
// overloaded input operator
std::istream& operator>>(std::istream &in, bin_pic &pic){
    if(pic.maxX == 0 || pic.maxY == 0)
        throw MyException("Dimensions are 0");

    for(int i = 0; i < pic.maxX; i++)
        for(int j = 0; j < pic.maxY; j++)
            in >> pic.matrix[i][j];

    return in;
}
// overloaded equality operator
bool operator==(const bin_pic &pic1, const bin_pic &pic2){
    if(pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY)
        throw MyException("Dimensions do not match");

    for(int i = 0; i < pic1.maxX; i++)
        for(int j = 0; j < pic1.maxY; j++)
            if(pic1.matrix[i][j] != pic2.matrix[i][j])
                return false;

    return true;
}
// overloaded inequality operator
bool operator!=(const bin_pic &pic1, const bin_pic &pic2){
    if (pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY)
        throw MyException("Dimensions do not match");

    for (int i = 0; i < pic1.maxX; i++)
        for (int j = 0; j < pic1.maxY; j++)
            if (pic1.matrix[i][j] != pic2.matrix[i][j])
                return true;

    return false;
}
// draw a circle
void bin_pic::draw_circle(bin_pic &pic, int x, int y, int radius){
    if (x < 0 || y < 0 || radius < 0 || x > pic.maxX || y > pic.maxY || radius * 2 > pic.maxX ||
    radius * 2 > pic.maxY)
        throw MyException("Invalid input");

    for (int i = 0; i < pic.maxX; i++)
        for (int j = 0; j < pic.maxY; j++)
            if ((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius)
                pic.matrix[i][j] = true;
}