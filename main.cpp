#include <iostream>

class bin_pic{
private:
    bool **matrix;
    int maxX, maxY;

public:
    bin_pic(int x, int y){
        matrix = new bool*[x];
        for(int i = 0; i < x; i++){
            matrix[i] = new bool[y];
        }
        maxX = x;
        maxY = y;
    }
    bin_pic(const bin_pic &pic){
        matrix = new bool*[pic.maxX];
        for(int i = 0; i < pic.maxX; i++){
            matrix[i] = new bool[pic.maxY];
        }
        maxX = pic.maxX;
        maxY = pic.maxY;
    }
    ~bin_pic(){
        for(int i = 0; i < maxX; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    void set(int x, int y, bool value){
        matrix[x][y] = value;
    }
    bool get(int x, int y){
        return matrix[x][y];
    }
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
};

int main() {
    bin_pic pic(5, 5);
    pic.set(0, 0, true);
    pic.set(1, 1, true);
    pic.set(2, 2, true);
    pic.set(3, 3, true);
    pic.set(4, 4, true);
    pic.print();
    return 0;
}
