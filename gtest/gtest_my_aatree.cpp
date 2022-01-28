#include <gtest/gtest.h>
#include "my_aatree.hpp"

class MyAatreeTest : public ::testing::Test {
protected:
  ft::AATree<int int> tree_;
  virtual void SetUp() {
    for (int i = 1; i < 6; ++i) {
      tree_.insert(i);
    }
  }
};

TEST_F(MyAatreeTest, __size)
{
  EXPECT_EQ(tree_.size(), 5);
}
