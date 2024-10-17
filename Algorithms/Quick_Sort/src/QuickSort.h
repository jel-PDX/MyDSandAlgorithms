void swap(int &a, int &b) {
  int temp{a};
  a = b;
  b = temp;
}
int partition(int arr[], int l, int r) {
  int pivot{arr[r]};

  int i{l};
  int j{r};

  while (i < j) {
    while (!(arr[i] >= pivot))
      i++;
    while (j >= 0 && !(arr[j] < pivot))
      j--;
    if (i < j)
      swap(arr[i], arr[j]);
  }

  swap(arr[i], arr[r]);
  return j;
}
void quickSortRecursive(int arr[], int l, int r) {
  if (l < r) {
    int p{partition(arr, l, r)};
    quickSortRecursive(arr, l, p);
    quickSortRecursive(arr, p + 1, r);
  }
}
void quickSort(int arr[], int len) { quickSortRecursive(arr, 0, len - 1); }
