#include "Slot.h"

template <typename K, typename V>
Slot<K, V>::Slot(K key, V val) : s_key{key}, s_val{val} {}
template <typename K, typename V> K Slot<K, V>::key() { return s_key; }
template <typename K, typename V> V &Slot<K, V>::val() { return s_val; }
template <typename K, typename V> void Slot<K, V>::setSlot(K key, V val) {
  s_key = key;
  s_val = val;
}
template <typename K, typename V> void Slot<K, V>::clearSlot() {
  s_key = K();
  s_val = V();
}
template <typename K, typename V> bool Slot<K, V>::isClear() {
  return (s_key == K() && s_val == V());
}
