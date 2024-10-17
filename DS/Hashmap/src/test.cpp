/// Hashmap with Linear Probing Collision Handling
//
// By: James Lawrance
// Date: 6/27/23
//
/// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

#include <catch2/catch_test_macros.hpp>
#include <string>

#include "Hashmap.cpp"
#include "Slot.cpp"

using std::string;

TEST_CASE("Slot") {
  Slot<string, int> s{};
  Slot<string, int> s2{"key1", 1};

  CHECK(s.key() == "");
  CHECK(s2.key() == "key1");
  CHECK(s.val() == 0);
  CHECK(s2.val() == 1);

  s.setSlot("key2", 2);

  CHECK(s.key() == "key2");
  CHECK(s.val() == 2);

  s.clearSlot();

  CHECK(s.key() == "");
  CHECK(s.val() == 0);
  CHECK(s.isClear() == true);
}

TEST_CASE("Default Constructor") {
  Hashmap<string, int> h{};

  CHECK(h.isEmpty() == true);
}

TEST_CASE("Paramaterized Constructor") {
  SECTION("Single Slot Initialization") {
    Hashmap<string, int> h({"key1", 1});

    CHECK(h.size() == 1);
    CHECK(h["key1"] == 1);
  }
  SECTION("Initializer List Initialization") {
    Hashmap<string, int> h{{"key1", 1}, {"key2", 2}, {"key3", 3}};

    CHECK(h.size() == 3);
    CHECK(h["key1"] == 1);
    CHECK(h["key2"] == 2);
    CHECK(h["key3"] == 3);
  }
}

TEST_CASE("Add Operation") {
  SECTION("Add on Empty Hashmap") {
    Hashmap<string, int> h{};

    h.add({"key1", 1});

    CHECK(h.size() == 1);
    CHECK(h["key1"] == 1);
  }
  SECTION("Add on Non-Empty Hashmap, no rehash") {
    Hashmap<string, int> h{{"key1", 1}, {"key2", 2}, {"key3", 3}};

    h.add({"key4", 4});

    CHECK(h.size() == 4);
    CHECK(h["key1"] == 1);
    CHECK(h["key2"] == 2);
    CHECK(h["key3"] == 3);
    CHECK(h["key4"] == 4);
  }
  SECTION("Add Key that already Exists") {
    Hashmap<string, int> h{{"key1", 1}, {"key2", 2}, {"key3", 3}};

    REQUIRE_THROWS(h.add({"key2", 5}));
  }
}

TEST_CASE("Remove Operation") {
  SECTION("Remove on Empty Hashmap") {
    Hashmap<string, int> h{};

    REQUIRE_THROWS(h.remove("key1"));
  }
  SECTION("Remove on Non-Empty Hashmap") {
    Hashmap<string, int> h{{"key1", 1}, {"key2", 2}, {"key3", 3}};

    h.remove("key2");

    CHECK(h.size() == 2);
    CHECK(h["key1"] == 1);
    CHECK(h["key3"] == 3);
  }
  SECTION("Remove Non-Existant Key") {
    Hashmap<string, int> h{{"key1", 1}, {"key2", 2}, {"key3", 3}};

    REQUIRE_THROWS(h.remove("key4"));
  }
}

TEST_CASE("Subscript Operator") {
  Hashmap<string, int> h{{"key1", 1}, {"key2", 2}, {"key3", 3}};

  SECTION("Reading from Key") {
    CHECK(h["key1"] == 1);
    CHECK(h["key2"] == 2);
    CHECK(h["key3"] == 3);
  }
  SECTION("Reading from Non-Existant Key") {
    // Creates Slot with given Key, sets Value to Default of Type
    CHECK(h["key4"] == 0);
  }
  SECTION("Writing to Key") {
    h["key2"] = 5;

    CHECK(h["key2"] == 5);
  }
  SECTION("Writing to Non-Existant Key") {
    h["key4"] = 4;

    CHECK(h["key4"] == 4);
  }
}

TEST_CASE("Collision Handling & Linear Probing") {
  SECTION("Non-Circular Collision Handling") {
    Hashmap<string, int> h({"cat", 3});  // 312 % 16 = 8
    // First collision
    h.add({"meow", 4});  // 440 % 16 = 8

    CHECK(h.size() == 2);
    CHECK(h["cat"] == 3);
    CHECK(h["meow"] == 4);  // Has to look to next slot to find the "meow" key

    // Second collision, occuring at same index
    // (has to look two slots ahead for open slot)
    h.add({"woem", 4});  // 440 % 16 = 8

    CHECK(h.size() == 3);
    CHECK(h["cat"] == 3);
    CHECK(h["meow"] == 4);
    CHECK(h["woem"] == 4);
  }
  SECTION("Circular Collision Handling") {
    Hashmap<string, int> h({"o", 1});  // 111 % 16 = 15
    h.add({"op", 2});  // 223 % 16 = 15 (collision at end of slot array), goes
                       // to hash index 1
    CHECK(h.size() == 2);
    CHECK(h["o"] == 1);
    CHECK(h["op"] == 2);
  }
  SECTION(
      "Locating and Removing a Slot that Underwent Non-Circular Collision "
      "(Located away from its Home Index)") {
    Hashmap<string, int> h{{"cat", 3}, {"meow", 4}, {"woem", 4}};
    h.remove("woem");

    CHECK(h.size() == 2);
    CHECK(h["cat"] == 3);
    CHECK(h["meow"] == 4);
    // Check that it's creating a new "woem" key with a default value, as
    // opposed to using the one that should be removed
    CHECK(h["woem"] == 0);
  }
  SECTION(
      "Locating and Removing a Slot that Underwent Circular Collision "
      "(Located away from its Home Index)") {
    Hashmap<string, int> h{{"o", 1}, {"op", 2}};
    h.remove("op");

    CHECK(h.size() == 1);
    CHECK(h["o"] == 1);
  }
}

TEST_CASE("Rehashing") {}
