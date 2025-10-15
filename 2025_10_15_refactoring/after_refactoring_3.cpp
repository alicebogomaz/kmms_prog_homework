#include <cmath>
#include <cstdlib>
#include <iostream>

int main()
{
    const int size = 20;
	int arr[size];
	std::cout << "Изначальный массив: ";
	for (int i = 0; i < size; i++)
    {
        arr[i] = std::rand() % size;
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
    
	
	for (int i = 0; i < size / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1- i] = temp;
    }
    
	std::cout << "Перевёрнутый массив: ";
	for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << ' ';
    }
	
    return 0;
}