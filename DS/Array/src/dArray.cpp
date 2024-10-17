#include "dArray.h"

#include <iostream>

template <typename T>
dArray<T>::dArray(T data) : len{1} {
  buffer = new T[len];
  buffer[0] = data;
}

template <typename T>
dArray<T>::dArray(std::initializer_list<T> data) : len{(int)data.size()} {
  buffer = new T[len];
  for (auto it{data.begin()}, i{0}; i < len; ++i, ++it) buffer[i] = *it;
}

template <typename T>
dArray<T>::~dArray() {
  delete[] buffer;
}

template <typename T>
int dArray<T>::length() {
  return len;
}

template <typename T>
T &dArray<T>::operator[](int pos) {
  return buffer[pos];
}

template <typename T>
void dArray<T>::resize(int new_length) {
  if (new_length == len) return;

  T *temp = buffer;
  buffer = new T[new_length];
  for (int i{}; i < len && i < new_length; ++i, ++temp) buffer[i] = *temp;
  len = new_length;
}

template <typename T>
void dArray<T>::push(T data) {
  resize(len + 1);
  buffer[len - 1] = data;
}

template <typename T>
void dArray<T>::push(std::initializer_list<T> data) {
  int old_len = len;
  resize(len + data.size());
  for (auto it{data.begin()}, i{0}; it != data.end(); ++i, ++it) {
    buffer[i + old_len] = *it;
  }
}

template <typename T>
T dArray<T>::pop() {
  T val{buffer[len - 1]};
  len--;
  return val;
}

template <typename T>
T *dArray<T>::pop(int num_elements) {
  T *popped_elements = new T[num_elements];
  for (int num_remaining{num_elements}, i{0}; num_remaining != 0;
       --num_remaining, ++i) {
    popped_elements[i] = pop();
  }
  return popped_elements;
}
