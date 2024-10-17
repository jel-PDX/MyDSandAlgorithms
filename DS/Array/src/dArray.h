#include <initializer_list>

// dArray = dynamic array
template <typename T> class dArray {
private:
  int len{};
  T *buffer{};

public:
  dArray() = default;
  dArray(T data);
  dArray(std::initializer_list<T> data);
  ~dArray();

  int length();
  T &operator[](int pos);

  void resize(int new_length);
  void push(T data);
  void push(std::initializer_list<T> data);
  T pop();
  T *pop(int num_elements);
};
