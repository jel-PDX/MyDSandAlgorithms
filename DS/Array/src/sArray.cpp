#include "sArray.h"

template <typename T>
sArray<T>::sArray(T data) : len{1} {
  buffer = new T[len];
  buffer[0] = data;
}

template <typename T>
sArray<T>::sArray(std::initializer_list<T> data) : len{(int)data.size()} {
  buffer = new T[len];
  for (auto it{data.begin()}, i{0}; i < len; ++i, ++it) buffer[i] = *it;
}

template <typename T>
sArray<T>::~sArray() {
  delete[] buffer;
}

template <typename T>
int sArray<T>::length() {
  return len;
}

template <typename T>
T &sArray<T>::operator[](int pos) {
  return buffer[pos];
}
