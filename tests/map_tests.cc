#include "unit-tests.h"

template <typename key_type, typename value_type>
bool compare_map(ns::map<key_type, value_type> my_map,
                 std::map<key_type, value_type> std_map) {
  bool res = true;
  auto i2 = my_map.begin();
  for (auto i1 = std_map.begin(); i1 != std_map.end(); ++i1, ++i2) {
    if ((*i1).first != (*i2).first || (*i1).second != (*i2).second) res = false;
  }
  return res;
}

TEST(map, default_constructor_1) {
  ns::map<int, int> A;
  ASSERT_TRUE(A.empty());
  EXPECT_EQ(A.size(), 0);
}

TEST(map, default_constructor_2) {
  ns::map<char, int> A;
  ASSERT_TRUE(A.empty());
  EXPECT_EQ(A.size(), 0);
}

TEST(map, map_list) {
  ns::map<int, int> A{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  std::map<int, int> B{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), 4);
}

TEST(map, insert) {
  ns::map<int, int> A;
  std::map<int, int> B;
  A.insert({21, 21});
  B.insert({21, 21});
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map, copy_constructor) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  auto A1 = A;
  auto B1 = B;
  EXPECT_TRUE(compare_map(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
}

TEST(map, move_constructor) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  auto A1 = std::move(A);
  auto B1 = std::move(B);
  EXPECT_TRUE(compare_map(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
}

TEST(map, operaor_copy) {
  ns::map<int, int> A{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  ns::map<int, int> A1{{1, 1}, {2, 2}, {3, 3},  {4, 4},
                        {8, 4}, {9, 5}, {10, 6}, {-1, 0}};
  std::map<int, int> B{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  std::map<int, int> B1{{1, 1}, {2, 2}, {3, 3},  {4, 4},
                        {8, 4}, {9, 5}, {10, 6}, {-1, 0}};
  A = A1;
  B = B1;
  EXPECT_TRUE(compare_map(A1, B1));
}

TEST(map, move_operator) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  ns::map<int, int> A1;
  A1 = std::move(A);
  std::map<int, int> B1;
  B1 = std::move(B);
  EXPECT_TRUE(compare_map(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
}

TEST(map, func_at_1) {
  ns::map<int, int> A = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> B = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  for (size_t i = 1; i < A.size(); i++) EXPECT_EQ(A.at(i), B.at(i));
}

TEST(map, func_at_2) {
  ns::map<int, int> A = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> B = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  EXPECT_ANY_THROW(A.at(21));
}

TEST(map, func_at_3) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  EXPECT_EQ(A[9], B[9]);
  EXPECT_NO_THROW(A[5]);
  EXPECT_NO_THROW(B[5]);
  A.at(5) = 5;
  B.at(5) = 5;
  EXPECT_TRUE(compare_map(A, B));
}

TEST(map, func_begin) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  auto A1 = A.begin();
  auto B1 = B.begin();
  EXPECT_EQ((*A1).second, (*B1).second);
}

TEST(map, func_end_1) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  auto A1 = A.end();
  auto B1 = B.end();
  B1--;  // A.end() указывает на последний элемент контейнера
  EXPECT_EQ((*A1).second, (*B1).second);
}

TEST(map, func_end_2) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  auto A1 = A.end();
  auto B1 = B.end();
  A1++, B1++;
  EXPECT_EQ((*A1).second, (*B1).second);
}

TEST(map, func_end_4) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  auto A1 = A.end();
  auto B1 = B.end();
  ++A1, ++B1;
  EXPECT_EQ((*A1).second, (*B1).second);
}

TEST(map, func_empty_1) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  EXPECT_FALSE(A.empty());
}

TEST(map, func_empty_2) {
  ns::map<int, int> A;
  EXPECT_TRUE(A.empty());
}

TEST(map, func_clear_1) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  A.clear();
  EXPECT_TRUE(A.empty());
}

TEST(map, func_clear_2) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  A.clear();
  B.clear();
  EXPECT_EQ(A.size(), B.size());
}

TEST(map, func_clear_3) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  A.clear();
  B.clear();
  EXPECT_EQ(A.empty(), B.empty());
  EXPECT_EQ(A.size(), B.size());
}
TEST(map, func_size_1) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  EXPECT_EQ(A.size(), B.size());
}

TEST(map, func_size_2) {
  ns::map<int, int> A;
  std::map<int, int> B;
  EXPECT_EQ(A.size(), B.size());
}

TEST(map, func_insert_pair_1) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::pair<int, int> pair = {3, 1};
  EXPECT_EQ(A.insert(pair).second, B.insert(pair).second);
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map_test, func_insert_pair_2) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::pair<int, int> pair = {9, 1};
  EXPECT_EQ(A.insert(pair).second, B.insert(pair).second);
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map, func_insert_pair_3) {
  ns::map<int, int> A;
  std::map<int, int> B;
  std::pair<int, int> pair = {9, 1};
  EXPECT_EQ(A.insert(pair).second, B.insert(pair).second);
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map_test, func_insert_or_assign_1) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  EXPECT_EQ(A.insert_or_assign(1, 1).second, B.insert_or_assign(1, 1).second);
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map_test, func_insert_or_assign_2) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  EXPECT_EQ(A.insert_or_assign(9, 1).second, B.insert_or_assign(9, 1).second);
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map, func_insert_or_assign_3) {
  ns::map<int, int> A;
  std::map<int, int> B;
  EXPECT_EQ(A.insert_or_assign(9, 1).second, B.insert_or_assign(9, 1).second);
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map, func_insert_key_obj_1) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  EXPECT_FALSE(A.insert(9, 1).second);
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map, func_insert_key_obj_2) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}, {1, 1}};
  EXPECT_TRUE(A.insert(1, 1).second);
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map, func_insert_key_obj_3) {
  ns::map<int, int> A;
  std::map<int, int> B = {{9, 1}};
  EXPECT_TRUE(A.insert(9, 1).second);
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map_test, func_erase_1) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  auto A1 = A.begin();
  auto B1 = B.begin();
  A.erase(A1);
  B.erase(B1);
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map, func_erase_2) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  EXPECT_NO_THROW(A.erase(A.end()));
  EXPECT_EQ(A.size(), B.size() - 1);
}

TEST(map_test, func_swap_1) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  ns::map<int, int> A1;
  std::map<int, int> B1;
  A1.swap(A);
  B1.swap(B);
  EXPECT_TRUE(compare_map(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
}

TEST(map, func_swap_2) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  ns::map<int, int> A1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> B1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  A1.swap(A);
  B1.swap(B);
  EXPECT_TRUE(compare_map(A1, B1));
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.empty(), B.empty());
}

TEST(map, func_swap_3) {
  ns::map<int, int> A;
  std::map<int, int> B;
  ns::map<int, int> A1;
  std::map<int, int> B1;
  A1.swap(A);
  B1.swap(B);
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
}

TEST(map, func_merge_1) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  ns::map<int, int> A1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  std::map<int, int> B1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
  A1.merge(A);
  B1.merge(B);
  EXPECT_TRUE(compare_map(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.empty(), B.empty());
}

TEST(map, func_merge_2) {
  ns::map<int, int> A = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  std::map<int, int> B = {{9, 9}, {10, 10}, {123, 123}, {-4, -4}};
  ns::map<int, int> A1;
  std::map<int, int> B1;
  A1.merge(A);
  B1.merge(B);
  EXPECT_TRUE(compare_map(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.empty(), B.empty());
}

TEST(map, func_contains_1) {
  ns::map<int, int> A{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  EXPECT_TRUE(A.contains(1));
}

TEST(map, func_contains_23) {
  ns::map<int, int> A{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  EXPECT_FALSE(A.contains(6));
}

TEST(map, func_insert_many_1) {
  ns::map<int, int> A{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  std::map<int, int> B{{1, 1}, {2, 2}, {3, 3},  {4, 4},
                       {8, 4}, {9, 5}, {10, 6}, {-1, 0}};
  A.insert_many(std::make_pair(8, 4), std::make_pair(9, 5),
                std::make_pair(10, 6), std::make_pair(-1, 0));
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map, func_insert_many_2) {
  ns::map<int, int> A;
  std::map<int, int> B{{8, 4}, {9, 5}, {10, 6}, {-1, 0}};
  A.insert_many(std::make_pair(8, 4), std::make_pair(9, 5),
                std::make_pair(10, 6), std::make_pair(-1, 0));
  EXPECT_TRUE(compare_map(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(map, max_size_function) {
  ns::map<int, int> A{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  std::map<int, int> B{{1, 1}, {2, 2}, {3, 3}, {4, 4}};

  EXPECT_EQ(A.max_size(), 2 * B.max_size());

  std::map<int, char> A1;
  ns::map<int, char> B1;

  EXPECT_EQ(2 * A1.max_size(), B1.max_size());
}

TEST(map, big_erase_1) {
  ns::map<int, int> A{{1, 1},   {2, 2},   {3, 3},   {4, 4},
                       {5, 5},   {6, 6},   {7, 7},   {8, 8},
                       {9, 9},   {10, 10}, {11, 11}, {12, 12},
                       {13, 13}, {14, 14}, {15, 15}, {16, 16}};
  std::map<int, int> B{{1, 1},   {2, 2},   {3, 3},   {4, 4},
                       {5, 5},   {6, 6},   {7, 7},   {8, 8},
                       {9, 9},   {10, 10}, {11, 11}, {12, 12},
                       {13, 13}, {14, 14}, {15, 15}, {16, 16}};
  auto A1 = A.begin();
  auto B1 = B.begin();

  EXPECT_TRUE(A.IsBalanced());
  A.erase(A1);
  B.erase(B1);

  auto A2 = A.begin();
  auto B2 = B.begin();
  ++A2;
  ++B2;
  A.erase(A2);
  B.erase(B2);
  EXPECT_TRUE(compare_map(A, B));

  auto a = (int)A.size();
  for (int i = 0; i < a; ++i) {
    auto A3 = A.begin();
    A.erase(A3);
    EXPECT_TRUE(A.IsBalanced());
  }
  EXPECT_TRUE(A.empty());
}
