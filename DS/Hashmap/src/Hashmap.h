#pragma once

#include "Slot.h"

#include <initializer_list>
#include <iostream>

template <typename K, typename V> class Hashmap {
private:
  // Open Addressing using Linear Probing
  // Initial Capacity is 16
  // Load Factor is 0.75
  // When num_elements > (Capacity * Load Factor), Capacity Doubles
  Slot<K, V> *h_slots{};
  int h_num_elements{};
  int h_capacity{16};

  struct hashFuncs {
    // Integer keys
    static int hashFunc(int key, int n) { return key % n; }
    // Alphanumeric keys
    static int hashFunc(std::string key, int n) {
      int ascii_sum{};
      for (char c : key) {
        ascii_sum += (int)c;
      }
      return ascii_sum % n;
    }
  };

  int hashFunction(K key);
  void rehash();

public:
  Hashmap() = default;
  Hashmap(Slot<K, V> slot);
  Hashmap(std::initializer_list<Slot<K, V>> slots);

  void add(Slot<K, V> slot);
  void remove(K key);

  V &operator[](K key);

  int size();
  bool isEmpty();
};
