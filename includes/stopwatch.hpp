#ifndef GBENCH_STOPWATCH_HPP_
#define GBENCH_STOPWATCH_HPP_

#include <time.h>

#include <iomanip>
#include <iostream>

namespace ft {

class Stopwatch {
  char const* __activity_;
  int         __range_;
  clock_t     __start_;

 public:
  Stopwatch(char const* activity = "Stopwatch", int range = 0,
            bool is_start = true)
      : __activity_(activity), __range_(range), __start_(0) {
    if (is_start) start();
  }
  ~Stopwatch() { stop(); }
  void          clear() { __start_ = 0; }
  unsigned long get_ms() {
    if (!is_started()) return 0;
    return (clock() - __start_) * 1000 / CLOCKS_PER_SEC;
  }
  bool          is_started() const { return __start_ != 0; }
  unsigned long stop() {
    if (!is_started()) return 0;
    unsigned long ms = get_ms();
    std::cout << __activity_ << "/" << std::left << std::setw(7) << __range_ << ": "
    << std::right
    << std::setw(3)
               << ms << " ms" << std::endl;
    clear();
    return ms;
  }
  void start() { __start_ = clock(); }
};

}  // namespace ft

#endif  // GBENCH_STOPWATCH_HPP_
