#include "LList.h"
#include <iostream>

template <typename T> LList<T>::LList(Node<T> *head_node) : l_head{head_node} {
  if (l_head == nullptr) {
    len = 0;
    return;
  }

  int i{};
  traverse([&](Node<T> *n) { ++i; });
  len = i;
}

template <typename T> Node<T> *LList<T>::head() { return l_head; }

template <typename T> int LList<T>::length() { return len; }

template <typename T> void LList<T>::setHead(Node<T> *head_node) {
  l_head = head_node;

  int i{};
  traverse([&](Node<T> *n) { ++i; });
  len = i;
}

template <typename T> void LList<T>::push_front(T data) {
  Node<T> *new_node = new Node{data};
  if (l_head == nullptr) {
    l_head = new_node;
    len++;
    return;
  }
  new_node->setNext(l_head);
  l_head = new_node;
  len++;
}

template <typename T> void LList<T>::push_back(T data) {
  if (l_head == nullptr) {
    push_front(data);
    return;
  }

  Node<T> *new_node{nullptr};
  traverse([&new_node, data](Node<T> *n) {
    if (n->next() == nullptr && new_node == nullptr) {
      new_node = new Node{data};
      n->setNext(new_node);
    }
  });
  len++;
}

template <typename T>
void LList<T>::traverse(std::function<void(Node<T> *n)> func) {
  if (l_head == nullptr)
    return;

  Node<T> *traverse_node{l_head};
  while (traverse_node != nullptr) {
    func(traverse_node);
    traverse_node = traverse_node->next();
  }
}

template <typename T> T LList<T>::pop_front() {
  try {
    if (l_head == nullptr) {
      throw "ERROR: cannot pop empty linked list\n";
    }
  } catch (std::string msg) {
    std::cout << msg;
  }
  if (l_head->next() == nullptr) {
    T val{l_head->data()};
    delete l_head;
    l_head == nullptr;
    return val;
  }
  Node<T> *temp{l_head};
  l_head = l_head->next();
  T val{temp->data()};
  len--;
  return val;
}

template <typename T> T LList<T>::pop_back() {
  try {
    if (l_head == nullptr) {
      throw "ERROR: cannot pop empty linked list\n";
    }
  } catch (std::string msg) {
    std::cout << msg;
  }
  if (l_head->next() == nullptr) {
    delete l_head;
    return T{};
  }

  Node<T> *prev{l_head};
  T val{};
  traverse([&](Node<T> *n) {
    if (n->next() == nullptr) {
      val = n->data();
      prev->setNext(nullptr);
    } else if (n != l_head) {
      prev = prev->next();
    }
  });

  len--;
  return val;
}
