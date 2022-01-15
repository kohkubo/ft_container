#include <gtest/gtest.h>
#include <vector>
#include "vector_func.hpp"
#include "random_access_iterator.hpp"

#define VISUAL(a) std::cout << #a << ": " << a << std::endl;

class random_access_iterator_test : public ::testing::Test {
public:
    ft::vector<int> _v;
    ft::vector<int>::iterator _it;
    std::vector<int> _std_v;
    std::vector<int>::iterator _std_it;

    ft::vector<int> _v2;
    ft::vector<int>::iterator _it2;
    std::vector<int> _std_v2;
    std::vector<int>::iterator _std_it2;
    virtual void SetUp() {
        for (int i = 1; i < 11; ++i) {
            _v.push_back(i);
            _std_v.push_back(i);
            _v2.push_back(i * 2);
            _std_v2.push_back(i * 2);
        }
    }
};

// deref
TEST_F(random_access_iterator_test, deref) {
    _it = _v.begin();
    _std_it = _std_v.begin();
    for (int i = 1; i < 11; ++i) {
        EXPECT_EQ(*_it, *_std_it);
        ++_it;
        ++_std_it;
    }
}

// ref
TEST_F(random_access_iterator_test, ref) {
    ft::vector<int> *ft_v = &_v;
    std::vector<int> *std_v = &_std_v;
    _it = ft_v->begin();
    _std_it = std_v->begin();
    EXPECT_EQ(*_it, *_std_it);
}

// pre increment
TEST_F(random_access_iterator_test, pre_increment) {
    _it = _v.begin() - 1;
    _std_it = _std_v.begin() - 1;
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(*(++_it), *(++_std_it));
    }
}

// post increment
TEST_F(random_access_iterator_test, post_increment) {
    _it = _v.begin();
    _std_it = _std_v.begin();
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(*(_it++), *(_std_it++));
    }
}

// pre decrement
TEST_F(random_access_iterator_test, pre_decrement) {
    _it = _v.end() ;
    _std_it = _std_v.end();
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(*(--_it), *(--_std_it));
    }
}

// post decrement
TEST_F(random_access_iterator_test, post_decrement) {
    _it = _v.end() - 1;
    _std_it = _std_v.end() - 1;
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(*(_it--), *(_std_it--));
    }
}

// plus
TEST_F(random_access_iterator_test, test_operator_plus) {
    _it = _v.begin();
    _std_it = _std_v.begin();
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(*(_it + i), *(_std_it + i));
    }
}

// plus_equal
TEST_F(random_access_iterator_test, test_operator_plus_equal) {
    _it = _v.begin();
    _std_it = _std_v.begin();
    for (int i = 0; i < 10 - 1; ++i) {
        _it += 1;
        _std_it += 1;
        EXPECT_EQ(*_it, *_std_it);
    }
}

// minus
TEST_F(random_access_iterator_test, test_operator_minus) {
    _it = _v.end();
    _std_it = _std_v.end();
    for (int i = 10; i > 0; --i) {
        EXPECT_EQ(*(_it - i), *(_std_it - i));
    }
}

// minus_equal
TEST_F(random_access_iterator_test, test_operator_minus_equal) {
    _it = _v.end();
    _std_it = _std_v.end();
    for (int i = 10 - 1; i > 0; --i) {
        _it -= 1;
        _std_it -= 1;
        EXPECT_EQ(*_it, *_std_it);
    }
}

// []
TEST_F(random_access_iterator_test, test_operator_bracket) {
    _it = _v.begin();
    _std_it = _std_v.begin();
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(_it[i], _std_it[i]);
    }
}

// =============================================================================
// non-member functions
// =============================================================================
// operator==
TEST_F(random_access_iterator_test, test_operator_equal) {
    _it = _v.begin();
    _std_it = _std_v.begin();
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(*_it == *_it);
        EXPECT_TRUE(*_std_it == *_std_it);
        _it += 1;
        _std_it += 1;
    }
}

// operator!=
TEST_F(random_access_iterator_test, test_operator_not_equal) {
    _it = _v.begin();
    _std_it = _std_v.begin();
    _it2 = _v2.begin();
    _std_it2 = _std_v2.begin();
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(*_it != *_it2);
        EXPECT_TRUE(*_std_it != *_std_it2);
        EXPECT_FALSE(*_it != *_std_it);
        _it += 1;
        _std_it += 1;
        _it2 += 1;
        _std_it2 += 1;
    }
}

// operator<
TEST_F(random_access_iterator_test, test_operator_less) {
    _it = _v.begin();
    _std_it = _std_v.begin();
    _it2 = _v2.begin();
    _std_it2 = _std_v2.begin();
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(*_it < *_it2);
        EXPECT_TRUE(*_std_it < *_std_it2);
        EXPECT_FALSE(*_it2 < *_it);
        EXPECT_FALSE(*_std_it2 < *_std_it);
        _it += 1;
        _std_it += 1;
        _it2 += 1;
        _std_it2 += 1;
    }
}

// operator>
TEST_F(random_access_iterator_test, test_operator_greater) {
    _it = _v.begin();
    _std_it = _std_v.begin();
    _it2 = _v2.begin();
    _std_it2 = _std_v2.begin();
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(*_it2 > *_it);
        EXPECT_TRUE(*_std_it2 > *_std_it);
        EXPECT_FALSE(*_it > *_it2);
        EXPECT_FALSE(*_std_it > *_std_it2);
        _it += 1;
        _std_it += 1;
        _it2 += 1;
        _std_it2 += 1;
    }
}

// operator<=
TEST_F(random_access_iterator_test, test_operator_less_equal) {
    _it = _v.begin();
    _std_it = _std_v.begin();
    _it2 = _v2.begin();
    _std_it2 = _std_v2.begin();
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(*_it <= *_it2);
        EXPECT_TRUE(*_std_it <= *_std_it2);
        EXPECT_FALSE(*_it2 <= *_it);
        EXPECT_FALSE(*_std_it2 <= *_std_it);
        _it += 1;
        _std_it += 1;
        _it2 += 1;
        _std_it2 += 1;
    }
}

// operator>=
TEST_F(random_access_iterator_test, test_operator_greater_equal) {
    _it = _v.begin();
    _std_it = _std_v.begin();
    _it2 = _v2.begin();
    _std_it2 = _std_v2.begin();
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(*_it2 >= *_it);
        EXPECT_TRUE(*_std_it2 >= *_std_it);
        EXPECT_FALSE(*_it >= *_it2);
        EXPECT_FALSE(*_std_it >= *_std_it2);
        _it += 1;
        _std_it += 1;
        _it2 += 1;
        _std_it2 += 1;
    }
}
