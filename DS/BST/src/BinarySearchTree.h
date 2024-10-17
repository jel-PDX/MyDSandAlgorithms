#pragma once

#include "BST.fwd.h"
#include "Node.fwd.h"

#include <functional>
#include <list>

template <typename T> class BST {
private:
  Node<T> *t_root{};

  void checkImbalance(Node<T> *n, Node<T> *root);
  void insertFromRoot(T data, Node<T> *root);
  void rebalance(Node<T> *n, int diff);

public:
  BST() = default;
  BST(T data);
  BST(Node<T> *root);
  BST(BST &src);

  Node<T> *root();

  Node<T> *binarySearch(T data);

  void insert(T data);
  void remove(T data);

  int height();
  void inorder(std::function<void(Node<T> *n)> func);
  void preorder(std::function<void(Node<T> *n)> func);
  void postorder(std::function<void(Node<T> *n)> func);
  void breadthfirst(std::function<void(Node<T> *n)> func);
};
