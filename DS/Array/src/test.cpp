/// Static and Dynamic Array
//
// By: James Lawrance
// Date: 6/27/23
//
/// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

#include <catch2/catch_test_macros.hpp>

#include "dArray.cpp"
#include "sArray.cpp"

TEST_CASE("Default Constructor", "[sArray]") {
  sArray<int> arr1{};
  REQUIRE(arr1.length() == 0);
}

TEST_CASE("Paramaterized Constructor", "[sArray]") {
  SECTION("Initialize with Single Item") {
    sArray<int> arr1{3};
    REQUIRE(arr1.length() == 1);
    REQUIRE(arr1[0] == 3);
  }
  SECTION("Initialize with Initializer List of Items") {
    sArray<int> arr1{3, 4, 5, 6, 7, 8};
    REQUIRE(arr1.length() == 6);
    REQUIRE(arr1[0] == 3);
    REQUIRE(arr1[1] == 4);
    REQUIRE(arr1[2] == 5);
    REQUIRE(arr1[3] == 6);
    REQUIRE(arr1[4] == 7);
    REQUIRE(arr1[5] == 8);
  }
}

TEST_CASE("Default Constructor", "[dArray]") {
  dArray<int> arr1{};
  REQUIRE(arr1.length() == 0);
}

TEST_CASE("Paramaterized Constructor", "[dArray]") {
  SECTION("Initialize with Single Item") {
    dArray<int> arr1{3};
    REQUIRE(arr1.length() == 1);
    REQUIRE(arr1[0] == 3);
  }
  SECTION("Initialize with Initializer List of Items") {
    dArray<int> arr1{3, 4, 5, 6, 7, 8};
    REQUIRE(arr1.length() == 6);
    REQUIRE(arr1[0] == 3);
    REQUIRE(arr1[1] == 4);
    REQUIRE(arr1[2] == 5);
    REQUIRE(arr1[3] == 6);
    REQUIRE(arr1[4] == 7);
    REQUIRE(arr1[5] == 8);
  }
}

TEST_CASE("Resize dArray Buffer", "[dArray]") {
  dArray<int> arr1{};
  arr1.resize(5);
  REQUIRE(arr1.length() == 5);
}

TEST_CASE("dArray Push", "[dArray]") {
  SECTION("Push Single Items") {
    dArray<int> arr1{};
    arr1.push(1);
    REQUIRE(arr1.length() == 1);
    REQUIRE(arr1[0] == 1);
    arr1.push(2);
    REQUIRE(arr1.length() == 2);
    REQUIRE(arr1[0] == 1);
    REQUIRE(arr1[1] == 2);
    arr1.push(3);
    REQUIRE(arr1.length() == 3);
    REQUIRE(arr1[0] == 1);
    REQUIRE(arr1[1] == 2);
    REQUIRE(arr1[2] == 3);
  }
  SECTION("Push Initializer Lists of Items") {
    dArray<int> arr1{};
    arr1.push({1, 2, 3});
    REQUIRE(arr1.length() == 3);
    REQUIRE(arr1[0] == 1);
    REQUIRE(arr1[1] == 2);
    REQUIRE(arr1[2] == 3);
    arr1.push({4, 5, 6});
    REQUIRE(arr1.length() == 6);
    REQUIRE(arr1[0] == 1);
    REQUIRE(arr1[1] == 2);
    REQUIRE(arr1[2] == 3);
    REQUIRE(arr1[3] == 4);
    REQUIRE(arr1[4] == 5);
    REQUIRE(arr1[5] == 6);
  }
}

TEST_CASE("dArray Pop", "[dArray]") {
  SECTION("Pop Single Items") {
    dArray<int> arr1{1, 2, 3};
    REQUIRE(arr1.pop() == 3);
    REQUIRE(arr1.length() == 2);
    REQUIRE(arr1.pop() == 2);
    REQUIRE(arr1.length() == 1);
    REQUIRE(arr1.pop() == 1);
    REQUIRE(arr1.length() == 0);
  }
  SECTION("Pop Initializer Lists of Items") {
    dArray<int> arr1{1, 2, 3, 4, 5, 6};
    int* list = arr1.pop(3);
    REQUIRE(list[0] == 6);
    REQUIRE(list[1] == 5);
    REQUIRE(list[2] == 4);
    REQUIRE(arr1.length() == 3);
    list = arr1.pop(3);
    REQUIRE(list[0] == 3);
    REQUIRE(list[1] == 2);
    REQUIRE(list[2] == 1);
    REQUIRE(arr1.length() == 0);
  }
}
