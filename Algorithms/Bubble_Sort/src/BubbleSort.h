void swap(int &a, int &b) {
  int temp{a};
  a = b;
  b = temp;
}
void bubbleSort(int arr[], int len) {
  int end_index{len - 1};
  for (int i{}; i < end_index; ++i) {
    for (int j{}; j < end_index - i; ++j)
      if (arr[j] > arr[j + 1])
        swap(arr[j], arr[j + 1]);
  }
}
