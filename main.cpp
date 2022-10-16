#include <iostream>

class MyException : public std::exception {
public:
    explicit MyException(const char* msg) : msg_(msg) {}
    const char* what() const noexcept override { return msg_; }
private:
    const char* msg_;
};


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
        try{
            if(x >= maxX || y >= maxY){
                throw MyException("Index out of bounds");
            }
            matrix[x][y] = value;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
    }
    // get the value of a pixel
    bool get(int x, int y){
        try{
            if(x >= maxX || y >= maxY){
                throw MyException("Index out of bounds");
            }
            return matrix[x][y];
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return false;
    }
    // output the picture
    void print(){
        try{
            for(int i = 0; i < maxX; i++){
                for(int j = 0; j < maxY; j++){
                    if(matrix[i][j]){
                        std::cout << "1";
                    }
                    else{
                        std::cout << "0";
                    }
                }
                std::cout << std::endl;
            }
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
    }
    // invert the picture
    bin_pic operator!(){
        try{
            bin_pic pic(maxX, maxY);
            for (int i = 0; i < maxX; i++) {
                for (int j = 0; j < maxY; j++) {
                    pic.set(i, j, !matrix[i][j]);
                }
            }
            return pic;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return {0, 0};
    }
    // add two pictures
    bin_pic operator+(const bin_pic &pic){
        try{
            if(pic.maxX != maxX || pic.maxY != maxY){
                throw MyException("Dimensions do not match");
            }
            bin_pic newPic(maxX, maxY);
            for(int i = 0; i < maxX; i++){
                for(int j = 0; j < maxY; j++){
                    newPic.set(i, j, matrix[i][j] || pic.matrix[i][j]);
                }
            }
            return newPic;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return *this;
    }
    // multiply two pictures
    bin_pic operator*(const bin_pic &pic){
        try{
            if(pic.maxX != maxX || pic.maxY != maxY){
                throw MyException("Dimensions do not match");
            }
            bin_pic newPic(maxX, maxY);
            for(int i = 0; i < maxX; i++){
                for(int j = 0; j < maxY; j++){
                    newPic.set(i, j, matrix[i][j] && pic.matrix[i][j]);
                }
            }
            return newPic;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return *this;
    }
    // subtract two pictures
    bin_pic operator-(const bin_pic &pic){
        try{
            if(pic.maxX != maxX || pic.maxY != maxY){
                throw MyException("Dimensions do not match");
            }
            bin_pic newPic(maxX, maxY);
            for(int i = 0; i < maxX; i++){
                for(int j = 0; j < maxY; j++){
                    newPic.set(i, j, matrix[i][j] && !pic.matrix[i][j]);
                }
            }
            return newPic;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return *this;
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
        }
        return *this;
    }
    // commutativity of addition
    friend bin_pic operator+(const bin_pic &pic1, const bin_pic &pic2){
        try{
            if(pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY){
                throw MyException("Dimensions do not match");
            }
            bin_pic newPic(pic1.maxX, pic1.maxY);
            for(int i = 0; i < pic1.maxX; i++){
                for(int j = 0; j < pic1.maxY; j++){
                    newPic.set(i, j, pic1.matrix[i][j] || pic2.matrix[i][j]);
                }
            }
            return newPic;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return pic1;
    }
    // commutativity of multiplication
    friend bin_pic operator*(const bin_pic &pic1, const bin_pic &pic2){
        try{
            if(pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY){
                throw MyException("Dimensions do not match");
            }
            bin_pic newPic(pic1.maxX, pic1.maxY);
            for(int i = 0; i < pic1.maxX; i++){
                for(int j = 0; j < pic1.maxY; j++){
                    newPic.set(i, j, pic1.matrix[i][j] && pic2.matrix[i][j]);
                }
            }
            return newPic;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return pic1;
    }
    // fill ratio
    double fill_ratio(){
        try{
            if(maxX == 0 || maxY == 0){
                throw MyException("Dimensions are 0");
            }
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
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return 0;
    }
    // overloaded output operator
    friend std::ostream& operator<<(std::ostream &out, const bin_pic &pic){
        try{
            if(pic.maxX == 0 || pic.maxY == 0){
                throw MyException("Dimensions are 0");
            }
            for(int i = 0; i < pic.maxX; i++){
                for(int j = 0; j < pic.maxY; j++){
                    out << pic.matrix[i][j];
                }
                out << std::endl;
            }
            return out;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return out;
    }
    // overloaded input operator
    friend std::istream& operator>>(std::istream &in, bin_pic &pic){
        try{
            if(pic.maxX == 0 || pic.maxY == 0){
                throw MyException("Dimensions are 0");
            }
            for(int i = 0; i < pic.maxX; i++){
                for(int j = 0; j < pic.maxY; j++){
                    in >> pic.matrix[i][j];
                }
            }
            return in;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return in;
    }
    // overloaded equality operator
    friend bool operator==(const bin_pic &pic1, const bin_pic &pic2){
        try{
            if(pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY){
                throw MyException("Dimensions do not match");
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
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return false;
    }
    // overloaded inequality operator
    friend bool operator!=(const bin_pic &pic1, const bin_pic &pic2){
        try{
            if (pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY) {
                throw MyException("Dimensions do not match");
            }
            for (int i = 0; i < pic1.maxX; i++) {
                for (int j = 0; j < pic1.maxY; j++) {
                    if (pic1.matrix[i][j] != pic2.matrix[i][j]) {
                        return true;
                    }
                }
            }
            return false;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return false;
    }
    // overloaded less than operator
    friend bool operator<(const bin_pic &pic1, const bin_pic &pic2){
        try{
            if(pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY){
                throw MyException("Dimensions do not match");
            }
            for(int i = 0; i < pic1.maxX; i++){
                for(int j = 0; j < pic1.maxY; j++){
                    if(pic1.matrix[i][j] < pic2.matrix[i][j]){
                        return true;
                    }
                }
            }
            return false;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return false;
    }
    // overloaded greater than operator
    friend bool operator>(const bin_pic &pic1, const bin_pic &pic2){
        try{
            if(pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY){
                throw MyException("Dimensions do not match");
            }
            for(int i = 0; i < pic1.maxX; i++){
                for(int j = 0; j < pic1.maxY; j++){
                    if(pic1.matrix[i][j] > pic2.matrix[i][j]){
                        return true;
                    }
                }
            }
            return false;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return false;
    }
    // overloaded less than or equal to operator
    friend bool operator<=(const bin_pic &pic1, const bin_pic &pic2){
        try{
            if(pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY){
                throw MyException("Dimensions do not match");
            }
            for(int i = 0; i < pic1.maxX; i++){
                for(int j = 0; j < pic1.maxY; j++){
                    if(pic1.matrix[i][j] <= pic2.matrix[i][j]){
                        return true;
                    }
                }
            }
            return false;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return false;
    }
    // overloaded greater than or equal to operator
    friend bool operator>=(const bin_pic &pic1, const bin_pic &pic2){
        try{
            if (pic1.maxX != pic2.maxX || pic1.maxY != pic2.maxY) {
                throw MyException("Dimensions do not match");
            }
            for (int i = 0; i < pic1.maxX; i++) {
                for (int j = 0; j < pic1.maxY; j++) {
                    if (pic1.matrix[i][j] >= pic2.matrix[i][j]) {
                        return true;
                    }
                }
            }
            return false;
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
        return false;
    }
    // draw circle function
    static void draw_circle(bin_pic &pic, int x, int y, int radius){
        try{
            if(x < 0 || y < 0 || radius < 0 || x > pic.maxX || y > pic.maxY || radius*2 > pic.maxX || radius*2 > pic.maxY){
                throw MyException("Invalid input");
            }
            for(int i = 0; i < pic.maxX; i++){
                for(int j = 0; j < pic.maxY; j++){
                    if((i - x) * (i - x) + (j - y) * (j - y) <= radius * radius){
                        pic.matrix[i][j] = true;
                    }
                }
            }
        }
        catch(MyException &e){
            std::cout << e.what() << std::endl;
        }
    }
};

int main() {
    bin_pic pic1(5, 5);
    bin_pic::draw_circle(pic1, 3, 3, 2);
    std::cout << pic1 << std::endl;
    return 0;
}
