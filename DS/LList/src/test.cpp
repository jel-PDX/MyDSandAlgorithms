/// Singly Linked List
//
// By: James Lawrance
// Date: 6/27/23
//
/// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

#include <catch2/catch_test_macros.hpp>

#include "LList.cpp"
#include "Node.cpp"

Node<int> n{};
LList<int> l{};

TEST_CASE("Node Default Constructor") {
  REQUIRE(n.data() == 0);
  REQUIRE(n.next() == nullptr);
}

TEST_CASE("Node Paramaterized Constructor") {
  Node<int> n1{5};
  SECTION("Pass one argument, second argument defaults") {
    REQUIRE(n1.data() == 5);
    REQUIRE(n1.next() == nullptr);
  }

  Node<int> n2{5, &n1};
  SECTION("Pass both arguments") {
    REQUIRE(n2.data() == 5);
    REQUIRE(n2.next() == &n1);
  }
}

TEST_CASE("Node Set Data") {
  n.setData(5);
  REQUIRE(n.data() == 5);
  REQUIRE(n.next() == nullptr);
}

TEST_CASE("Node Set Next") {
  Node<int> n2{};
  n.setNext(&n2);
  REQUIRE(n.next() == &n2);
}

TEST_CASE("LList Default Constructor") {
  REQUIRE(l.head() == nullptr);
  REQUIRE(l.length() == 0);
}

TEST_CASE("LList Paramaterized Constructor") {
  Node<int> n{};
  LList<int> l1{&n};
  SECTION("Pass Address of Node") {
    REQUIRE(l1.head() == &n);
    REQUIRE(l1.length() == 1);
  }

  LList<int> l2{nullptr};
  SECTION("Pass Nullptr") {
    REQUIRE(l2.head() == nullptr);
    REQUIRE(l2.length() == 0);
  }
}

TEST_CASE("LList Operations") {
  Node<int> n5{5};
  Node<int> n4{4, &n5};
  Node<int> n3{3, &n4};
  Node<int> n2{2, &n3};
  Node<int> n1{1, &n2};

  Node<int> n{};

  LList<int> l1{&n};
  LList<int> l2{&n1};
  LList<int> l3{};

  SECTION("Set Head") {
    l1.setHead(&n1);
    REQUIRE(l1.head() == &n1);
    REQUIRE(l1.length() == 5);
  }

  SECTION("Push Front Empty List") {
    l3.push_front(1);
    REQUIRE(l3.head()->data() == 1);
    REQUIRE(l3.length() == 1);
  }

  SECTION("Push Front Multiple Element List") {
    l2.push_front(0);
    l2.push_front(-1);
    REQUIRE(l2.head()->data() == -1);
    REQUIRE(l2.length() == 7);
  }

  SECTION("Push Back Empty List") {
    l3.push_back(1);
    REQUIRE(l3.head()->data() == 1);
    REQUIRE(l3.length() == 1);
  }

  SECTION("Push Back Multiple Element List") {
    l2.push_back(6);
    l2.push_back(7);
    REQUIRE(l2.head() == &n1);
    REQUIRE(l2.length() == 7);
  }

  SECTION("Pop Front Empty List") { REQUIRE_THROWS(l3.pop_front()); }

  SECTION("Pop Front Multiple Element List") {
    int data1 = l2.pop_front();
    int data2 = l2.pop_front();
    REQUIRE(l2.head() == &n3);
    REQUIRE(l2.length() == 3);
    REQUIRE(data1 == 1);
    REQUIRE(data2 == 2);
  }

  SECTION("Pop Back Empty List") { REQUIRE_THROWS(l3.pop_back()); }

  SECTION("Pop Back Multiple Element List") {
    int data1 = l2.pop_back();
    int data2 = l2.pop_back();
    REQUIRE(l2.head() == &n1);
    REQUIRE(l2.length() == 3);
    REQUIRE(data1 == 5);
    REQUIRE(data2 == 4);
  }
}
