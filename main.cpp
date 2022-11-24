#include <iostream>
#include "matrix_pic.h"

/*
void menu(matrix_pic<bool> &pic1, matrix_pic<bool> &pic2){
    while(true){
        int i;
        std::cout << "1. Create a circle" << std::endl;
        std::cout << "2. Print a picture" << std::endl;
        std::cout << "3. Invert a picture" << std::endl;
        std::cout << "4. Add two pictures" << std::endl;
        std::cout << "5. Add picture with bool" << std::endl;
        std::cout << "6. Multiply two pictures" << std::endl;
        std::cout << "7. Multiply picture with bool" << std::endl;
        std::cout << "8. Fill ratio" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cin >> i;

        switch(i){
            case 1:{
                // creating picture
                int x, y, radius;
                std::cout << "Enter the coordinates of the center and the radius of the circle" << std::endl;
                std::cin >> x >> y >> radius;
                matrix_pic<bool>::draw_circle(pic1, x, y, radius, true);
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
                // operator + bool
                bool value;
                std::cout << "Enter a bool" << std::endl;
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
                // operator * bool
                bool value;
                std::cout << "Enter a bool" << std::endl;
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

void select_pic(){
    int x, y;

    std::cout << "Create a first picture" << std::endl;
    std::cout << "Enter the size of the picture" << std::endl;
    std::cin >> x >> y;
    matrix_pic<bool> pic1(x, y);

    std::cout << "Enter the second picture" << std::endl;
    std::cout << "Enter the size of the picture" << std::endl;
    std::cin >> x >> y;
    matrix_pic<bool> pic2(x, y);

    int num;
    while(true){
        std::cout << "Select picture" << std::endl;
        std::cout << "1. First picture" << std::endl;
        std::cout << "2. Second picture" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cin >> num;
        switch (num){
            case 1:
                menu(pic1, pic2);
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
*/

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
                select_pic();
                break;
            }
            case 2:{
                select_pic();
                break;
            }
            case 3:{
                select_pic();
                break;
            }
            case 0:{
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


int main(){

    return 0;
}
