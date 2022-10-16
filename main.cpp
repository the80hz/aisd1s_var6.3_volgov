#include <iostream>
#include "bin_pic.h"


int main() {
    bin_pic pic1(7, 7);
    bin_pic::draw_circle(pic1, 3, 3, 2);
    std::cout << pic1 << std::endl;
    bin_pic pic2(7, 7);
    bin_pic::draw_circle(pic2, 1, 1, 3);
    std::cout << pic2 << std::endl;
    bin_pic pic3 = pic1 + pic2;
    std::cout << pic3 << std::endl;
    return 0;
}
