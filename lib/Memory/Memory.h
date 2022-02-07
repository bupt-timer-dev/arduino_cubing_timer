#ifndef __TIMER_MEMORY__
#define __TIMER_MEMORY__

#include <Data.h>

template <typename T>
class Memory {
  int addr;
  size_t len;

  public:
  Memory() = default;
  Memory(int _addr)
      : addr(_addr);
  Memory(int _begin, int _end)
      : addr(_begin)
      , len(_end - _begin);

  T operator[](size_t index);

  size_t length() const { return len; }
  void erase(size_t);
  size_t append(const T&);
  T[] toArray() const;
};

#endif