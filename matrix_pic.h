#ifndef LAB1_BIN_PIC_H
#define LAB1_BIN_PIC_H

#include <iostream>


template <typename T>
class matrix_pic{
private:
    T **matrix;
    int _maxX{}, _maxY{};

public:
    // constructor
    matrix_pic(int x, int y);
    // copy constructor
    matrix_pic(const matrix_pic &pic);
    // destructor
    ~matrix_pic();

    // set the value of a pixel
    void set(int x, int y, T value);
    // get the value of a pixel
    T get(int x, int y);

    // output the picture
    void print();

    // operator +
    matrix_pic operator+(matrix_pic &pic);
    // operator *
    matrix_pic operator*(matrix_pic &pic);
    // operator !
    matrix_pic operator!();
    // operator =
    matrix_pic& operator=(const matrix_pic &pic);

    // operator + but binary
    matrix_pic operator+(T value);
    // operator * but binary
    matrix_pic operator*(T value);

    // operator <<
    friend std::ostream& operator<<(std::ostream &out, matrix_pic &pic);
    // operator >>
    friend std::istream& operator>>(std::istream &in, matrix_pic &pic);

    // fill ratio
    double fill_ratio();
    // draw a circle
    static void draw_circle(matrix_pic &pic, int x, int y, int radius);

    // const call operator
    T operator()(int x, int y) const;

    // call operator
    T& operator()(int x, int y);
};


#endif //LAB1_BIN_PIC_H
