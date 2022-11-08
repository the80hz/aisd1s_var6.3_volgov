#ifndef LAB1_BIN_PIC_H
#define LAB1_BIN_PIC_H

#include <iostream>


class bin_pic{
private:
    bool **matrix;
    int _maxX, _maxY;

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

    // operator +
    bin_pic operator+(bin_pic &pic);
    // operator *
    bin_pic operator*(bin_pic &pic);
    // operator !
    bin_pic operator!();
    // operator =
    bin_pic& operator=(const bin_pic &pic);

    // operator + but binary
    bin_pic operator+(bool value);
    // operator * but binary
    bin_pic operator*(bool value);

    // operator <<
    friend std::ostream& operator<<(std::ostream &out, bin_pic &pic);
    // operator >>
    friend std::istream& operator>>(std::istream &in, bin_pic &pic);

    // fill ratio
    double fill_ratio();
    // draw a circle
    static void draw_circle(bin_pic &pic, int x, int y, int radius);

    // const call operator
    bool operator()(int x, int y) const;

    // call operator
    bool& operator()(int x, int y);
};


#endif //LAB1_BIN_PIC_H
