#include <gtest/gtest.h>
#include "pointer_traits.hpp"
#include <type_traits>

class PointerTraitsTest : public ::testing::Test {};

TEST_F(PointerTraitsTest, pointer_traits_test) {
    typedef ft::pointer_traits<int*>::element_type element_type;
    EXPECT_EQ(typeid(int), typeid(element_type));
    typedef ft::pointer_traits<int*>::pointer pointer_type;
    EXPECT_EQ(typeid(int*), typeid(pointer_type));
}
