#include "Hashmap.h"

template <typename K, typename V> int Hashmap<K, V>::hashFunction(K key) {
  return hashFuncs::hashFunc(key, h_capacity);
}

template <typename K, typename V> void Hashmap<K, V>::rehash() {}

template <typename K, typename V> Hashmap<K, V>::Hashmap(Slot<K, V> slot) {
  h_slots = new Slot<K, V>[h_capacity];

  add(slot);
}

template <typename K, typename V>
Hashmap<K, V>::Hashmap(std::initializer_list<Slot<K, V>> slots) {
  h_slots = new Slot<K, V>[h_capacity];

  for (Slot<K, V> slot : slots)
    add(slot);
}
template <typename K, typename V> void Hashmap<K, V>::add(Slot<K, V> slot) {
  if (h_slots == nullptr)
    h_slots = new Slot<K, V>[h_capacity];

  h_num_elements++;
  if (h_num_elements > (h_capacity * 0.75)) {
    h_capacity *= 2;
    rehash();
  }
  int hash_index{hashFunction(slot.key())};

  try {
    if (h_slots[hash_index].key() == slot.key())
      throw "ERROR: cannot add key that already exists in hashmap\n";
  } catch (std::string msg) {
    std::cout << msg;
  }

  for (int i{}; i < h_capacity; ++i, ++hash_index) {
    if (h_slots[hash_index].isClear()) {
      h_slots[hash_index] = slot;
      break;
    }
    if (hash_index == h_capacity - 1)
      hash_index = 0;
  }
}

template <typename K, typename V> void Hashmap<K, V>::remove(K key) {
  try {
    if (h_slots == nullptr || h_num_elements == 0) {
      throw "ERROR: cannot remove from empty hashmap\n";
    }
  } catch (std::string msg) {
    std::cout << msg;
  }

  int hash_index{hashFunction(key)};

  for (int i{}; i < h_capacity; ++i, ++hash_index) {
    if (h_slots[hash_index].key() == key) {
      h_slots[hash_index].clearSlot();
      h_num_elements--;
      return;
    }
    try {
      if (h_slots[hash_index].isClear())
        throw "ERROR: cannot remove non-existant key";
    } catch (std::string msg) {
      std::cout << msg;
    }

    if (hash_index == h_capacity - 1)
      hash_index = 0;
  }
}

template <typename K, typename V> V &Hashmap<K, V>::operator[](K key) {
  int hash_index{hashFunction(key)};
  for (int i{}; i < h_capacity; ++i, ++hash_index) {
    if (h_slots[hash_index].key() == key)
      return h_slots[hash_index].val();
    if (h_slots[hash_index].isClear()) {
      h_slots[hash_index].setSlot(key, V());
      return h_slots[hash_index].val();
    }
    if (hash_index == h_capacity - 1)
      hash_index = 0;
  }
}

template <typename K, typename V> int Hashmap<K, V>::size() {
  return h_num_elements;
}

template <typename K, typename V> bool Hashmap<K, V>::isEmpty() {
  return (h_num_elements == 0);
}
