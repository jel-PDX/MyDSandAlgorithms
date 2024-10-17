/// Merge Sort
//
// By: James Lawrance
// Date: 6/27/23
//
/// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

#include <catch2/catch_test_macros.hpp>

#include "MergeSort.h"

void matchLists(int arr[], int sorted_arr[], int len) {
  for (int i{}; i < len; ++i) {
    CHECK(arr[i] == sorted_arr[i]);
  }
}

TEST_CASE("Single Item Array") {
  int arr[]{2};
  int sorted_arr[]{2};
  mergeSort(arr, 1);
  matchLists(arr, sorted_arr, 1);
}

TEST_CASE("Multiple Item Array 1") {
  int arr[]{5, 8, 1, 2};
  int sorted_arr[]{1, 2, 5, 8};
  mergeSort(arr, 4);
  matchLists(arr, sorted_arr, 4);
}

TEST_CASE("Multiple Item Array 2") {
  int arr[]{9, 8, 7, 6, 5, 4, 3, 2, 1};
  int sorted_arr[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
  mergeSort(arr, 9);
  matchLists(arr, sorted_arr, 9);
}
