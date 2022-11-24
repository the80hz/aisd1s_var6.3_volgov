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

    /*
    // operator +
    matrix_pic<T> operator+(const matrix_pic<T> &pic);
    // operator *
    matrix_pic<T> operator*(const matrix_pic<T> &pic);
    // operator + but with value
    matrix_pic<T> operator+(T value);
    // operator * but with value
    matrix_pic<T> operator*(T value);
    */

    matrix_pic& operator *(const matrix_pic& obg);
    matrix_pic& operator +(const matrix_pic& obg);
    matrix_pic& operator *(T value);
    matrix_pic& operator +(T value);
    friend matrix_pic& operator *(T value, matrix_pic& obj);
    friend matrix_pic& operator +(T value, matrix_pic& obj);

    // operator !
    matrix_pic<T> operator!();
    // operator =
    matrix_pic<T> &operator=(const matrix_pic<T> &pic);



    // operator <<
    friend std::ostream &operator<<(std::ostream &out, const matrix_pic &pic){
        for(int i = 0; i < pic._maxX; i++){
            for(int j = 0; j < pic._maxY; j++){
                out << pic.matrix[i][j] << " ";
            }
            out << std::endl;
        }
        return out;
    }
    // operator >>
    friend std::istream &operator>>(std::istream &in, matrix_pic &pic){
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
    static void draw_circle(matrix_pic<T> &pic, int x, int y, int r, T value);

    // const call operator
    T operator()(int x, int y) const;

    // call operator
    T &operator()(int x, int y);
};


#endif //LAB1_BIN_PIC_H
