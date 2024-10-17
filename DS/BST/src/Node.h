#pragma once

#include "BST.fwd.h"
#include "Node.fwd.h"

template <typename T> class Node {
private:
  Node<T> *left_ptr{};
  Node<T> *right_ptr{};
  T n_data{};

public:
  Node() = default;
  Node(T data);
  Node(Node<T> &src);
  Node &operator=(Node<T> &src);

  T data();
  Node *lChild();
  Node *rChild();

  void setData(T data);
  void setlChild(Node<T> *n);
  void setrChild(Node<T> *n);

  void swap(Node<T> *n);
};
