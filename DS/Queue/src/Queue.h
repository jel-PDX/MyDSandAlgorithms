#include <initializer_list>
#include <iostream>
#include <string>

template <typename T> class Queue {
private:
  T *buffer{}; // Implemented using static array (circular queue approach)
  int len{};
  int num_elements{};
  T *front_ptr{};
  T *rear_ptr{};

  void lengthGreaterthanElementsCheck();

public:
  Queue() = default;
  Queue(T data, int length = 10);
  Queue(std::initializer_list<T> data);
  Queue(std::initializer_list<T> data, int length);

  int numElements();
  int bufferLength();
  bool isEmpty();

  void setBufferLength(int new_length);

  void enqueue(T data);
  T dequeue();
  T peekFront();
  T peekRear();
};
