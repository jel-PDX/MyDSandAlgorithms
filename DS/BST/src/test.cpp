/// Binary Search Tree with AVL Self-Balancing (AVL Tree)
//
// By: James Lawrance
// Date: 6/27/23
//
/// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

#include <catch2/catch_test_macros.hpp>

#include "BinarySearchTree.cpp"
#include "Node.cpp"

// Testing Tree

enum {
  n1_data = 15,
  n2_data = 9,
  n3_data = 21,
  n4_data = 5,
  n5_data = 11,
  n6_data = 19,
  n7_data = 25,
  n8_data = 7,
  n9_data = 10,
  n10_data = 17,
  n11_data = 20
};

Node<int> n1{n1_data};
Node<int> n2{n2_data};
Node<int> n3{n3_data};
Node<int> n4{n4_data};
Node<int> n5{n5_data};
Node<int> n6{n6_data};
Node<int> n7{n7_data};
Node<int> n8{n8_data};
Node<int> n9{n9_data};
Node<int> n10{n10_data};
Node<int> n11{n11_data};

void setupNodes() {
  n1.setlChild(&n2);
  n1.setrChild(&n3);
  n2.setlChild(&n4);
  n2.setrChild(&n5);
  n3.setlChild(&n6);
  n3.setrChild(&n7);
  n4.setrChild(&n8);
  n5.setlChild(&n9);
  n6.setlChild(&n10);
  n6.setrChild(&n11);
}

//               n1
//          /          \
//       n2              n3
//    /      \        /      \
//  n4        n5    n6        n7
//    \      /     /  \
//     n8  n9    n10  n11

// For checking tree data

template <typename T, typename Function>
void inOrderTraversal(Node<T> *root, Function func) {
  if (root == nullptr) return;

  inOrderTraversal(root->lChild(), func);
  func(root);
  inOrderTraversal(root->rChild(), func);
}

TEST_CASE("Node") {
  Node<int> n1{};
  Node<int> n2{2};
  Node<int> n3{3};

  n1.setData(1);
  n1.setlChild(&n2);
  n1.setrChild(&n3);

  CHECK(n1.data() == 1);
  CHECK(n1.lChild() == &n2);
  CHECK(n1.rChild() == &n3);
  CHECK(n2.data() == 2);
  CHECK(n2.lChild() == nullptr);
  CHECK(n2.rChild() == nullptr);
  CHECK(n3.data() == 3);
  CHECK(n3.lChild() == nullptr);
  CHECK(n3.rChild() == nullptr);
}

TEST_CASE("Tree Default Constructor") {
  BST<int> t{};

  CHECK(t.root() == nullptr);
}

TEST_CASE("Tree Paramaterized Constructor") {
  Node<int> n{};
  BST<int> t{&n};

  CHECK(t.root() == &n);
}

TEST_CASE("Tree Copy Constructor") {
  SECTION("Copy from Empty Tree") {
    BST<int> t1{};
    BST<int> t2{t1};

    CHECK(t2.root() == nullptr);
  }
  SECTION("Copy from Non-Empty Tree") {
    setupNodes();
    BST<int> t1{&n1};
    BST<int> t2{t1};

    int data[]{n4_data,  n8_data, n2_data,  n9_data, n5_data, n1_data,
               n10_data, n6_data, n11_data, n3_data, n7_data};
    int i{};
    auto check = [&i, data](Node<int> *n) {
      CHECK(n->data() == data[i]);
      i++;
    };

    inOrderTraversal(t2.root(), check);
  }
}

TEST_CASE("Tree Binary Search") {
  setupNodes();
  BST<int> t{&n1};

  SECTION("Search for Root") { CHECK(t.binarySearch(n1_data) == &n1); }

  SECTION("Search for Internal Node") {
    CHECK(t.binarySearch(n2_data) == &n2);
    CHECK(t.binarySearch(n6_data) == &n6);
  }

  SECTION("Search for Leaf Node") {
    CHECK(t.binarySearch(n9_data) == &n9);
    CHECK(t.binarySearch(n11_data) == &n11);
    CHECK(t.binarySearch(n7_data) == &n7);
  }
}

TEST_CASE("Tree Insertion") {
  BST<int> t{};

  t.insert(5);   // Insertion on empty tree
  t.insert(10);  // Can insert to the right
  t.insert(9);   // Can insert to the left
  t.insert(11);  // Can insert on node with one child
  t.insert(2);
  t.insert(3);
  t.insert(1);
  t.insert(5);

  int data[]{1, 2, 3, 5, 5, 9, 10, 11};
  int i{};
  auto check = [&i, data](Node<int> *n) {
    CHECK(n->data() == data[i]);
    i++;
  };

  inOrderTraversal(t.root(), check);

  // Expected tree:

  //           5
  //      /         \
  //    2           10
  //  /   \        /   \
  // 1     3      9    11
  //        \
  //         5
}

TEST_CASE("Tree Removal") {
  setupNodes();
  BST<int> t_test{&n1};

  SECTION("Remove Leaf Node") {
    BST<int> t{t_test};
    t.remove(n8_data);
    t.remove(n9_data);

    int data[]{n4_data, n2_data,  n5_data, n1_data, n10_data,
               n6_data, n11_data, n3_data, n7_data};
    int i{};
    auto check = [&i, data](Node<int> *n) {
      CHECK(n->data() == data[i]);
      i++;
    };

    inOrderTraversal(t.root(), check);
  }

  SECTION("Remove Internal Node, One Child") {
    BST<int> t{t_test};
    t.remove(n4_data);  // Has right child
    t.remove(n5_data);  // Has left child

    int data[]{n8_data, n2_data,  n9_data, n1_data, n10_data,
               n6_data, n11_data, n3_data, n7_data};
    int i{};
    auto check = [&i, data](Node<int> *n) {
      CHECK(n->data() == data[i]);
      i++;
    };

    inOrderTraversal(t.root(), check);
  }

  SECTION("Remove Internal Node, Two Children") {
    BST<int> t{t_test};
    t.remove(n2_data);  // Replace n2 with inorder successor

    int data[]{n4_data,  n8_data, n9_data,  n5_data, n1_data,
               n10_data, n6_data, n11_data, n3_data, n7_data};
    int i{};
    auto check = [&i, data](Node<int> *n) {
      CHECK(n->data() == data[i]);
      i++;
    };

    inOrderTraversal(t.root(), check);
  }

  SECTION("Remove Root Node") {
    BST<int> t{t_test};

    t.remove(n1_data);  // Replace n1 with inorder successor

    int data[]{n4_data,  n8_data, n2_data,  n9_data, n5_data,
               n10_data, n6_data, n11_data, n3_data, n7_data};
    int i{};
    auto check = [&i, data](Node<int> *n) {
      CHECK(n->data() == data[i]);
      i++;
    };

    inOrderTraversal(t.root(), check);
  }

  SECTION("Remove on Empty Tree") {
    BST<int> t{};
    REQUIRE_THROWS(t.remove(5));
  }
}

TEST_CASE("Tree Traversal") {
  setupNodes();
  BST<int> t{&n1};
  std::vector<int> ordered_data{};

  auto fill = [&ordered_data](Node<int> *n) {
    ordered_data.push_back(n->data());
  };

  SECTION("Inorder") {
    t.inorder(fill);

    int inorder_list[]{n4_data,  n8_data, n2_data,  n9_data, n5_data, n1_data,
                       n10_data, n6_data, n11_data, n3_data, n7_data};

    for (int i{}; i < ordered_data.size(); ++i) {
      CHECK(ordered_data[i] == inorder_list[i]);
    }
  }

  SECTION("Preorder") {
    t.preorder(fill);

    int preorder_list[]{n1_data, n2_data, n4_data,  n8_data,  n5_data, n9_data,
                        n3_data, n6_data, n10_data, n11_data, n7_data};

    for (int i{}; i < ordered_data.size(); ++i) {
      CHECK(ordered_data[i] == preorder_list[i]);
    }
  }
  SECTION("Postorder") {
    t.postorder(fill);

    int postorder_list[]{n8_data,  n4_data, n9_data, n5_data, n2_data, n10_data,
                         n11_data, n6_data, n7_data, n3_data, n1_data};

    for (int i{}; i < ordered_data.size(); ++i) {
      CHECK(ordered_data[i] == postorder_list[i]);
    }
  }
  SECTION("Breadth First") {
    t.breadthfirst(fill);

    int breadthfirst_list[]{n1_data, n2_data,  n3_data, n4_data,
                            n5_data, n6_data,  n7_data, n8_data,
                            n9_data, n10_data, n11_data};

    for (int i{}; i < ordered_data.size(); ++i) {
      CHECK(ordered_data[i] == breadthfirst_list[i]);
    }
  }
}

TEST_CASE("Height") {
  SECTION("Height of Empty Tree") {
    BST<int> t{};
    CHECK(t.height() == -1);
  }

  SECTION("Height of Tree with only Root") {
    BST<int> t{5};
    CHECK(t.height() == 0);
  }

  SECTION("Height of Complex Tree with no Imbalance") {
    setupNodes();
    BST<int> t{&n1};
    CHECK(t.height() == 3);
  }

  SECTION("Height of Complex Tree with Imbalance") {
    setupNodes();
    BST<int> t{&n1};  // Working directly on testing tree
    // Assembling new nodes from scratch instead of inserting to prevent
    // self-balancing from occurring
    Node<int> n12{16}, n13{16};
    n10.setlChild(&n12);
    n12.setlChild(&n13);
    CHECK(t.height() == 5);
  }

  // Undoing modification to n10 in previous test
  n10.setlChild(nullptr);
}

TEST_CASE("AVL Self-Balancing") {
  SECTION(
      "Tree Imbalanced Left Rotation, Imbalance at Root"
      "Minimal 3-Node Tree") {
    BST<int> t{1};
    t.insert(2);
    t.insert(3);  // Should trigger rebalance

    //   1
    //    \            2
    //     2    ->    / \
    //      \        1   3
    //       3

    CHECK(t.root()->data() == 2);
    CHECK(t.root()->lChild()->data() == 1);
    CHECK(t.root()->rChild()->data() == 3);
  }

  SECTION(
      "Tree Imbalanced Right Rotation, Imbalance at Root"
      "Minimal 3-Node Tree") {
    BST<int> t{3};
    t.insert(2);
    t.insert(1);  // Should trigger rebalance

    //       3
    //      /          2
    //     2    ->    / \
    //    /          1   3
    //   1

    CHECK(t.root()->data() == 2);
    CHECK(t.root()->lChild()->data() == 1);
    CHECK(t.root()->rChild()->data() == 3);
  }

  SECTION(
      "Tree Imbalanced Left Right Rotation, Imbalance at Root"
      "Minimal 3-Node Tree") {
    BST<int> t{3};
    t.insert(1);
    t.insert(2);  // Should trigger rebalance

    //     3          3
    //    /          /          2
    //   1    ->    2    ->    / \
    //    \        /          1   3
    //     2      1

    CHECK(t.root()->data() == 2);
    CHECK(t.root()->lChild()->data() == 1);
    CHECK(t.root()->rChild()->data() == 3);
  }

  SECTION(
      "Tree Imbalanced Right Left Rotation, Imbalance at Root"
      "Minimal 3-Node Tree") {
    BST<int> t{1};
    t.insert(3);
    t.insert(2);  // Should trigger rebalance

    //   1          1
    //    \          \            2
    //     3    ->    2    ->    / \
    //    /            \        1   3
    //   2              3

    CHECK(t.root()->data() == 2);
    CHECK(t.root()->lChild()->data() == 1);
    CHECK(t.root()->rChild()->data() == 3);
  }

  BST<int> t_test{&n1};
  SECTION(
      "Tree Imbalanced Left Rotation, Imbalance at Internal Node more than "
      "1 Edge away from Insertion") {
    BST<int> t{t_test};
    t.remove(n8_data);
    t.insert(12);
    t.insert(13);  // Should trigger rebalance at n2

    //           n1                          n1
    //       /        \                  /        \
		//      n2       (...)              n5       (...)
    //    /    \                     /      \
		//  n4      n5          ->     n2       (12)
    //         /  \               /  \        \
		//       n9   (12)          n4    n9      (13)
    //              \
		//              (13)

    int data[]{n4_data, n2_data,  n9_data, n5_data,  12,      13,
               n1_data, n10_data, n6_data, n11_data, n3_data, n7_data};
    int i{};
    auto check = [&i, data](Node<int> *n) {
      CHECK(n->data() == data[i]);
      int diff = heightFromRoot(n->lChild()) - heightFromRoot(n->rChild());
      CHECK(!(diff > 1));
      CHECK(!(diff < -1));
      i++;
    };

    inOrderTraversal(t.root(), check);
  }

  SECTION(
      "Tree Imbalanced Right Rotation, Imbalance at Internal Node more "
      "than 1 Edge away from Insertion") {
    BST<int> t{t_test};
    t.insert(16);  // Should trigger rebalance at n3

    //         n1                      n1
    //     /        \              /        \
		//  (...)        n3         (...)        n6
    //             /    \                  /    \
		//            n6    n7  ->           n10    n3
    //           /  \                    /     /  \
		//         n10  n11               (16)   n11   n7
    //         /
    //      (16)

    int data[]{n4_data, n8_data,  n2_data, n9_data,  n5_data, n1_data,
               16,      n10_data, n6_data, n11_data, n3_data, n7_data};
    int i{};
    auto check = [&i, data](Node<int> *n) {
      CHECK(n->data() == data[i]);
      int diff = heightFromRoot(n->lChild()) - heightFromRoot(n->rChild());
      CHECK(!(diff > 1));
      CHECK(!(diff < -1));
      i++;
    };

    inOrderTraversal(t.root(), check);
  }

  SECTION(
      "Tree Imbalanced Left Right Rotation, Imbalance at Internal Node "
      "more than 1 Edge away from Insertion") {
    BST<int> t{t_test};
    t.insert(21);  // Should trigger rebalance at n3

    //         n1                    n1                      n1
    //     /        \            /        \              /        \
		//  (...)       n3         (...)        n3         (...)       n11
    //            /    \                  /    \                  /    \
		//           n6    n7  ->            n11   n7  ->           n6     n3
    //          /  \                    /  \                    /     /  \
		//        n10 n11                 n6   (21)              n10    (21)  n7
    //               \                /
    //               (21)          n10

    int data[]{n4_data,  n8_data, n2_data,  n9_data, n5_data, n1_data,
               n10_data, n6_data, n11_data, n3_data, 21,      n7_data};
    int i{};
    auto check = [&i, data](Node<int> *n) {
      CHECK(n->data() == data[i]);
      int diff = heightFromRoot(n->lChild()) - heightFromRoot(n->rChild());
      CHECK(!(diff > 1));
      CHECK(!(diff < -1));
      i++;
    };

    inOrderTraversal(t.root(), check);
  }

  SECTION(
      "Tree Imbalanced Right Left Rotation, Imbalance at Internal Node "
      "more than 1 Edge away from Insertion") {
    BST<int> t{t_test};
    t.remove(n8_data);
    t.insert(12);
    t.insert(10);  // Should trigger rebalance at n2

    //           n1                     n1                         n1
    //       /        \             /        \                 /        \
		//      n2       (...)         n2       (...)             n9       (...)
    //    /    \                 /    \                    /      \
		//  n4     n5           ->  n4      n9         ->     n2       n5
    //        /  \                     /  \              /  \        \
		//       n9  (12)               (10)   n5          n4   (10)     (12)
    //      /                               \
		//    (10)                              (12)

    int data[]{n4_data, n2_data,  10,      n9_data,  n5_data, 12,
               n1_data, n10_data, n6_data, n11_data, n3_data, n7_data};
    int i{};
    auto check = [&i, data](Node<int> *n) {
      CHECK(n->data() == data[i]);
      int diff = heightFromRoot(n->lChild()) - heightFromRoot(n->rChild());
      CHECK(!(diff > 1));
      CHECK(!(diff < -1));
      i++;
    };

    inOrderTraversal(t.root(), check);
  }
}
