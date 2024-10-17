#include "BinarySearchTree.h"
#include <iostream>

template <typename T> BST<T>::BST(T data) {
  t_root = new Node<T>;
  t_root->setData(data);
}
template <typename T> BST<T>::BST(Node<T> *root) : t_root{root} {}

template <typename T> BST<T>::BST(BST &src) {
  auto copyNode = [this](Node<T> *n) { this->insert(n->data()); };
  src.breadthfirst(copyNode);
}

template <typename T> Node<T> *BST<T>::root() { return t_root; }

template <typename T> Node<T> *BST<T>::binarySearch(T data) {
  return binarySearchFromRoot(data, t_root);
}

template <typename T> void BST<T>::insert(T data) {
  if (t_root == nullptr) {
    t_root = new Node<T>{data};
    return;
  }

  insertFromRoot(data, t_root);
}

template <typename T> void BST<T>::remove(T data) {
  try {
    if (t_root == nullptr)
      throw "ERROR: cannot remove on empty list\n";
  } catch (std::string msg) {
    std::cout << msg;
  }

  if (data == t_root->data()) {
    Node<T> temp{};
    temp.setlChild(t_root);
    removeFromRoot(data, &temp);
    return;
  }
  removeFromRoot(data, t_root);
}

template <typename T>
void BST<T>::inorder(std::function<void(Node<T> *n)> func) {
  inorderTraverseFromRoot(func, t_root);
}

template <typename T>
void BST<T>::preorder(std::function<void(Node<T> *n)> func) {
  preorderTraverseFromRoot(func, t_root);
}

template <typename T>
void BST<T>::postorder(std::function<void(Node<T> *n)> func) {
  postorderTraverseFromRoot(func, t_root);
}

template <typename T>
void BST<T>::breadthfirst(std::function<void(Node<T> *n)> func) {
  if (t_root == nullptr)
    return;

  std::list<Node<T> *> init_queue{t_root};
  breadthfirstTraverseFromRoot(func, init_queue);
}

template <typename T> int BST<T>::height() {
  if (t_root == nullptr)
    return -1;
  if (t_root->lChild() == nullptr && t_root->rChild() == nullptr)
    return 0;

  return heightFromRoot(t_root);
}

template <typename T> void BST<T>::checkImbalance(Node<T> *n, Node<T> *root) {
  if (root == n)
    return;
  int diff = heightFromRoot(root->lChild()) - heightFromRoot(root->rChild());
  if (diff > 1 || diff < -1) {
    rebalance(root, diff);
    return;
  }

  if (n->data() > root->data())
    checkImbalance(n, root->rChild());
  else if (n->data() <= root->data())
    checkImbalance(n, root->lChild());
}

template <typename T> void BST<T>::rebalance(Node<T> *n, int diff) {
  Node<T> *A{n};

  // If right-heavy and imbalance occurs in right subtree of right side
  //
  //     A
  //      \
	//       B
  //      / \
	//    (t)  C

  if (diff < -1 && heightFromRoot(n->rChild()->rChild()) >
                       heightFromRoot(n->rChild()->lChild())) {
    Node<T> *B{A->rChild()};
    Node<T> *B_left_tree{B->lChild()};
    A->swap(B); // A becomes B, B becomes A
    A->setlChild(B);
    B->setrChild(B_left_tree);
  }

  // If left-heavy and imbalance occurs in left subtree of left side
  //
  //         A
  //        /
  //       B
  //      / \
  //     C  (t)

  else if (diff > 1 && heightFromRoot(n->lChild()->lChild()) >
                           heightFromRoot(n->lChild()->rChild())) {
    Node<T> *B{A->lChild()};
    Node<T> *B_right_tree{B->rChild()};
    A->swap(B); // A becomes B, B becomes A
    A->setrChild(B);
    B->setlChild(B_right_tree);
  }

  // If right-heavy and imbalance occurs in left subtree of right side
  //
  //     A
  //      \
	//       B
  //      /
  //     C
  //    /
  //  (t)

  else if (diff < -1 && heightFromRoot(n->rChild()->lChild()) >
                            heightFromRoot(n->rChild()->rChild())) {
    Node<T> *B{A->rChild()};
    Node<T> *C{B->lChild()};
    Node<T> *C_left_tree{C->lChild()};
    B->swap(C); // B becomes C, C becomes B
    B->setrChild(C);
    B->setlChild(C_left_tree);
    C->setlChild(nullptr);

    rebalance(n, diff);
  }

  // If left-heavy and imbalance occurs in right subtree of left side
  //
  //       A
  //      /
  //     B
  //      \
	//       C
  //        \
	//        (t)

  else if (diff > 1 && heightFromRoot(n->lChild()->rChild()) >
                           heightFromRoot(n->lChild()->lChild())) {
    Node<T> *B{n->lChild()};
    Node<T> *C{B->rChild()};
    Node<T> *C_right_tree{C->rChild()};

    B->swap(C); // B becomes C, C becomes B
    B->setlChild(C);
    B->setrChild(C_right_tree);
    C->setrChild(nullptr);

    rebalance(n, diff);
  }

  checkImbalance(n, t_root);
}

// Recursive Functions
template <typename T> Node<T> *binarySearchFromRoot(T data, Node<T> *root) {
  if (data == root->data())
    return root;

  if (data > root->data() && root->rChild() != nullptr)
    return binarySearchFromRoot(data, root->rChild());
  else if (data <= root->data() && root->lChild() != nullptr)
    return binarySearchFromRoot(data, root->lChild());
}

template <typename T> void BST<T>::insertFromRoot(T data, Node<T> *root) {
  if (data > root->data() && root->rChild() == nullptr) {
    Node<T> *new_node = new Node<T>{data};
    root->setrChild(new_node);
    checkImbalance(root, t_root);
    return;
  }
  if (data <= root->data() && root->lChild() == nullptr) {
    Node<T> *new_node = new Node<T>{data};
    root->setlChild(new_node);
    checkImbalance(root, t_root);
    return;
  }

  if (data > root->data() && root->rChild() != nullptr)
    insertFromRoot(data, root->rChild());
  else if (data <= root->data() && root->lChild() != nullptr)
    insertFromRoot(data, root->lChild());
}

template <typename T> void removeFromRoot(T data, Node<T> *root) {
  Node<T> *mark_node{};
  if (root->lChild() != nullptr && root->lChild()->data() == data)
    mark_node = root->lChild();
  else if (root->rChild() != nullptr && root->rChild()->data() == data)
    mark_node = root->rChild();

  if (mark_node != nullptr) {
    // 1: Remove node with no children
    if (mark_node->lChild() == nullptr && mark_node->rChild() == nullptr) {
      if (mark_node == root->lChild()) {
        root->setlChild(nullptr);
      } else if (mark_node == root->rChild()) {
        root->setrChild(nullptr);
      }
    }
    // 2: Remove node with left child
    else if (mark_node->lChild() != nullptr && mark_node->rChild() == nullptr) {
      if (mark_node == root->lChild())
        root->setlChild(mark_node->lChild());
      else if (mark_node == root->rChild())
        root->setrChild(mark_node->lChild());
    }
    // 3: Remove node with right child
    else if (mark_node->lChild() == nullptr && mark_node->rChild() != nullptr) {
      if (mark_node == root->lChild())
        root->setlChild(mark_node->rChild());
      else if (mark_node == root->rChild())
        root->setrChild(mark_node->rChild());
    }
    // 4: Remove node with two children
    else {
      Node<T> *inorder_successor{mark_node->rChild()};
      Node<T> *prev{};
      while (inorder_successor->lChild() != nullptr) {
        prev = inorder_successor;
        inorder_successor = inorder_successor->lChild();
      }

      mark_node->setData(inorder_successor->data());
      removeFromRoot(inorder_successor->data(), prev);
    }
    return;
  }

  if (data <= root->data() && root->lChild() != nullptr)
    removeFromRoot(data, root->lChild());
  else if (data > root->data() && root->rChild() != nullptr)
    removeFromRoot(data, root->rChild());
}

template <typename T>
void inorderTraverseFromRoot(std::function<void(Node<T> *n)> func,
                             Node<T> *root) {
  if (root == nullptr)
    return;

  inorderTraverseFromRoot(func, root->lChild());
  func(root);
  inorderTraverseFromRoot(func, root->rChild());
}

template <typename T>
void preorderTraverseFromRoot(std::function<void(Node<T> *n)> func,
                              Node<T> *root) {
  if (root == nullptr)
    return;

  func(root);
  preorderTraverseFromRoot(func, root->lChild());
  preorderTraverseFromRoot(func, root->rChild());
}

template <typename T>
void postorderTraverseFromRoot(std::function<void(Node<T> *n)> func,
                               Node<T> *root) {
  if (root == nullptr)
    return;

  postorderTraverseFromRoot(func, root->lChild());
  postorderTraverseFromRoot(func, root->rChild());
  func(root);
}

template <typename T>
void breadthfirstTraverseFromRoot(std::function<void(Node<T> *n)> func,
                                  std::list<Node<T> *> &node_queue) {
  while (!node_queue.empty()) {
    Node<T> *node = node_queue.front();
    node_queue.pop_front();

    if (node->lChild() != nullptr)
      node_queue.push_back(node->lChild());

    if (node->rChild() != nullptr)
      node_queue.push_back(node->rChild());

    func(node);
  }
}

template <typename T> int heightFromRoot(Node<T> *root) {
  if (root == nullptr)
    return -1;
  else {
    int lDepth{heightFromRoot(root->lChild())};
    int rDepth{heightFromRoot(root->rChild())};

    if (lDepth > rDepth)
      return (lDepth + 1);
    else
      return (rDepth + 1);
  }
}
