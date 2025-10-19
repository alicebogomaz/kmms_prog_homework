#include "io.hpp"
#include "sortings.hpp"

#include <vector>

int main() {

    std::vector<int> arr = {1, 8, 2, 5, 3, 11};
	
	const int arr_size = sizeof(arr) / sizeof(arr[0]);
	
	biv::print_array("Массив до сортировки:", arr, arr_size);
    
    biv::sortings::mergeSort(arr, 0, arr.size() - 1);

    biv::print_array("Массив после сортировки:", arr, arr_size);

    return 0;
}
