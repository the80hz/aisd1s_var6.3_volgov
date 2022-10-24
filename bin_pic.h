//
// Created by Даниил Вольгов on 16.10.2022.
//

#ifndef LAB1_BIN_PIC_H
#define LAB1_BIN_PIC_H

#include <iostream>
#include "MyException.h"

class bin_pic{
private:
    bool **matrix;
    int maxX, maxY;

public:
    // constructor
    bin_pic(int x, int y);
    // copy constructor
    bin_pic(const bin_pic &pic);
    // destructor
    ~bin_pic();
    // set the value of a pixel
    void set(int x, int y, bool value);
    // get the value of a pixel
    bool get(int x, int y);
    // output the picture
    void print();
    // invert the picture
    bin_pic invert();
    // add two pictures
    bin_pic operator+(const bin_pic &pic);
    // multiply two pictures
    bin_pic operator*(const bin_pic &pic);
    // subtract two pictures
    bin_pic operator-(const bin_pic &pic);
    // copy assignment
    bin_pic& operator=(const bin_pic &pic);
    // commutativity of addition
    friend bin_pic operator+(const bin_pic &pic1, const bin_pic &pic2);
    // commutativity of multiplication
    friend bin_pic operator*(const bin_pic &pic1, const bin_pic &pic2);
    // fill ratio
    double fill_ratio();
    // overloaded output operator
    friend std::ostream& operator<<(std::ostream &out, const bin_pic &pic);
    // overloaded input operator
    friend std::istream& operator>>(std::istream &in, bin_pic &pic);
    // overloaded equality operator
    friend bool operator==(const bin_pic &pic1, const bin_pic &pic2);
    // overloaded inequality operator
    friend bool operator!=(const bin_pic &pic1, const bin_pic &pic2);
    // draw circle function
    static void draw_circle(bin_pic &pic, int x, int y, int radius);
};


#endif //LAB1_BIN_PIC_H
