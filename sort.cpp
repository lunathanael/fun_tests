#include <iostream>
#include <algorithm>

using namespace std;


bool verify_array(int* first, int* last) {
	int prev = *first;
	int* i = first + 1;
	while (i < last) {
		if (*i < prev) {
			return false;
		}
		prev = *i;
		++i;
	}
	return true;
}

template<typename CMP>
bool verify_array(int* first, int* last, CMP cmp) {
	int prev = *first;
	int* i = first + 1;
	while (i < last) {
		if (cmp(*i, prev)) {
			return false;
		}
		prev = *i;
		++i;
	}
	return true;
}

void insertion_sort(int* first, int* last) {
	int key;
	int* i; int* j;
	for (i = first + 1; i < last; ++i) {
		key = *i;
		j = i - 1;
		while (j >= first && key < *j) {
			*(j + 1) = *j;
			--j;
		}
		*(j + 1) = key;
	}
}

template<typename CMP>
void insertion_sort(int* first, int* last, CMP cmp) {
	int key;
	int* i; int* j;
	for (i = first + 1; i < last; ++i) {
		key = *i;
		j = i - 1;
		while (j >= first && cmp(key, *j)) {
			*(j + 1) = *j;
			--j;
		}
		*(j + 1) = key;
	}
}

void quick_sort(int* first, int* last) {
	if (first < last) {
		int pivot = *first;
		int* i = first; int* j = first + 1;
		while (j < last) {
			if (*j < pivot) {
				++i;
				int temp = *i;
				*i = *j;
				*j = temp;
			}
			++j;
		}
		int temp = *i;
		*i = *first;
		*first = temp;
		quick_sort(first, i);
		quick_sort(i + 1, last);
	}
	return;
}

template<typename CMP>
void quick_sort(int* first, int* last, CMP cmp) {
	if (first < last) {
		int pivot = *first;
		int* i = first; int* j = first + 1;
		while (j < last) {
			if (cmp(*j, pivot)) {
				++i;
				int temp = *i;
				*i = *j;
				*j = temp;
			}
			++j;
		}
		int temp = *i;
		*i = *first;
		*first = temp;
		quick_sort(first, i, cmp);
		quick_sort(i + 1, last, cmp);
	}
	return;
}

void radix_sort(int* first, int* last) {
	int largest_number = 0;
	for (int* i = first; i < last; ++i) {
		largest_number = max(*i, largest_number);
		largest_number = max(-(*i), largest_number);
	}
	int digits = 1;
	while (largest_number != 0) {
		largest_number /= 10;
		insertion_sort(first, last, [digits](int i, int j) {
			int a = ((i / digits) % 10);
			int b = ((j / digits) % 10);
			return (a < b);
		});
		digits *= 10;
	}
}

template<typename CMP>
void radix_sort(int* first, int* last, CMP cmp) {
	int largest_number = 0;
	for (int* i = first; i < last; ++i) {
		largest_number = max(*i, largest_number);
		largest_number = max(-(*i), largest_number);
	}
	int digits = 1;
	while (largest_number != 0) {
		largest_number /= 10;
		insertion_sort(first, last, [&digits, &cmp](int i, int j) {
			int a = ((i / digits) % 10);
			int b = ((j / digits) % 10);
			return cmp(a,b);
			});
		digits *= 10;
	}
}

auto desc = [](int i, int j) {
	return i > j;
};


constexpr int arr0[] = { 3, 5, 4, 2, 6, 1 };
constexpr int arr1[] = { 102, 3982, 1958, -193, 295, 20189, 295, -2959, 0, 2429, 19583, 20481, 230, 934, 2058 };
constexpr int arr2[] = { 2, 3, 2, 0, 0, 0, 2, 0, 2, 1, 3, 4 };


int main() {

	int target[] = { 102, 3982, 1958, -193, 295, 20189, 295, -2959, 0, 2429, 19583, 20481, 230, 934, 2058, -100000};

	for (int i : target) {
		cout << i << ' ';
	}
	cout << '\n';
	int N = sizeof(target) / sizeof(target[0]);
	quick_sort(target, target + N, desc);
	radix_sort(target, target + N, desc);


	for (int i : target) {
		cout << i << ' ';
	}
	cout << '\n';
	if (verify_array(target, target + N)) {
		cout << "Ascending order sorted.\n";
	}
	else {
		if (verify_array(target, target + N, desc) {
			cout << "Descending order sorted.\n";
		}
		else {
			cout << "Failed.\n";
		}
	}
	return 0;
}