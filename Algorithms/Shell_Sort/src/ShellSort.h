void shift(int *list, int left_bound, int right_bound, int gap_size) {
  for (int i{right_bound}; i >= left_bound; i -= gap_size) {
    list[i + gap_size] = list[i];
  }
}
void gappedInsertion(int *sublist, int gap_size, int len) {
  for (int i{}; i < len; i += gap_size) {
    for (int j{}; j != i; j += gap_size) {
      if (sublist[j] > sublist[i]) {
        int temp{sublist[i]};
        shift(sublist, j, i - gap_size, gap_size);
        sublist[j] = temp;
        break;
      }
    }
  }
}
void shellSort(int arr[], int len) {
  int gap_size{len / 2};
  while (gap_size > 0) {
    for (int i{}; i < gap_size; ++i)
      gappedInsertion(&arr[i], gap_size, len - i);

    gap_size = (gap_size / 2);
  }
}
