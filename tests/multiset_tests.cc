#include "unit-tests.h"

template <typename key_type>
bool compare_multiset(ns::multiset<key_type> my_multiset,
                      std::multiset<key_type> std_multiset) {
  bool res = true;
  auto i1 = std_multiset.begin();
  for (auto i2 = my_multiset.begin(); i1 != std_multiset.end(); ++i1, ++i2) {
    if ((*i1) != (*i2)) {
      res = false;
    }
  }
  return res;
}

TEST(multiset, default_constructor_1) {
  ns::multiset<int> A;
  ASSERT_TRUE(A.empty());
  EXPECT_EQ(A.size(), 0);
}

TEST(multiset, default_constructor_2) {
  ns::multiset<char> A;
  ASSERT_TRUE(A.empty());
  EXPECT_EQ(A.size(), 0);
}

TEST(multiset, multiset_list) {
  ns::multiset<int> A{1, 2, 3, 4};
  std::multiset<int> B{1, 2, 3, 4};
  EXPECT_TRUE(compare_multiset(A, B));
  EXPECT_EQ(A.size(), 4);
}

TEST(multiset, insert_1) {
  ns::multiset<int> A;
  std::multiset<int> B;
  A.insert(21);
  B.insert(21);
  EXPECT_TRUE(compare_multiset(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(multiset, copy_constructor) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  auto A1 = A;
  auto B1 = B;
  EXPECT_TRUE(compare_multiset(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
}

TEST(multiset, move_constructor) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  auto A1 = std::move(A);
  auto B1 = std::move(B);
  EXPECT_TRUE(compare_multiset(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
}

TEST(multiset, move_operator) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  ns::multiset<int> A1;
  A1 = std::move(A);
  std::multiset<int> B1;
  B1 = std::move(B);
  EXPECT_TRUE(compare_multiset(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
}

TEST(multiset, func_begin_1) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  auto A1 = A.begin();
  auto B1 = B.begin();
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_end_1) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  auto A1 = A.end();
  auto B1 = B.end();
  A1--, B1--;
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_end_2) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  auto A1 = A.end();
  auto B1 = B.end();
  A1++, B1++;
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_end_3) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  auto A1 = A.end();
  auto B1 = B.end();
  --A1, --B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_end_4) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  auto A1 = A.end();
  auto B1 = B.end();
  ++A1, ++B1;
  EXPECT_EQ((*A1), (*B1));
}
TEST(multiset, func_cend_1) {
  const ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  const std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  auto A1 = A.end();
  auto B1 = B.end();
  --A1, --B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_cend_2) {
  const ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  const std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  auto A1 = A.end();
  auto B1 = B.end();
  A1--, B1--;
  EXPECT_EQ((*A1), (*B1));
}
TEST(multiset, func_cbegin_1) {
  const ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  const std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  auto A1 = A.begin();
  auto B1 = B.begin();
  A1++, B1++;
  EXPECT_EQ((*A1), (*B1));
}
TEST(multiset, func_cbegin_2) {
  const ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  const std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  auto A1 = A.begin();
  auto B1 = B.begin();
  ++A1, ++B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_empty_1) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  EXPECT_FALSE(A.empty());
}

TEST(multiset, func_empty_2) {
  ns::multiset<int> A;
  EXPECT_TRUE(A.empty());
}

TEST(multiset, func_clear_1) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  A.clear();
  EXPECT_TRUE(A.empty());
}

TEST(multiset, func_size_0) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  EXPECT_EQ(A.size(), B.size());
  EXPECT_TRUE(compare_multiset(A, B));
}

TEST(multiset, func_size_2) {
  ns::multiset<int> A;
  std::multiset<int> B;
  EXPECT_EQ(A.size(), B.size());
  EXPECT_TRUE(compare_multiset(A, B));
}

TEST(multiset, func_size_3) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  A.insert(3);
  B.insert(3);
  EXPECT_TRUE(compare_multiset(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(multiset, func_size_4) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  A.insert(9);
  B.insert(9);
  EXPECT_TRUE(compare_multiset(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(multiset, func_insert_2) {
  ns::multiset<int> A;
  std::multiset<int> B;
  auto A1 = A.insert(9);
  auto B1 = B.insert(9);
  EXPECT_TRUE(compare_multiset(A, B));
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_clear_2) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  A.clear();
  B.clear();
  EXPECT_EQ(A.empty(), B.empty());
  EXPECT_EQ(A.size(), B.size());
}

TEST(multiset, func_clear_3) {
  ns::multiset<int> A;
  std::multiset<int> B;
  A.clear();
  B.clear();
  EXPECT_EQ(A.empty(), B.empty());
  EXPECT_EQ(A.size(), B.size());
}

TEST(multiset, func_clear_4) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  A.clear();
  B.clear();
  EXPECT_EQ(A.size(), B.size());
}

TEST(multiset, func_insert_3) {
  ns::multiset<int> A;
  std::multiset<int> B;
  for (int i = 0; i < 5; ++i) A.insert(9);
  for (int i = 0; i < 5; ++i) B.insert(9);
  EXPECT_TRUE(compare_multiset(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(multiset, func_erase_1) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  auto A1 = A.begin();
  auto B1 = B.begin();
  A.erase(A1);
  B.erase(B1);
  EXPECT_TRUE(compare_multiset(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(multiset, func_erase_2) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  A.erase(A.end());
  B.erase(--B.end());
  EXPECT_TRUE(compare_multiset(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(multiset, func_swap_1) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  ns::multiset<int> A1;
  std::multiset<int> B1;
  A1.swap(A);
  B1.swap(B);
  EXPECT_TRUE(compare_multiset(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
}

TEST(multiset, func_swap_2) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  ns::multiset<int> A1 = {1, 2, 3, 4, 5};
  std::multiset<int> B1 = {1, 2, 3, 4, 5};
  A1.swap(A);
  B1.swap(B);
  EXPECT_TRUE(compare_multiset(A1, B1));
  EXPECT_TRUE(compare_multiset(A, B));
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.empty(), B.empty());
}

TEST(multiset, func_swap_3) {
  ns::multiset<int> A;
  std::multiset<int> B;
  ns::multiset<int> A1;
  std::multiset<int> B1;
  A1.swap(A);
  B1.swap(B);
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
}

TEST(multiset, func_merge_1) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  ns::multiset<int> A1 = {1, 2, 3, 4, 5};
  std::multiset<int> B1 = {1, 2, 3, 4, 5};
  B1.merge(B);
  A1.merge(A);
  EXPECT_TRUE(compare_multiset(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.empty(), B.empty());
}

TEST(multiset, func_merge_2) {
  ns::multiset<int> A = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  std::multiset<int> B = {9, 10, 123, -4, 5, 9, 9, 123, -4};
  ns::multiset<int> A1;
  std::multiset<int> B1;
  A1.merge(A);
  B1.merge(B);
  EXPECT_TRUE(compare_multiset(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.empty(), B.empty());
}

TEST(multiset, func_contains_1) {
  ns::multiset<int> A{1, 2, 3, 4, 5};
  EXPECT_TRUE(A.contains(1));
}

TEST(multiset, func_contains_2) {
  ns::multiset<int> A{1, 2, 3, 4, 5};
  EXPECT_FALSE(A.contains(6));
}

TEST(multiset, func_find_1) {
  ns::multiset<int> A{1, 2, 3, 4, 5};
  std::multiset<int> B{1, 2, 3, 4, 5};
  auto A1 = A.find(2);
  auto B1 = B.find(2);
  EXPECT_TRUE((*A1) == (*B1));
}

TEST(multiset, func_find_2) {
  ns::multiset<int> A{1, 2, 3, 4, 5};
  auto A1 = A.find(6);
  EXPECT_TRUE(A1 == (nullptr));
}

TEST(multiset, func_count_1) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 5, 5, 5, 5, 5, -4, 9};
  std::multiset<int> B{1, 2, 3, 4, 5, 5, 5, 5, 5, 5, -4, 9};
  EXPECT_EQ(A.count(5), B.count(5));
}

TEST(multiset, func_count_2) {
  ns::multiset<int> A{1, 2, 2, 3, 4, 5, 5, 5, 5, -4};
  std::multiset<int> B{1, 2, 2, 3, 4, 5, 5, 5, 5, -4};
  EXPECT_EQ(A.count(2), B.count(2));
}

TEST(multiset, func_count_3) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 5, 5, 5, -4};
  std::multiset<int> B{1, 2, 3, 4, 5, 5, 5, 5, -4};
  EXPECT_EQ(A.count(0), B.count(0));
}

TEST(multiset, func_lower_bound_1) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 5, 5, 5, -4};
  std::multiset<int> B{1, 2, 3, 4, 5, 5, 5, 5, -4};
  auto A1 = A.lower_bound(5);
  auto B1 = B.lower_bound(5);
  EXPECT_EQ((*A1), (*B1));
  ++A1;
  ++B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_lower_bound_2) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 5, 5, 5, -4};
  std::multiset<int> B{1, 2, 3, 4, 5, 5, 5, 5, -4};
  auto A1 = A.lower_bound(1);
  auto B1 = B.lower_bound(1);
  EXPECT_EQ((*A1), (*B1));
  ++A1;
  ++B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_lower_bound_3) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 5, 5, 5, -4};
  std::multiset<int> B{1, 2, 3, 4, 5, 5, 5, 5, -4};
  auto A1 = A.lower_bound(0);
  auto B1 = B.lower_bound(0);
  EXPECT_EQ((*A1), (*B1));
  ++A1;
  ++B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_upper_bound_1) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 5, 5, 5, -4};
  std::multiset<int> B{1, 2, 3, 4, 5, 5, 5, 5, -4};
  auto A1 = A.upper_bound(0);
  auto B1 = B.upper_bound(0);
  EXPECT_EQ((*A1), (*B1));
  ++A1;
  ++B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_upper_bound_2) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 5, 5, 5, -4};
  std::multiset<int> B{1, 2, 3, 4, 5, 5, 5, 5, -4};
  auto A1 = A.upper_bound(1);
  auto B1 = B.upper_bound(1);
  EXPECT_EQ((*A1), (*B1));
  ++A1;
  ++B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_upper_bound_3) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 5, 5, 5, -4};
  std::multiset<int> B{1, 2, 3, 4, 5, 5, 5, 5, -4};
  auto A1 = A.upper_bound(5);
  auto B1 = B.upper_bound(5);
  --A1;
  --B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(multiset, func_equal_range_1) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 5, 5, 5, -4};
  std::multiset<int> B{1, 2, 3, 4, 5, 5, 5, 5, -4};
  auto A1 = A.equal_range(5);
  auto B1 = B.equal_range(5);
  EXPECT_EQ((*(A1.first)), (*(B1.first)));
}

TEST(multiset, func_equal_range_2) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 5, 5, 5, -4};
  std::multiset<int> B{1, 2, 3, 4, 5, 5, 5, 5, -4};
  auto A1 = A.equal_range(3);
  auto B1 = B.equal_range(3);
  EXPECT_EQ((*(A1.first)), (*(B1.first)));
  EXPECT_EQ((*(A1.second)), (*(B1.second)));
}

TEST(multiset, func_equal_range_3) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 5, 5, 5, -4};
  std::multiset<int> B{1, 2, 3, 4, 5, 5, 5, 5, -4};
  auto A1 = A.equal_range(0);
  auto B1 = B.equal_range(0);
  EXPECT_EQ((*(A1.first)), (*(B1.first)));
  EXPECT_EQ((*(A1.second)), (*(B1.second)));
}

TEST(multiset, func_insert_many_1) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 5, 5, 5, -4};
  std::multiset<int> B{1, 2, 3, 4, 5, 5, 5, 5, -4, 9, 9, 7, 4};
  A.insert_many(9, 9, 7, 4);
  EXPECT_TRUE(compare_multiset(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(multiset, func_insert_many_2) {
  ns::multiset<int> A;
  std::multiset<int> B{9, 9, 7, 4};
  A.insert_many(9, 9, 7, 4);
  EXPECT_TRUE(compare_multiset(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(multiset, max_size_function) {
  ns::multiset<int> A{9, 9, 7, 4};
  std::multiset<int> B{9, 9, 7, 4};

  EXPECT_EQ(A.max_size(), B.max_size());

  std::multiset<int> A1;
  ns::multiset<int> B1;

  EXPECT_EQ(A1.max_size(), B1.max_size());
}
TEST(multiset, big_erase_1) {
  ns::multiset<int> A{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  std::multiset<int> B{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  auto A1 = A.begin();
  auto B1 = B.begin();
  A.erase(A1);
  B.erase(B1);

  auto A2 = A.begin();
  auto B2 = B.begin();
  ++A2;
  ++A2;
  ++B2;
  ++B2;
  A.erase(A2);
  B.erase(B2);
  EXPECT_TRUE(compare_multiset(A, B));

  for (int i = 0; i < 11; ++i) {
    auto A3 = A.begin();
    A.erase(A3);
  }
  EXPECT_TRUE(A.empty());
}
