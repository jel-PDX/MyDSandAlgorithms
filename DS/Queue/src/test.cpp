/// Queue with Circular Buffer
//
// By: James Lawrance
// Date: 6/27/23
//
/// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

#include <catch2/catch_test_macros.hpp>

#include "Queue.cpp"

TEST_CASE("Default Constructor") {
  Queue<int> q{};

  CHECK(q.isEmpty() == true);
  CHECK(q.bufferLength() == 0);
}

TEST_CASE("Paramaterized Constructor") {
  SECTION("Initialize with Single Item, Default Length") {
    Queue<int> q{1};

    CHECK(q.peekRear() == 1);
    CHECK(q.numElements() == 1);
    CHECK(q.bufferLength() == 10);
  }
  SECTION(
      "Initialize with Single Item, Pass in Length Greater than Number of "
      "Elements") {
    Queue<int> q({1}, 5);  // If you want to pass a single item and a length,
                           // you must use this bizarre syntax

    CHECK(q.peekRear() == 1);
    CHECK(q.numElements() == 1);
    CHECK(q.bufferLength() == 5);
  }

  SECTION(
      "Initialize with Single Item, Pass in Length Less than Number of "
      "Elements (i.e. Invalid Length)") {
    REQUIRE_THROWS(Queue<int>(1, 0));
  }

  SECTION(
      "Initialize with Initializer List of Items, Default Length (len = 10 "
      "+ (n elements past 1))") {
    Queue<int> q1{{1, 2}};

    CHECK(q1.peekRear() == 2);
    CHECK(q1.numElements() == 2);
    CHECK(q1.bufferLength() == 11);

    Queue<int> q2{{1, 2, 3}};

    CHECK(q2.peekRear() == 3);
    CHECK(q2.numElements() == 3);
    CHECK(q2.bufferLength() == 12);

    Queue<int> q3{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

    CHECK(q3.peekRear() == 10);
    CHECK(q3.numElements() == 10);
    CHECK(q3.bufferLength() == 19);
  }

  SECTION(
      "Initialize with Initializer List of Items, Pass in Length Greater "
      "than Number of Elements") {
    Queue<int> q{{1, 2, 3, 4, 5}, 20};

    CHECK(q.peekRear() == 5);
    CHECK(q.numElements() == 5);
    CHECK(q.bufferLength() == 20);
  }

  SECTION(
      "Initialize with Initializer List of Items, Pass in Length Less than "
      "Number of Elements (i.e. Invalid Length)") {
    REQUIRE_THROWS(Queue<int>({1, 2, 3, 4, 5}, 4));
  }
}

TEST_CASE("Enqueue") {
  SECTION("Enqueue on Non-Empty Queue") {
    Queue<int> q{{1, 2, 3}};

    q.enqueue(4);

    CHECK(q.peekRear() == 4);
    CHECK(q.numElements() == 4);
    CHECK(q.bufferLength() == 12);
  }

  SECTION("Enqueue on Queue with bufferLength == 0") {
    Queue<int> q{};

    REQUIRE_THROWS(q.enqueue(1));
  }

  SECTION("Enqueue on Full Queue (numElements == bufferLength)") {
    Queue<int> q{{1, 2, 3}, 3};

    REQUIRE_THROWS(q.enqueue(4));
  }
}

TEST_CASE("Dequeue") {
  SECTION("Dequeue on Non-Empty Queue") {
    Queue<int> q{{1, 2, 3}};

    int data{q.dequeue()};

    CHECK(data == 1);
    CHECK(q.peekFront() == 2);
    CHECK(q.numElements() == 2);
    CHECK(q.bufferLength() == 12);
  }

  SECTION("Dequeue on Queue with bufferLength == 0") {
    Queue<int> q{};

    REQUIRE_THROWS(q.dequeue());
  }

  SECTION("Dequeue on Queue with numElements == 0, but bufferLength != 0") {
    Queue<int> q{1};

    q.dequeue();
    REQUIRE_THROWS(q.dequeue());  // numElements == 0, exception should occur
  }
}

TEST_CASE("Set Buffer Length") {
  Queue<int> q{1, 2, 3, 4, 5};
  SECTION("Set Greater than numElements, Greater than Old Buffer Length") {
    q.setBufferLength(15);
    CHECK(q.bufferLength() == 15);
    CHECK(q.numElements() == 5);
    CHECK(q.peekFront() == 1);
    CHECK(q.peekRear() == 5);
  }

  SECTION("Set Greater than numElements, Less than Old Buffer Length") {
    q.setBufferLength(8);
    CHECK(q.bufferLength() == 8);
    CHECK(q.numElements() == 5);
    CHECK(q.peekFront() == 1);
    CHECK(q.peekRear() == 5);
  }

  SECTION("Set Less than numElements") { REQUIRE_THROWS(q.setBufferLength(3)); }

  SECTION("Set to zero") { REQUIRE_THROWS(q.setBufferLength(0)); }

  SECTION("Set to Negative Length") { REQUIRE_THROWS(q.setBufferLength(-1)); }

  SECTION("Set same as numElements") {
    q.setBufferLength(10);
    CHECK(q.bufferLength() == 10);
    CHECK(q.numElements() == 5);
    CHECK(q.peekFront() == 1);
    CHECK(q.peekRear() == 5);
  }
}

TEST_CASE("Circular Buffer Test") {
  SECTION("Enqueue when Rear Pointer is at end of Buffer (buffer[9])") {
    Queue<int> q{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10};  // full queue

    q.dequeue();    // front pointer moves from buffer[0] to buffer[1]
    q.enqueue(11);  // rear pointer must move from buffer[9] to buffer[0]

    // 11, 2, 3, 4, 5, 6, 7, 8, 9
    // ^   ^
    // R   F

    CHECK(q.numElements() == 10);
    CHECK(q.bufferLength() == 10);
    CHECK(q.peekFront() == 2);
    CHECK(q.peekRear() == 11);
  }

  SECTION("Dequeue when Front Pointer is at end of Buffer (buffer[2])") {
    Queue<int> q{{1, 2}, 3};

    q.enqueue(3);  // queue is full
    q.dequeue();   // front pointer moves from buffer[0] to buffer[1]
    q.enqueue(4);  // rear pointer moves from buffer[2] to buffer[0]
    q.dequeue();   // front pointer moves from buffer[1] to buffer[2]
    q.dequeue();   // front pointer must move from buffer[2] to buffer[0]

    // 4, -, -
    // ^
    // R
    // F

    CHECK(q.numElements() == 1);
    CHECK(q.bufferLength() == 3);
    CHECK(q.peekFront() == 4);
    CHECK(q.peekRear() == 4);
  }

  SECTION(
      "Set Buffer Length when Front Pointer Reaches end of "
      "Buffer (buffer[2]) during Copy") {
    Queue<int> q{{1, 2}, 3};

    q.enqueue(3);  // queue is full
    q.dequeue();   // front pointer moves from buffer[0] to buffer[1]
    q.enqueue(4);  // rear pointer moves from buffer[2] to buffer[0]

    // 4, 2, 3
    // ^  ^
    // R  F

    q.setBufferLength(4);  // front pointer needs to go from 2 to 3 to 4
                           // jump from 3 to 4 must execute properly

    CHECK(q.numElements() == 3);
    CHECK(q.bufferLength() == 4);
    CHECK(q.peekFront() == 2);
    CHECK(q.peekRear() == 4);
  }
}
