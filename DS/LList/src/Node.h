#pragma once

template <typename T> class Node {
private:
  T n_data{};
  Node *next_ptr{};

public:
  Node() = default;
  Node(T data, Node *next_node = nullptr);
  ~Node() = default;

  T data();
  Node *next();
  void setData(T data);
  void setNext(Node *next_node);
};
