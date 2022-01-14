#include <gtest/gtest.h>
#include "vector.hpp"

class VectorTest : public ::testing::Test {};

TEST_F(VectorTest, DefaultConstructor) {
    ft::vector<int> v;
    EXPECT_EQ(1, v.empty());
    EXPECT_EQ(0, v.size());
    EXPECT_EQ(0, v.capacity());
}

TEST_F(VectorTest, Constructor) {
    ft::vector<int> v(10);
    EXPECT_EQ(1, v.empty());
    EXPECT_EQ(0, v.size());
    EXPECT_EQ(10, v.capacity());
}

TEST_F(VectorTest, CopyConstructor) {
    ft::vector<int> v1(10);
    ft::vector<int> v2(v1);
    EXPECT_EQ(1, v2.empty());
    EXPECT_EQ(0, v2.size());
    EXPECT_EQ(10, v2.capacity());
}
