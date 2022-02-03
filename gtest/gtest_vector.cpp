#include <gtest/gtest.h>

#include <vector>

#include "vector.hpp"

#define VISUAL(a) std::cout << #a << ": " << a << std::endl;
#define VISUAL2(a, b) \
  std::cout << #a << ": " << a << ", " << #b << ": " << b << std::endl;

class VectorTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    for (int i = 1; i < 6; ++i) {
      _ft_vector.push_back(i);
      _std_vector.push_back(i);
      _ft_vector_insert.push_back(i * 10);
      _std_vector_insert.push_back(i * 10);
    }
  }
  ft::vector<int>  _ft_vector;
  std::vector<int> _std_vector;
  ft::vector<int>  _ft_vector_empty;
  std::vector<int> _std_vector_empty;
  ft::vector<int>  _ft_vector_insert;
  std::vector<int> _std_vector_insert;
};

#define RESULT_VISUAL 1

#ifdef RESULT_VISUAL
#define RESULT_VISUAL_EXPECT_EQ(a, b)                    \
  std::cout << "ft:" << a << ", std:" << b << std::endl; \
  EXPECT_EQ(a, b)
#else
#define RESULT_VISUAL_EXPECT_EQ(a, b) EXPECT_EQ(a, b)
#endif

TEST_F(VectorTest, DefaultConstructor) {
  ft::vector<int>  ft;
  std::vector<int> std;
  // Capacity
  EXPECT_EQ(ft.size(), std.size());
  EXPECT_EQ(ft.capacity(), std.capacity());
  EXPECT_EQ(ft.empty(), std.empty());
  // TODO(kohkubo) max_size他の人がどういう実装にしているのか調査
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

TEST_F(VectorTest, Constructor_allocator) {
  std::allocator<int>                   alloc;
  ft::vector<int, std::allocator<int>>  ft(alloc);
  std::vector<int, std::allocator<int>> std(alloc);

  // Capacity
  EXPECT_EQ(ft.size(), std.size());
  EXPECT_EQ(ft.capacity(), std.capacity());
  EXPECT_EQ(ft.empty(), std.empty());
}

TEST_F(VectorTest, Constructor) {
  ft::vector<int>  ft(10);
  std::vector<int> std(10);
  // Capacity
  EXPECT_EQ(ft.size(), std.size());
  EXPECT_EQ(ft.capacity(), std.capacity());
  EXPECT_EQ(ft.empty(), std.empty());
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
// 5
TEST_F(VectorTest, Constructor5) {
  ft::vector<int>  ft(_ft_vector.begin(), _ft_vector.end());
  std::vector<int> std(_std_vector.begin(), _std_vector.end());
}

TEST_F(VectorTest, CopyConstructor) {
  ft::vector<int>  ft(_ft_vector);
  std::vector<int> std(_std_vector);
  // Capacity
  EXPECT_EQ(ft.size(), std.size());
  EXPECT_EQ(ft.capacity(), std.capacity());
  EXPECT_EQ(ft.empty(), std.empty());

  // Element access
  for (size_t i = 0; i < ft.size(); ++i) {
    EXPECT_EQ(ft.at(i), std.at(i));
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
// =============================================================================
// Iterators
// =============================================================================
// begin
TEST_F(VectorTest, Begin) {
  ft::vector<int>::iterator  ft_it  = _ft_vector.begin();
  std::vector<int>::iterator std_it = _std_vector.begin();
  for (size_t i = 0; i < _ft_vector.size(); ++i) {
    EXPECT_EQ(*ft_it, *std_it);
    ++ft_it;
    ++std_it;
  }
}

// end
TEST_F(VectorTest, End) {
    ft::vector<int>::iterator ft_it = _ft_vector.end();
    std::vector<int>::iterator std_it = _std_vector.end();
    for (size_t i = 0; i < _ft_vector.size(); ++i) {
        --ft_it;
        --std_it;
        EXPECT_EQ(*ft_it, *std_it);
    }
}

// rbegin
TEST_F(VectorTest, RBegin) {
  ft::vector<int>::reverse_iterator  ft_it  = _ft_vector.rbegin();
  std::vector<int>::reverse_iterator std_it = _std_vector.rbegin();
  for (size_t i = 0; i < _ft_vector.size(); ++i) {
    EXPECT_EQ(*ft_it, *std_it);
    ++ft_it;
    ++std_it;
  }
}

// rend
TEST_F(VectorTest, REnd) {
  ft::vector<int>::reverse_iterator  ft_it = _ft_vector.rend();
  std::vector<int>::reverse_iterator std_it = _std_vector.rend();
  for (size_t i = 0; i < _ft_vector.size(); ++i) {
    --ft_it;
    --std_it;
    EXPECT_EQ(*ft_it, *std_it);
  }
}

// =============================================================================
// Capacity
// =============================================================================
// reserve()
TEST_F(VectorTest, Reserve) {
  ft::vector<int> v1(10);
  v1.reserve(100);
  std::vector<int> v2(10);
  v2.reserve(100);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
  EXPECT_EQ(v1.empty(), v2.empty());

  v1.reserve(1000);
  v2.reserve(1000);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
  EXPECT_EQ(v1.empty(), v2.empty());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], v2[i]);
  }
  v1.push_back(1);
  v2.push_back(1);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
  EXPECT_EQ(v1.empty(), v2.empty());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], v2[i]);
  }
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

// erase()
TEST_F(VectorTest, Erase) {
  ft::vector<int> v1(_ft_vector);
  v1.erase(v1.begin());
  std::vector<int> v2(_std_vector);
  v2.erase(v2.begin());
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
  EXPECT_EQ(v1.empty(), v2.empty());
  EXPECT_EQ(v1.front(), v2.front());
  EXPECT_EQ(v1.back(), v2.back());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1.at(i), v2.at(i));
    EXPECT_EQ(v1[i], v2[i]);
  }
}

// insert(iterator, input_iterator, input_iterator)
TEST_F(VectorTest, Insert) {
  ft::vector<int> v1(_ft_vector);
  v1.insert(v1.begin(), _ft_vector_insert.begin(), _ft_vector_insert.end());
  std::vector<int> v2(_std_vector);
  v2.insert(v2.begin(), _std_vector_insert.begin(), _std_vector_insert.end());
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.empty(), v2.empty());
  EXPECT_EQ(v1.front(), v2.front());
  EXPECT_EQ(v1.back(), v2.back());
  for (size_t i = 0; i < v2.size(); ++i) {
    // VISUAL(v2.at(i));
    EXPECT_EQ(v1.at(i), v2.at(i));
    EXPECT_EQ(v1[i], v2[i]);
  }
}
// insert(iterator, size_type, const T&)
TEST_F(VectorTest, Insert_2) {
  ft::vector<int> v1(_ft_vector);
  v1.insert(v1.begin(), _ft_vector_insert.size(), 1);
  std::vector<int> v2(_std_vector);
  v2.insert(v2.begin(), _std_vector_insert.size(), 1);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.empty(), v2.empty());
  EXPECT_EQ(v1.front(), v2.front());
  EXPECT_EQ(v1.back(), v2.back());
  for (size_t i = 0; i < v2.size(); ++i) {
    // VISUAL(v2.at(i));
    EXPECT_EQ(v1.at(i), v2.at(i));
    EXPECT_EQ(v1[i], v2[i]);
  }
}

// insert 
// TEST_F(VectorTest, insert_benchmark) {
//   ft::vector<int> ft;
//   std::vector<int> std;
//   for (size_t i = 0; i < 100000; ++i) {
//     ft.insert(ft.begin(), i);
//   }
//   for (size_t i = 0; i < 100000; ++i) {
//     std.insert(std.begin(), i);
//   }
// }

// push_back
TEST_F(VectorTest, PushBack) {
  ft::vector<int>  v1(10);
  std::vector<int> v2(10);
  v1.push_back(1);
  v2.push_back(1);
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.empty(), v2.empty());
  for (int i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], v2[i]);
  }
  for (int i = 0; i < 100; ++i) {
    v1.push_back(i * 2);
    v2.push_back(i * 2);
  }
  for (int i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1[i], v2[i]);
  }
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.empty(), v2.empty());
  v1.clear();
  v2.clear();
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.empty(), v2.empty());
}
