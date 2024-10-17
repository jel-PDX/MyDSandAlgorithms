#include <initializer_list>

// sArray = static array
template <typename T> class sArray {
private:
  int len{};
  T *buffer{};

public:
  sArray() = default;
  sArray(T data);
  sArray(std::initializer_list<T> data);
  ~sArray();

  int length();
  T &operator[](int pos);
};
