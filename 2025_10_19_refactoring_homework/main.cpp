#include "io.hpp"
#include "sortings.hpp"

int main() {
	int arr_size = 6;
    int* arr = new int[]{1, 8, 2, 5, 3, 11};
	
	print::print_array("Массив до сортировки:", arr, arr_size);
    sort::mergeSort(arr, 0, arr_size - 1);
    print::print_array("Массив после сортировки:", arr, arr_size);

    return 0;
}
