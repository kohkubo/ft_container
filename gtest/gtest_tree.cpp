#include <gtest/gtest.h>

#include <map>
#include <random>

#include "rb_tree.hpp"

#define VISUAL(a) std::cout << #a << ": " << a << std::endl;
#define VISUAL2(a, b) \
  std::cout << #a << ": " << a << ", " << #b << ": " << b << std::endl;

class RbTreeTest : public ::testing::Test {
 public:
  typedef ft::pair<const int, int>                                    ftPair;
  typedef std::pair<const int, int>                                   stdPair;
  typedef ft::__tree<ftPair, std::less<int>, std::allocator<ftPair> > ftTree;
  typedef std::map<int, int>                                          stdMap;
  typedef ft::__tree<ftPair, std::less<int>, std::allocator<ftPair> >::iterator
                                          ftIt;
  typedef std::map<int, int>::iterator    stdIt;
  typedef ft::pair<ftIt, bool>            ftPairBool;
  typedef std::pair<stdIt, bool>          stdPairBool;
  typedef typename ftTree::__node_pointer ftNodePtr;

  virtual void                            SetUp() {
    std::srand(std::time(nullptr));
    for (int i = 1; i <= nb_elem; ++i) {
      ft_tree_.insert(ft::make_pair(i, i));
      std_tree_.insert(std::make_pair(i, i));
    }
  }
  const int   nb_elem = 10;
  ftIt        ft_it_;
  stdIt       std_it_;
  ftTree      ft_tree_;
  stdMap      std_tree_;
  ftPairBool  ft_pair_bool_;
  stdPairBool std_pair_bool_;
  ftNodePtr   ft_node_ptr_;
};

class DISABLED_RbTreeTest : public ::testing::Test {
 public:
  typedef ft::pair<const int, int>                                    ftPair;
  typedef std::pair<const int, int>                                   stdPair;
  typedef ft::__tree<ftPair, std::less<int>, std::allocator<ftPair> > ftTree;
  typedef std::map<int, int>                                          stdMap;
  typedef ft::__tree<ftPair, std::less<int>, std::allocator<ftPair> >::iterator
                                       ftIt;
  typedef std::map<int, int>::iterator stdIt;
  typedef ft::pair<ftIt, bool>         ftPairBool;
  typedef std::pair<stdIt, bool>       stdPairBool;
  ftIt                                 ft_it_;
  stdIt                                std_it_;
  ftTree                               ft_tree_;
  stdMap                               std_tree_;
  ftPairBool                           ft_pair_bool_;
  stdPairBool                          std_pair_bool_;
};

TEST_F(RbTreeTest, Constructor) {
  ftTree __ft_tree;
  stdMap __std_tree;
  EXPECT_EQ(__ft_tree.size(), __std_tree.size());
}

// insert true with sequence value
TEST_F(RbTreeTest, InsertTrue) {
  // beginより前に挿入
  int key                  = -1;
  ft_pair_bool_            = ft_tree_.insert(ft::make_pair(key, key));
  std_pair_bool_           = std_tree_.insert(std::make_pair(key, key));

  const int        __kSize = 10;
  std::vector<int> keys(__kSize);
  ftTree           __ft_tree;
  stdMap           __std_tree;
  for (int i = 0; i < __kSize; ++i) {
    key            = i;
    keys[i]        = key;
    ft_pair_bool_  = __ft_tree.insert(ft::make_pair(key, key));
    std_pair_bool_ = __std_tree.insert(std::make_pair(key, key));
    EXPECT_EQ(ft_pair_bool_.second, std_pair_bool_.second);
  }
  for (int i = 0; i < __kSize; ++i) {
    EXPECT_EQ(__ft_tree.find(keys[i])->first, __std_tree.find(keys[i])->first);
    EXPECT_EQ(__ft_tree.find(keys[i])->second,
              __std_tree.find(keys[i])->second);
  }
}

// insert true
TEST_F(RbTreeTest, InsertTrue2) {
  int       key     = 0;
  const int __kSize = 10;
  ftTree    __ft_tree;
  stdMap    __std_tree;
  for (int i = __kSize; i > 0; --i) {
    key            = i;
    ft_pair_bool_  = __ft_tree.insert(ft::make_pair(key, key));
    std_pair_bool_ = __std_tree.insert(std::make_pair(key, key));
    EXPECT_EQ(ft_pair_bool_.second, std_pair_bool_.second);
  }
}

// insert false
TEST_F(RbTreeTest, InsertFalse) {
  for (int i = 0; i < 6; ++i) {
    ft_pair_bool_  = ft_tree_.insert(ft::make_pair(i, i));
    std_pair_bool_ = std_tree_.insert(std::make_pair(i, i));
    EXPECT_EQ(ft_pair_bool_.second, std_pair_bool_.second);
  }
}

// insert true with random value
TEST_F(RbTreeTest, InsertTrueRandom) {
  ftTree           __ft;
  stdMap           __std;
  const int        SIZE = 1000;
  std::vector<int> keys(SIZE);
  for (int i = 0; i < SIZE; ++i) {
    int key        = std::rand() % 1000;
    keys[i]        = key;
    ft_pair_bool_  = __ft.insert(ft::make_pair(key, key));
    std_pair_bool_ = __std.insert(std::make_pair(key, key));
    EXPECT_EQ(ft_pair_bool_.second, std_pair_bool_.second);
  }
  for (int i = 0; i < SIZE; ++i) {
    EXPECT_EQ(__ft.find(keys[i])->first, __std.find(keys[i])->first);
    EXPECT_EQ(__ft.find(keys[i])->second, __std.find(keys[i])->second);
  }
}

// insert(iterator, const value_type&)
TEST_F(RbTreeTest, InsertIterator) {
  ft_it_  = ft_tree_.insert(ft_tree_.begin(), ft::make_pair(0, 0));
  std_it_ = std_tree_.insert(std_tree_.begin(), std::make_pair(0, 0));
  EXPECT_EQ(ft_it_->first, std_it_->first);
  EXPECT_EQ(ft_it_->second, std_it_->second);
}

// erase
TEST_F(RbTreeTest, Erase) {
  int       key     = 0;
  const int __kSize = 10;
  ftTree    __ft_tree;
  stdMap    __std_tree;
  for (int i = __kSize; i > 0; --i) {
    key            = i;
    ft_pair_bool_  = __ft_tree.insert(ft::make_pair(key, key));
    std_pair_bool_ = __std_tree.insert(std::make_pair(key, key));
    EXPECT_EQ(ft_pair_bool_.second, std_pair_bool_.second);
  }
  for (int i = 0; i < __kSize; ++i) {
    key = i;
    EXPECT_EQ(__ft_tree.erase(key), __std_tree.erase(key));
    EXPECT_EQ(__ft_tree.size(), __std_tree.size());
  }
}

// clear
TEST_F(RbTreeTest, Clear) {
  ft_tree_.clear();
  std_tree_.clear();
  EXPECT_EQ(ft_tree_.size(), std_tree_.size());
}

// lower_bound
TEST_F(RbTreeTest, LowerBound) {
  ft_it_ = ft_tree_.lower_bound(1);
  EXPECT_EQ(ft_it_->first, 1);
  ft_it_ = ft_tree_.lower_bound(2);
  EXPECT_EQ(ft_it_->first, 2);
  std_it_ = std_tree_.lower_bound(100);
  EXPECT_EQ(std_it_, std_tree_.end());
}
