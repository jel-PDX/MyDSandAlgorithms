#include "Node.h"

template <typename T> Node<T>::Node(T data) : n_data{data} {}
template <typename T>
Node<T>::Node(Node<T> &src)
    : n_data{src.data()}, left_ptr{src.lChild()}, right_ptr{src.rChild()} {}
template <typename T> Node<T> &Node<T>::operator=(Node<T> &src) {
  n_data = src.data();
  left_ptr = src.lChild();
  right_ptr = src.rChild();
  return *this;
}
template <typename T> T Node<T>::data() { return n_data; }
template <typename T> Node<T> *Node<T>::lChild() { return left_ptr; }
template <typename T> Node<T> *Node<T>::rChild() { return right_ptr; }
template <typename T> void Node<T>::setData(T data) { n_data = data; }
template <typename T> void Node<T>::setlChild(Node<T> *n) { left_ptr = n; }
template <typename T> void Node<T>::setrChild(Node<T> *n) { right_ptr = n; }
template <typename T> void Node<T>::swap(Node<T> *n) {
  Node<T> temp{*this};
  *this = *n;
  *n = temp;
}
