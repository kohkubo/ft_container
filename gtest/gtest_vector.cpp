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

  template <typename T1, typename T2>
  void compare_vector(T1 v1, T2 v2) {
    EXPECT_EQ(v1.size(), v2.size());
    // EXPECT_EQ(v1.capacity(), v2.capacity());
    EXPECT_EQ(v1.empty(), v2.empty());
    EXPECT_EQ(v1.front(), v2.front());
    EXPECT_EQ(v1.back(), v2.back());
    size_t size = std::max(v1.size(), v2.size());
    for (size_t i = 0; i < size; ++i) {
      EXPECT_EQ(v1.at(i), v2.at(i));
      EXPECT_EQ(v1[i], v2[i]);
    }
  }
  template <typename T1, typename T2>
  void vector_print(T1 v1, T2 v2) {
    VISUAL2(v1.size(), v2.size());
    VISUAL2(v1.empty(), v2.empty());
    VISUAL2(v1.front(), v2.front());
    VISUAL2(v1.back(), v2.back());
    VISUAL2(v1.capacity(), v2.capacity());
    VISUAL2(v1.max_size(), v2.max_size());
    size_t size = std::max(v1.size(), v2.size());
    for (size_t i = 0; i < v2.size(); ++i) {
      std::cout << "v1[" << i << "] = " << v1[i] << " v2[" << i
                << "] = " << v2[i] << std::endl;
    }
  }

  ft::vector<int>  _ft_vector;
  std::vector<int> _std_vector;
  ft::vector<int>  _ft_vector_empty;
  std::vector<int> _std_vector_empty;
  ft::vector<int>  _ft_vector_insert;
  std::vector<int> _std_vector_insert;
};

class DISABLED_VectorTest : public ::testing::Test {
 public:
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
  EXPECT_EQ(ft.size(), std.size());
  EXPECT_EQ(ft.capacity(), std.capacity());
  EXPECT_EQ(ft.empty(), std.empty());
  for (int i = 0; i < 5; ++i) {
    ft.push_back(i);
    std.push_back(i);
  }
  compare_vector(ft, std);
}

TEST_F(VectorTest, Constructor_allocator) {
  std::allocator<int>                   alloc;
  ft::vector<int, std::allocator<int>>  ft(alloc);
  std::vector<int, std::allocator<int>> std(alloc);
  EXPECT_EQ(ft.size(), std.size());
  EXPECT_EQ(ft.capacity(), std.capacity());
  EXPECT_EQ(ft.empty(), std.empty());
  for (int i = 0; i < 5; ++i) {
    ft.push_back(i);
    std.push_back(i);
  }
  compare_vector(ft, std);
}

TEST_F(VectorTest, Constructor) {
  ft::vector<int>  ft(10);
  std::vector<int> std(10);
  compare_vector(ft, std);
  EXPECT_ANY_THROW(ft.at(ft.size()));
  EXPECT_ANY_THROW(std.at(std.size()));
  compare_vector(ft, std);
}
// 5
TEST_F(VectorTest, Constructor5) {
  ft::vector<int>  ft(_ft_vector.begin(), _ft_vector.end());
  std::vector<int> std(_std_vector.begin(), _std_vector.end());
  compare_vector(ft, std);
}

TEST_F(VectorTest, CopyConstructor) {
  ft::vector<int>  ft(_ft_vector);
  std::vector<int> std(_std_vector);
  compare_vector(ft, std);
}
// =============================================================================
// Element access
// =============================================================================
TEST_F(VectorTest, ElementAccess) {
  ft::vector<int>  ft(_ft_vector);
  std::vector<int> std(_std_vector);
  compare_vector(ft, std);
  EXPECT_ANY_THROW(ft.at(ft.size()));
  EXPECT_ANY_THROW(std.at(std.size()));
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
  ft::vector<int>::iterator  ft_it  = _ft_vector.end();
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
  ft::vector<int>::reverse_iterator  ft_it  = _ft_vector.rend();
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
  compare_vector(v1, v2);
  v1.reserve(1000);
  v2.reserve(1000);
  compare_vector(v1, v2);
  v1.push_back(1);
  v2.push_back(1);
  compare_vector(v1, v2);
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
  compare_vector(v1, v2);
}
// iterator insert(iterator position, const T& x);
// position is a valid iterator of the container
// x is the value to insert
// returns: an iterator pointing to the inserted value
// exception: if the iterator is invalid
TEST_F(VectorTest, Insert_iv) {
  ft::vector<int> v1(_ft_vector);
  v1.insert(v1.begin(), 1);
  std::vector<int> v2(_std_vector);
  v2.insert(v2.begin(), 1);
  compare_vector(v1, v2);
}

// void insert(InputIterator pos, InputIterator first, InputIterator last)
TEST_F(VectorTest, Insert_iii) {
  ft::vector<int>  v1(_ft_vector);
  std::vector<int> v2(_std_vector);
  EXPECT_EQ(_ft_vector_insert.size(), _std_vector_insert.size());
  EXPECT_EQ(v1.size(), v2.size());
  v1.insert(v1.begin(), _ft_vector_insert.begin(), _ft_vector_insert.end());
  v2.insert(v2.begin(), _std_vector_insert.begin(), _std_vector_insert.end());
  compare_vector(v1, v2);
  v1.insert(v1.end(), _ft_vector_insert.begin(), _ft_vector_insert.end());
  v2.insert(v2.end(), _std_vector_insert.begin(), _std_vector_insert.end());
  compare_vector(v1, v2);
}
// insert(iterator, size_type, const T&)
TEST_F(VectorTest, Insert_inv) {
  ft::vector<int>  v1(_ft_vector);
  std::vector<int> v2(_std_vector);
  v1.insert(v1.begin(), _ft_vector_insert.size(), 100);
  v2.insert(v2.begin(), _std_vector_insert.size(), 100);
  compare_vector(v1, v2);
}

// push_back
TEST_F(VectorTest, PushBack) {
  ft::vector<int>  v1(10);
  std::vector<int> v2(10);
  v1.push_back(1);
  v2.push_back(1);
  compare_vector(v1, v2);
  for (int i = 0; i < 100; ++i) {
    v1.push_back(i * 2);
    v2.push_back(i * 2);
  }
  compare_vector(v1, v2);
  v1.clear();
  v2.clear();
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.empty(), v2.empty());
}
// void pop_back();
// returns: void
// exceptions: none
TEST_F(VectorTest, PopBack) {
  ft::vector<int>  v1;
  std::vector<int> v2;
  for (int i = 0; i < 10; ++i) v1.push_back(i), v2.push_back(i);
  v1.pop_back(), v2.pop_back();
  compare_vector(v1, v2);
  v1.clear(), v2.clear();
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.empty(), v2.empty());
}
// void resize( size_type count, T value = T() );
// count is the new size of the vector
// value is the value to fill the new
// if count is greater than the current size, the new elements are default
// if count is less than the current size, the last elements are removed
// returns: void
// exceptions: out_of_range if count is greater than max_size()
TEST_F(VectorTest, Resize) {
  ft::vector<int>  v1(_ft_vector);
  std::vector<int> v2(_std_vector);
  v1.resize(v1.size() + 1);
  v2.resize(v2.size() + 1);
  compare_vector(v1, v2);
  v1.resize(v1.size() - 1);
  v2.resize(v2.size() - 1);
  compare_vector(v1, v2);
}

// void swap( vector& other );
// other is the vector to swap with
// returns: void
// exception: none
TEST_F(VectorTest, Swap) {
  ft::vector<int> v1(_ft_vector);
  ft::vector<int> v2(_ft_vector);
  v1.swap(v2);
  compare_vector(v1, _std_vector);
  compare_vector(v2, _ft_vector);
}

// =============================================================================
// Other
// =============================================================================
// operator=(const vector&)
TEST_F(VectorTest, AssignmentOperator) {
  ft::vector<int> v1(_ft_vector);
  ft::vector<int> v2(_ft_vector);
  v1 = v2;
  compare_vector(v1, v2);
}

// assign(size_type, const T&)
TEST_F(VectorTest, Assign_1) {
  ft::vector<int> v1(10);
  std::vector<int> v2(10);
  v1.assign(10, 100);
  v2.assign(10, 100);
  compare_vector(v1, v2);
}

// assign(InputIterator, InputIterator)
TEST_F(VectorTest, Assign_ii) {
  ft::vector<int> v1(100);
  std::vector<int> v2(100);
  v1.assign(_ft_vector_insert.begin(), _ft_vector_insert.end());
  v2.assign(_std_vector_insert.begin(), _std_vector_insert.end());
  compare_vector(v1, v2);
}

// =============================================================================
// non-menber functions
// =============================================================================
// operator==(const vector&, const vector&)
TEST_F(VectorTest, OperatorEqual) {
  ft::vector<int> v1(_ft_vector);
  ft::vector<int> v2(_ft_vector);
  EXPECT_TRUE(v1 == v2);
  v1.push_back(1);
  EXPECT_FALSE(v1 == v2);
  v2.push_back(1);
  EXPECT_TRUE(v1 == v2);
}

// operator!=(const vector&, const vector&)
TEST_F(VectorTest, OperatorNotEqual) {
  ft::vector<int> v1(_ft_vector);
  ft::vector<int> v2(_ft_vector);
  EXPECT_FALSE(v1 != v2);
  v1.push_back(1);
  EXPECT_TRUE(v1 != v2);
  v2.push_back(1);
  EXPECT_FALSE(v1 != v2);
}

// operator<(const vector&, const vector&)
TEST_F(VectorTest, OperatorLess) {
  ft::vector<int> v1(_ft_vector);
  ft::vector<int> v2(_ft_vector);
  EXPECT_FALSE(v1 < v2);
  v2.push_back(1);
  EXPECT_TRUE(v1 < v2);
  v1.push_back(1);
  EXPECT_FALSE(v1 < v2);
  v1[0] = 0;
  v1[1] = 0;
  EXPECT_TRUE(v1 < v2);
}

// operator>(const vector&, const vector&)
TEST_F(VectorTest, OperatorGreater) {
  ft::vector<int> v1(_ft_vector);
  ft::vector<int> v2(_ft_vector);
  EXPECT_FALSE(v1 > v2);
  v2[0] = 0;
  v2[1] = 0;
  EXPECT_TRUE(v1 > v2);
}

// operator<=(const vector&, const vector&)
TEST_F(VectorTest, OperatorLessEqual) {
  ft::vector<int> v1(_ft_vector);
  ft::vector<int> v2(_ft_vector);
  EXPECT_TRUE(v1 <= v2);
  v2[0] = 0;
  v2[1] = 0;
  EXPECT_FALSE(v1 <= v2);
}

// operator>=(const vector&, const vector&)
TEST_F(VectorTest, OperatorGreaterEqual) {
  ft::vector<int> v1(_ft_vector);
  ft::vector<int> v2(_ft_vector);
  EXPECT_TRUE(v1 >= v2);
  v1[0] = 0;
  v1[1] = 0;
  EXPECT_FALSE(v1 >= v2);
}

// void swap(vector&, vector&)
TEST_F(VectorTest, Swap_2) {
  ft::vector<int> v1(_ft_vector);
  ft::vector<int> v2(_ft_vector);
  v2.push_back(1000);
  swap(v1, v2);
  EXPECT_EQ(v1.back(), 1000);
  EXPECT_EQ(v2.back(), _ft_vector.back());
}

