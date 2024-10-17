#include "Stack.h"

template <typename T> Stack<T>::Stack(T data) : len{1} {
  buffer = new T[len];
  buffer[0] = data;
}

template <typename T>
Stack<T>::Stack(std::initializer_list<T> data) : len{(int)data.size()} {
  buffer = new T[data.size()];

  for (int i{}; i < len; ++i) {
    buffer[i] = *(data.begin() + i);
  }
}

template <typename T> int Stack<T>::length() { return len; }

template <typename T> void Stack<T>::push(T data) {
  if (buffer == nullptr) {
    buffer = new T{data};
    len++;
    return;
  }

  T *temp{buffer};
  buffer = new T[len + 1];

  for (int i{}; i < len; ++i) {
    buffer[i] = temp[i];
  }

  buffer[len] = data;

  len++;
}

template <typename T> T Stack<T>::pop() {
  try {
    if (buffer == nullptr) {
      throw "ERROR: cannot pop from empty stack\n";
    }
  } catch (std::string msg) {
    std::cout << msg;
  }

  if (len == 1) {
    T val = *buffer;
    delete buffer;
    buffer = nullptr;
    len = 0;
    return val;
  }

  T *temp{buffer};
  buffer = new T[len - 1];

  for (int i{}; i < len - 1; ++i) {
    buffer[i] = temp[i];
  }

  T val{temp[len - 1]};

  delete temp;

  len--;

  return val;
}
