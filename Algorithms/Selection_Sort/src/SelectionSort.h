void swap(int &a, int &b) {
  int temp{a};
  a = b;
  b = temp;
}
void selectionSort(int arr[], int len) {
  int end_index{len};
  for (int i{}; i < end_index; ++i) {
    int min{i};
    for (int j{i}; j < end_index; ++j) {
      if (arr[j] < arr[min])
        min = j;
    }
    swap(arr[min], arr[i]);
  }
}
