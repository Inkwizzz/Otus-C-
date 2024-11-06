#include "lib.h"
#include <iostream>

int main(int, char **) {
    std::cout << "version: " << version() << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
