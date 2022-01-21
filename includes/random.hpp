#ifndef INCLUDES_RANDOM_HPP_
#define INCLUDES_RANDOM_HPP_

static const int A = 48271;
static const int M = 2147483647;
static const int Q = M / A;
static const int R = M % A;

class Random {
 public:
  explicit Random(int initialValue = 1) {
    if (initialValue < 0) initialValue += M;
    __state_ = initialValue;
    if (__state_ == 0) __state_ = 1;
  }
  int randomInt(void) {
    int tmpState = A * (__state_ % Q) - R * (__state_ / Q);
    if (tmpState >= 0)
      __state_ = tmpState;
    else
      __state_ = tmpState + M;
    return __state_;
  }
  int randomInt(int low, int high) {
    double partitionSize = (double)M / (high - low + 1);
    return (int)((randomInt() / partitionSize) + low);
  }
 private:
  int __state_;
};

#endif  // INCLUDES_RANDOM_HPP_
