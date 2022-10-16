#include <iostream>
#include "bin_pic.h"


int main() {
    bin_pic pic1(7, 7);
    bin_pic::draw_circle(pic1, 3, 3, 2);
    std::cout << pic1 << std::endl;
    std::cout << pic1.fill_ratio();
    return 0;
}
