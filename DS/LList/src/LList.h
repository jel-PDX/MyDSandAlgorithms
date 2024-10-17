#pragma once

#include "Node.h"

#include <functional>

template <typename T> class LList {
private:
  Node<T> *l_head{};
  int len{};

public:
  LList() = default;
  LList(Node<T> *head_node);

  Node<T> *head();
  int length();

  void setHead(Node<T> *head_node);

  void push_front(T data);
  void push_back(T data);
  void traverse(std::function<void(Node<T> *n)> func);
  T pop_front();
  T pop_back();
};
