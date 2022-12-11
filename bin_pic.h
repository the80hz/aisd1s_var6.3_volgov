#ifndef LAB1_BIN_PIC_H
#define LAB1_BIN_PIC_H

#include <iostream>
#include <list>

template <typename T>
class bin_pic{
private:
    T **matrix;
    int _maxX{}, _maxY{};
public:
    // constructor
    bin_pic(int x, int y);
    // copy constructor
    bin_pic(const bin_pic &pic);
    // destructor
    ~bin_pic();

    // set the value of a pixel
    void set(int x, int y, T value);
    // get the value of a pixel
    T get(int x, int y);

    // output the picture
    void print();

    // operator +
    bin_pic<T> operator+(const bin_pic<T> &pic);
    // operator *
    bin_pic<T> operator*(const bin_pic<T> &pic);
    // operator + but with value
    bin_pic<T> operator+(T value);
    // operator * but with value
    bin_pic<T> operator*(T value);

    // operator !
    bin_pic<T> operator!();
    // operator =
    bin_pic<T> &operator=(const bin_pic<T> &pic);

    // operator <<
    friend std::ostream &operator<<(std::ostream &out, const bin_pic &pic){
        for(int i = 0; i < pic._maxX; i++){
            for(int j = 0; j < pic._maxY; j++){
                out << pic.matrix[i][j] << " ";
            }
            out << std::endl;
        }
        return out;
    }
    // operator >>
    friend std::istream &operator>>(std::istream &in, bin_pic &pic){
        for(int i = 0; i < pic._maxX; i++){
            for(int j = 0; j < pic._maxY; j++){
                in >> pic.matrix[i][j];
            }
        }
        return in;
    }

    // fill ratio
    double fill_ratio();
    // draw a circle
    static void draw_circle(bin_pic<T> &pic, int x, int y, int r, T value);

    // const call operator
    T operator()(int x, int y) const;

    // call operator
    T &operator()(int x, int y);
};


#endif //LAB1_BIN_PIC_H
