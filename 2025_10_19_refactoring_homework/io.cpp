#include "io.hpp"
#include <iostream>

void print::print_array(const char* const comment, const int* arr, int size) {
    std::cout << comment;
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;	
}
