#include <iostream>

void shift(int arr[], int left_bound, int right_bound) {
  for (int i{right_bound}; i >= left_bound; --i)
    arr[i + 1] = arr[i];
}

void insertionSort(int arr[], int len) {
  for (int i{}; i < len; ++i) {
    for (int j{}; j != i; ++j) {
      if (arr[j] > arr[i]) {
        int temp{arr[i]};
        shift(arr, j, i - 1);
        arr[j] = temp;
        break;
      }
    }
  }
}
