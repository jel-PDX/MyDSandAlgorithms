/// Stack
//
// By: James Lawrance
// Date: 6/27/23
//
/// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

#include <catch2/catch_test_macros.hpp>

#include "Stack.cpp"

TEST_CASE("Stack Default Constructor") { CHECK(1 == 1); }

TEST_CASE("Stack Paramaterized Constructor") {
  SECTION("Construct with Single Item") {
    Stack<int> s{1};

    CHECK(s.length() == 1);
  }

  SECTION("Construct with Initializer List of Items") {
    Stack<int> s{1, 2, 3, 4, 5};

    CHECK(s.length() == 5);
  }
}

TEST_CASE("Stack Operations") {
  SECTION("Push on Empty Stack") {
    Stack<int> s{};

    s.push(1);

    CHECK(s.length() == 1);
  }

  SECTION("Push on Non-Empty Stack") {
    Stack<int> s{1, 2};

    s.push(3);

    CHECK(s.length() == 3);
  }

  SECTION("Pop on Empty Stack") {
    Stack<int> s{};

    CHECK_THROWS(s.pop());
  }

  SECTION("Pop on Stack with 1 Element") {
    Stack<int> s{1};

    int data1{s.pop()};
    REQUIRE(data1 == 1);
    REQUIRE(s.length() == 0);
  }

  SECTION("Pop on Non-Empty Stack") {
    Stack<int> s{1, 2, 3};

    int data1{s.pop()};
    int data2{s.pop()};
    int data3{s.pop()};

    CHECK(data1 == 3);
    CHECK(data2 == 2);
    CHECK(data3 == 1);
    CHECK(s.length() == 0);
  }
}
