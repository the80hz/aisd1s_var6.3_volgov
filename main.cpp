#include <iostream>
#include "matrix_pic.h"

template<typename T>
void menu(matrix_pic<T> &pic1, matrix_pic<T> &pic2){
    while(true){
        int i;
        std::cout << "1. Create a circle" << std::endl;
        std::cout << "2. Print a picture" << std::endl;
        std::cout << "3. Invert a picture" << std::endl;
        std::cout << "4. Add two pictures" << std::endl;
        std::cout << "5. Add picture with value" << std::endl;
        std::cout << "6. Multiply two pictures" << std::endl;
        std::cout << "7. Multiply picture with value" << std::endl;
        std::cout << "8. Fill ratio" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cin >> i;

        switch(i){
            case 1:{
                // creating picture
                int x, y, radius;
                std::cout << "Enter the coordinates of the center and the radius of the circle" << std::endl;
                std::cin >> x >> y >> radius;
                std::cout << "Enter the value of the pixel" << std::endl;
                T value;
                std::cin >> value;
                matrix_pic<T>::draw_circle(pic1, x, y, radius, value);
                break;
            }
            case 2:{
                // printing
                std::cout << pic1;
                break;
            }
            case 3:{
                // operator !
                pic1 = !pic1;
                break;
            }
            case 4:{
                // operator +
                pic1 = pic1 + pic2;
                break;
            }
            case 5:{
                // operator + value
                bool value;
                std::cout << "Enter a value" << std::endl;
                std::cin >> value;
                pic1 = pic1 + value;
                break;
            }
            case 6:{
                // operator *
                pic1 = pic1 * pic2;
                break;
            }
            case 7:{
                // operator * value
                bool value;
                std::cout << "Enter a value" << std::endl;
                std::cin >> value;
                pic1 = pic1 * value;
                break;
            }
            case 8:{
                // fill ratio
                std::cout << pic1.fill_ratio() << std::endl;
                break;
            }
            case 9:{
                // exit
                return;
            }
            default:{
                std::cout << "Wrong input" << std::endl;
                std::cin >> i;
                break;
            }
        }
    }
}


void select_picture(size_t type){
    int x, y, num;
    std::cout << "Enter the size of the picture" << std::endl;
    std::cin >> x >> y;

    if(type == 1)
        std::cout << "bool" << std::endl;
    else if(type == 2)
        std::cout << "char" << std::endl;
    else if(type == 3)
        std::cout << "short" << std::endl;
    else if(type == 4)
        std::cout << "float" << std::endl;

    while(true){
        std::cout << "Select picture" << std::endl;
        std::cout << "1. First picture" << std::endl;
        std::cout << "2. Second picture" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cin >> num;
        switch (num){
            case 1:
                menu<T>(pic1, pic2);
                break;
            case 2:
                menu(pic2, pic1);
                break;
            case 3:
                return;
            default:
                std::cout << "Wrong number" << std::endl;
                break;
        }
    }
}

void select_type(){
    while(true){
        int i;
        std::cout << "Select type" << std::endl;
        std::cout << "1. bool" << std::endl;
        std::cout << "2. char" << std::endl;
        std::cout << "3. short" << std::endl;
        std::cout << "4. float" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cin >> i;
        switch(i){
            case 1:{
                select_picture(1);
                break;
            }
            case 2:{
                select_picture(2);
                break;
            }
            case 3:{
                select_picture(3);
                break;
            }
            case 4:{
                select_picture(4);
                break;
            }
            case 0:{
                return;
            }
            default:{
                std::cout << "Wrong input" << std::endl;
                break;
            }
        }
    }
}

int main(){
    select_type();

    return 0;
}
