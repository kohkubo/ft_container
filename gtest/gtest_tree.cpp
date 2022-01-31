#include <gtest/gtest.h>

#include <map>

#include "my_rb_tree.hpp"

#define VISUAL(a) std::cout << #a << ": " << a << std::endl;
#define VISUAL2(a, b) \
  std::cout << #a << ": " << a << ", " << #b << ": " << b << std::endl;

class RbTreeTest : public ::testing::Test {
 public:
  virtual void SetUp() {
    for (int i = 1; i < 6; ++i) {
      ft_tree_.__insert_unique(ft::make_pair(i, i));
      std_tree_.insert(std::make_pair(i, i));
    }
  }
  ft::__tree<ft::pair<const int, int>, std::less<int>,
                std::allocator<ft::pair<const int, int> > >
      ft_tree_;
  std::map<int, int> std_tree_;
};

TEST_F(RbTreeTest, Constructor) {
  ft::__tree<ft::pair<const int, int>, std::less<int>,
                std::allocator<ft::pair<const int, int> > >
      __ft_;
  std::map<int, int> __std_;
  // Capacity
  EXPECT_EQ(__ft_.size(), __std_.size());
}
