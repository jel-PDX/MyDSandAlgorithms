#include "Queue.h"

template <typename T> void Queue<T>::lengthGreaterthanElementsCheck() {
  try {
    if (len < num_elements) {
      len = 0;
      num_elements = 0;
      throw "\nERROR: cannot set buffer length smaller than number of "
            "elements\n";
    }
  } catch (std::string msg) {
    std::cout << msg;
  }
}

template <typename T>
Queue<T>::Queue(T data, int length) : len{length}, num_elements{1} {
  lengthGreaterthanElementsCheck();

  buffer = new T[len];
  buffer[0] == data;

  front_ptr = buffer;
  rear_ptr = buffer;
}

template <typename T>
Queue<T>::Queue(std::initializer_list<T> data)
    : len{10 + ((int)data.size() - 1)}, num_elements{(int)data.size()} {
  buffer = new T[len];
  lengthGreaterthanElementsCheck();

  for (int i{}; i < data.size(); ++i) {
    buffer[i] = *(data.begin() + i);
  }

  front_ptr = &buffer[0];
  rear_ptr = &buffer[data.size() - 1];
}

template <typename T>
Queue<T>::Queue(std::initializer_list<T> data, int length)
    : len{length}, num_elements{(int)data.size()} {
  buffer = new T[len];
  lengthGreaterthanElementsCheck();

  for (int i{}; i < data.size(); ++i) {
    buffer[i] = *(data.begin() + i);
  }

  front_ptr = &buffer[0];
  rear_ptr = &buffer[data.size() - 1];
}

template <typename T> int Queue<T>::numElements() { return num_elements; }
template <typename T> int Queue<T>::bufferLength() { return len; }

template <typename T> bool Queue<T>::isEmpty() {
  if (num_elements == 0)
    return true;

  return false;
}

template <typename T> void Queue<T>::setBufferLength(int new_length) {
  try {
    if (new_length < num_elements) {
      throw "ERROR: can't set new length less than number of elements\n";
    }
    if (new_length == 0) {
      throw "ERROR: can't set length to zero\n";
    }
    if (new_length < 0) {
      throw "ERROR: can't set negative length\n";
    }
  } catch (std::string msg) {
    std::cout << msg;
  }

  int old_length{len};

  T *temp{buffer};
  buffer = new T[new_length];

  int i{};
  while (i != num_elements) {
    buffer[i] = *front_ptr;

    if (front_ptr != &temp[old_length - 1])
      front_ptr += 1;
    else
      front_ptr = &temp[0];

    i++;
  }

  front_ptr = &buffer[0];
  rear_ptr = &buffer[i - 1];

  len = new_length;
}

template <typename T> void Queue<T>::enqueue(T data) {
  try {
    if (num_elements == len) {
      throw "ERROR: can't enqueue on full Queue\n";
    }
  } catch (std::string msg) {
    std::cout << msg;
  }

  if (num_elements == 0)
    *rear_ptr = data;
  else {
    if (rear_ptr != &buffer[len - 1]) {
      rear_ptr += 1;
    } else
      rear_ptr = &buffer[0];

    *rear_ptr = data;
  }

  num_elements++;
}

template <typename T> T Queue<T>::dequeue() {
  try {
    if (len == 0) {
      throw "ERROR: can't dequeue on Queue with empty buffer\n";
    }
    if (num_elements == 0) {
      throw "ERROR: can't dequeue on empty Queue\n";
    }
  } catch (std::string msg) {
    std::cout << msg;
  }

  T data{*front_ptr};
  if (front_ptr != &buffer[len - 1])
    front_ptr += 1;
  else
    front_ptr = &buffer[0];

  num_elements--;

  return data;
}

template <typename T> T Queue<T>::peekFront() { return *front_ptr; }
template <typename T> T Queue<T>::peekRear() { return *rear_ptr; }
