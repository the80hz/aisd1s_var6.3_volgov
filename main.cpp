#include <iostream>
#include "bin_pic.h"

void menu(int i, bin_pic &pic1, bin_pic &pic2){
    while(true){
        bin_pic pic3(0, 0);
        std::cout << "1. Create a circle" << std::endl;
        std::cout << "2. Print a picture" << std::endl;
        std::cout << "3. Invert a picture" << std::endl;
        std::cout << "4. Add two pictures" << std::endl;
        std::cout << "5. Subtract two pictures" << std::endl;
        std::cout << "6. Multiply two pictures" << std::endl;
        std::cout << "7. Fill ratio" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cin >> i;
        switch(i){
            case 1:{
                int x, y, radius;
                std::cout << "Enter the coordinates of the center and the radius of the circle" << std::endl;
                std::cin >> x >> y >> radius;
                bin_pic::draw_circle(pic1, x, y, radius);
                break;
            }
            case 2:{
                pic1.print();
                break;
            }
            case 3:{
                // ! function
                pic1 = pic1.invert();
                break;
            }
            case 4:{
                pic1 = pic1 + pic2;
                break;
            }
            case 5:{
                pic3 = pic1 - pic2;
                break;
            }
            case 6:{
                pic3 = pic1 * pic2;
                break;
            }
            case 7:{
                std::cout << pic1.fill_ratio() << std::endl;
                break;
            }
            case 9:{
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

void select_pic(int i) {
    int x, y;

    std::cout << "Create a first picture" << std::endl;
    std::cout << "Enter the size of the picture" << std::endl;
    std::cin >> x >> y;
    bin_pic pic1(x, y);

    std::cout << "Enter the second picture" << std::endl;
    std::cout << "Enter the size of the picture" << std::endl;
    std::cin >> x >> y;
    bin_pic pic2(x, y);

    bin_pic pic3(0, 0);

    int num;

    while(true){
        std::cout << "Select picture" << std::endl;
        std::cout << "1. First picture" << std::endl;
        std::cout << "2. Second picture" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cin >> num;
        switch (num) {
            case 1:
                menu(i, pic1, pic2);
                break;
            case 2:
                menu(i, pic2, pic1);
                break;
            case 3:
                return;

            default:
                std::cout << "Wrong number" << std::endl;
                break;
        }

    }

}
int main(){
    int i = 0;

    select_pic(i);

    return 0;
}
