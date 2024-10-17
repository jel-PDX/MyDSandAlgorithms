/// Bubble Sort
//
// By: James Lawrance
// Date: 6/27/23
//
/// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "BubbleSort.h"

void matchLists(int actual_arr[], int expected_arr[], int len) {
  for (int i{}; i < len; ++i) {
    CHECK(actual_arr[i] == expected_arr[i]);
  }
}

TEST_CASE("Single Item List") {
  int arr[]{2};
  int sorted_arr[]{2};
  bubbleSort(arr, 1);
  matchLists(arr, sorted_arr, 1);
}

TEST_CASE("Multiple Item List 1") {
  int arr[]{5, 8, 1, 2};
  int sorted_arr[]{1, 2, 5, 8};
  bubbleSort(arr, 4);
  matchLists(arr, sorted_arr, 4);
}

TEST_CASE("Multiple Item List 2") {
  int arr[]{9, 8, 7, 6, 5, 4, 3, 2, 1};
  int sorted_arr[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
  bubbleSort(arr, 9);
  matchLists(arr, sorted_arr, 9);
}
