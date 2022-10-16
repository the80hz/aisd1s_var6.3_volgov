#include <iostream>

class bin_pic{
private:
    bool **matrix;
    int maxX, maxY;

public:
    // constructor
    bin_pic(int x, int y){
        matrix = new bool*[x];
        for(int i = 0; i < x; i++){
            matrix[i] = new bool[y];
        }
        maxX = x;
        maxY = y;
    }
    // copy constructor
    bin_pic(const bin_pic &pic){
        matrix = new bool*[pic.maxX];
        for(int i = 0; i < pic.maxX; i++){
            matrix[i] = new bool[pic.maxY];
        }
        maxX = pic.maxX;
        maxY = pic.maxY;
    }
    // destructor
    ~bin_pic(){
        for(int i = 0; i < maxX; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    // set the value of a pixel
    void set(int x, int y, bool value){
        matrix[x][y] = value;
    }
    // get the value of a pixel
    bool get(int x, int y){
        return matrix[x][y];
    }
    // output the picture
    void print(){
        for(int i = 0; i < maxX; i++){
            for(int j = 0; j < maxY; j++){
                std::cout << matrix[i][j];
            }
            std::cout << std::endl;
        }
    }
    // invert the picture
    bin_pic operator!(){
        bin_pic pic(maxX, maxY);
        for(int i = 0; i < maxX; i++){
            for(int j = 0; j < maxY; j++){
                pic.set(i, j, !matrix[i][j]);
            }
        }
        return pic;
    }
    // add two pictures
    bin_pic operator+(const bin_pic &pic){
        bin_pic new_pic(maxX, maxY);
        for(int i = 0; i < maxX; i++){
            for(int j = 0; j < maxY; j++){
                new_pic.set(i, j, matrix[i][j] || pic.matrix[i][j]);
            }
        }
        return new_pic;
    }
    // multiply two pictures
    bin_pic operator*(const bin_pic &pic){
        bin_pic new_pic(maxX, maxY);
        for(int i = 0; i < maxX; i++){
            for(int j = 0; j < maxY; j++){
                new_pic.set(i, j, matrix[i][j] && pic.matrix[i][j]);
            }
        }
        return new_pic;
    }
    // subtract two pictures
    bin_pic operator-(const bin_pic &pic){
        bin_pic new_pic(maxX, maxY);
        for(int i = 0; i < maxX; i++){
            for(int j = 0; j < maxY; j++){
                new_pic.set(i, j, matrix[i][j] && !pic.matrix[i][j]);
            }
        }
        return new_pic;
    }
    // copy assignment
    bin_pic& operator=(const bin_pic &pic){
        if(this != &pic){
            for(int i = 0; i < maxX; i++){
                delete[] matrix[i];
            }
            delete[] matrix;
            matrix = new bool*[pic.maxX];
            for(int i = 0; i < pic.maxX; i++){
                matrix[i] = new bool[pic.maxY];
            }
            maxX = pic.maxX;
            maxY = pic.maxY;
            for(int i = 0; i < maxX; i++){
                for(int j = 0; j < maxY; j++){
                    matrix[i][j] = pic.matrix[i][j];
                }
            }
        }
        return *this;
    }
    // commutativity of addition
    friend bin_pic operator+(const bin_pic &pic1, const bin_pic &pic2){
        bin_pic new_pic(pic1.maxX, pic1.maxY);
        for(int i = 0; i < pic1.maxX; i++){
            for(int j = 0; j < pic1.maxY; j++){
                new_pic.set(i, j, pic1.matrix[i][j] || pic2.matrix[i][j]);
            }
        }
        return new_pic;
    }
    // commutativity of multiplication
    friend bin_pic operator*(const bin_pic &pic1, const bin_pic &pic2){
        bin_pic new_pic(pic1.maxX, pic1.maxY);
        for(int i = 0; i < pic1.maxX; i++){
            for(int j = 0; j < pic1.maxY; j++){
                new_pic.set(i, j, pic1.matrix[i][j] && pic2.matrix[i][j]);
            }
        }
        return new_pic;
    }
    // fill ratio
    double fill_ratio(){
        int count = 0;
        for(int i = 0; i < maxX; i++){
            for(int j = 0; j < maxY; j++){
                if(matrix[i][j]){
                    count++;
                }
            }
        }
        return (double)count / (maxX * maxY);
    }
    // overloaded output operator
    friend std::ostream& operator<<(std::ostream &out, const bin_pic &pic){
        for(int i = 0; i < pic.maxX; i++){
            for(int j = 0; j < pic.maxY; j++){
                out << pic.matrix[i][j];
            }
            out << std::endl;
        }
        return out;
    }
    // overloaded input operator
    friend std::istream& operator>>(std::istream &in, bin_pic &pic){
        for(int i = 0; i < pic.maxX; i++){
            for(int j = 0; j < pic.maxY; j++){
                in >> pic.matrix[i][j];
            }
        }
        return in;
    }
    // overloaded equality operator
    friend bool operator==(const bin_pic &pic1, const bin_pic &pic2){
        if(pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY){
            return false;
        }
        for(int i = 0; i < pic1.maxX; i++){
            for(int j = 0; j < pic1.maxY; j++){
                if(pic1.matrix[i][j] != pic2.matrix[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    bin_pic pic(5, 5);
    pic.set(0, 0, true);
    pic.set(1, 1, true);
    pic.set(2, 2, true);
    pic.set(3, 3, true);
    pic.set(4, 4, true);
    std::cout << pic;
    return 0;
}
