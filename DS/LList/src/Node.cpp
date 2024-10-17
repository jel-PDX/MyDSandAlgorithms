#include "Node.h"

template <typename T>
Node<T>::Node(T data, Node<T> *next_node) : n_data{data}, next_ptr{next_node} {}

template <typename T> T Node<T>::data() { return n_data; }

template <typename T> Node<T> *Node<T>::next() { return next_ptr; }

template <typename T> void Node<T>::setData(T data) { n_data = data; }

template <typename T> void Node<T>::setNext(Node<T> *next_node) {
  next_ptr = next_node;
}
