#include <gtest/gtest.h>
#include "type_traits.hpp"

class EnableIfTest : public ::testing::Test {};

TEST_F(EnableIfTest, true_type) {
    ft::enable_if<true, int>::type test = 1;
    EXPECT_EQ(1, test);
}

// TEST_F(EnableIfTest, false_type) {
//     ft::enable_if<false, int>::type test = 1;
//     EXPECT_EQ(0, test);
// }
