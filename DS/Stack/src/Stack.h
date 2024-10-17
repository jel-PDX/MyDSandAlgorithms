#include <initializer_list>
#include <iostream>

template <typename T> class Stack {
private:
  int len{};
  T *buffer{};

public:
  Stack() = default;
  Stack(T data);
  Stack(std::initializer_list<T> data);
  ~Stack() = default;

  int length();

  void push(T data);
  T pop();
};
