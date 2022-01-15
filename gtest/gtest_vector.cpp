#include <gtest/gtest.h>
#include <vector>
#include "vector_func.hpp"

#define VISUAL(a) std::cout << #a << ": " << a << std::endl;

class VectorTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        for (int i = 1; i < 6; ++i) {
            _ft_vector.push_back(i);
            _std_vector.push_back(i);
        }
    }
    ft::vector<int> _ft_vector;
    std::vector<int> _std_vector;
};

#define RESULT_VISUAL 1

#ifdef RESULT_VISUAL
#define RESULT_VISUAL_EXPECT_EQ(a, b) std::cout << "ft:" << a << ", std:" << b << std::endl;EXPECT_EQ(a, b)
#else
#define RESULT_VISUAL_EXPECT_EQ(a, b) EXPECT_EQ(a, b)
#endif

// 1
TEST_F(VectorTest, DefaultConstructor) {
    ft::vector<int> ft;
    std::vector<int> std;
    // Capacity
    EXPECT_EQ(ft.size(), std.size());
    EXPECT_EQ(ft.capacity(), std.capacity());
    EXPECT_EQ(ft.empty(), std.empty());
    // TODO max_size他の人がどういう実装にしているのか調査
    // EXPECT_EQ(ft.max_size(), std.max_size());
    for (int i = 0; i < ft.size(); ++i) {
        ft.push_back(i);
        std.push_back(i);
    }
    // Capacity
    EXPECT_EQ(ft.size(), std.size());
    EXPECT_EQ(ft.capacity(), std.capacity());
    EXPECT_EQ(ft.empty(), std.empty());
    // Element access
    for (int i = 0; i < ft.size(); ++i) {
        EXPECT_EQ(ft[i], std[i]);
        EXPECT_EQ(ft.at(i), std.at(i));
    }
}

// 3
TEST_F(VectorTest, Constructor) {
    ft::vector<int> ft(10);
    std::vector<int> std(10);
    // Element access
    for (size_t i = 0; i < ft.size(); ++i) {
        EXPECT_EQ(ft.at(i), std.at(i));
        EXPECT_EQ(ft[i], std[i]);
    }
    EXPECT_ANY_THROW(ft.at(ft.size()));
    EXPECT_ANY_THROW(std.at(std.size()));
    EXPECT_EQ(ft.front(), std.front());
    EXPECT_EQ(ft.back(), std.back());
    // Capacity
    EXPECT_EQ(ft.size(), std.size());
    EXPECT_EQ(ft.capacity(), std.capacity());
    EXPECT_EQ(ft.empty(), std.empty());
    // EXPECT_EQ(ft.max_size(), std.max_size());
}

// 6
TEST_F(VectorTest, CopyConstructor) {
    ft::vector<int> ft(_ft_vector);
    std::vector<int> std(_std_vector);
    // Element access
    for (size_t i = 0; i < ft.size(); ++i) {
        VISUAL(&ft[i]);
        // VISUAL(i);
        // VISUAL(ft.at(i));
        // VISUAL(std.at(i));
        // EXPECT_EQ(ft.at(i), std.at(i));
        EXPECT_EQ(ft[i], std[i]);
    }
    // Capacity
    EXPECT_EQ(ft.size(), std.size());
    EXPECT_EQ(ft.capacity(), std.capacity());
    EXPECT_EQ(ft.empty(), std.empty());
    // EXPECT_EQ(ft.max_size(), std.max_size());
    EXPECT_EQ(ft.front(), std.front());
    EXPECT_EQ(ft.back(), std.back());
}

// reserve()
TEST_F(VectorTest, Reserve) {
    ft::vector<int> v1(10);
    v1.reserve(100);
    std::vector<int> v2(10);
    v2.reserve(100);
    EXPECT_EQ(v1.size(), v2.size());
    EXPECT_EQ(v1.capacity(), v2.capacity());
    EXPECT_EQ(v1.empty(), v2.empty());
}

// =============================================================================
// Modifiers
// =============================================================================
// clear()
TEST_F(VectorTest, Clear) {
    ft::vector<int> v1(10);
    v1.clear();
    std::vector<int> v2(10);
    v2.clear();
    EXPECT_EQ(v1.size(), v2.size());
    EXPECT_EQ(v1.capacity(), v2.capacity());
    EXPECT_EQ(v1.empty(), v2.empty());
}

// push_back
TEST_F(VectorTest, PushBack) {
    ft::vector<int> v1(10);
    std::vector<int> v2(10);
    v1.push_back(1);
    v2.push_back(1);
    EXPECT_EQ(v1.size(), v2.size());
    // EXPECT_EQ(v1.capacity(), v2.capacity());
    EXPECT_EQ(v1.empty(), v2.empty());
    for (int i = 0; i < 11; ++i) {
        EXPECT_EQ(v1[i], v2[i]);
    }
}
