#ifndef SORTINGS_HPP
#define SORTINGS_HPP

#include <vector>

namespace biv {
	namespace sortings {
		void merge(std::vector<int>& arr, int left, int mid, int right);
		void mergeSort(std::vector<int>& arr, int left, int right);
	}
}

#endif
