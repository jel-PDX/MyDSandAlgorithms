/// Shell Sort
//
// By: James Lawrance
// Date: 6/27/23
//
/// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

#include <catch2/catch_test_macros.hpp>

#include "ShellSort.h"

void matchLists(int actual_arr[], int expected_arr[], int len) {
  for (int i{}; i < len; ++i) CHECK(actual_arr[i] == expected_arr[i]);
}

TEST_CASE("Single Item List") {
  int arr[]{2};
  int sorted_arr[]{2};
  shellSort(arr, 1);
  matchLists(arr, sorted_arr, 1);
}

TEST_CASE("Multiple Item List, 2^x Number of Items") {
  int arr[]{5, 8, 1, 2, 7, 3, 5, 1, 7, 9, 11, 2, 0, 4, 2, 7};
  int sorted_arr[]{0, 1, 1, 2, 2, 2, 3, 4, 5, 5, 7, 7, 7, 8, 9, 11};
  shellSort(arr, 16);
  matchLists(arr, sorted_arr, 16);
}

TEST_CASE("Multiple Item List, Not 2^x Number of Items") {
  int arr[]{6, 2, 6, 1, 3, 9, 4, 2, 4, 2, 0};
  int sorted_arr[]{0, 1, 2, 2, 2, 3, 4, 4, 6, 6, 9};
  shellSort(arr, 11);
  matchLists(arr, sorted_arr, 11);
}
