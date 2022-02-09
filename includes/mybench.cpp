#include <vector>

#include "stopwatch.hpp"
#include "vector.hpp"

#define BENCH(a, func)                                                 \
  {                                                                    \
    int range[]    = {1 << 22};                                        \
    int range_size = sizeof(range) / sizeof(int);                      \
    {                                                                  \
      double std_time = 0;                                             \
      for (int i = 0; i < range_size; ++i) {                           \
        {                                                              \
          std::vector<int> v;                                          \
          ft::Stopwatch    sw(a, range[i]);                            \
          for (int j = 0; j < range[i]; ++j) {                         \
            func;                                                      \
          }                                                            \
          std::cout << "lb_";                                          \
          std_time += sw.stop();                                       \
        }                                                              \
      }                                                                \
      double ft_time = 0;                                              \
      for (int i = 0; i < range_size; ++i) {                           \
        {                                                              \
          ft::vector<int> v;                                           \
          ft::Stopwatch   sw(a, range[i]);                             \
          for (int j = 0; j < range[i]; ++j) {                         \
            func;                                                      \
          }                                                            \
          std::cout << "ft_";                                          \
          ft_time += sw.stop();                                        \
        }                                                              \
      }                                                                \
      std::cout << "Faster rate: " << std_time / ft_time << std::endl; \
    }                                                                  \
  }

int main() {
  BENCH("push_bach", v.push_back(i));
  return 0;
}
