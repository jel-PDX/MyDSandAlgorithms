void merge(int arr[], int l, int m, int r) {
  int i = l, j = m + 1, k = l;
  int temp[r + 1]{};
  while (i <= m && j <= r) {
    if (arr[i] <= arr[j]) {
      temp[k] = arr[i];
      i++;
    } else {
      temp[k] = arr[j];
      j++;
    }
    k++;
  }
  while (i <= m) {
    temp[k] = arr[i];
    i++, k++;
  }
  while (j <= r) {
    temp[k] = arr[j];
    j++, k++;
  }
  for (int p = l; p <= r; p++)
    arr[p] = temp[p];
}
void mergeSortRecursive(int arr[], int l, int r) {
  if (l < r) {
    int m{(l + r) / 2};
    mergeSortRecursive(arr, l, m);
    mergeSortRecursive(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}
void mergeSort(int arr[], int len) { mergeSortRecursive(arr, 0, len - 1); }
