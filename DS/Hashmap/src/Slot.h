#pragma once

template <typename K, typename V> class Slot {
private:
  K s_key{};
  V s_val{};

public:
  Slot() = default;
  Slot(K key, V val);

  K key();
  V &val();
  void setSlot(K key, V val);
  void clearSlot();
  bool isClear();
};
