#include "unit-tests.h"

template <typename value_type1, typename value_type2>
bool compare_queues(ns::queue<value_type1> my_queue,
                    std::queue<value_type2> std_queue) {
  bool res = (my_queue.size() == std_queue.size());
  while (!my_queue.empty() && !std_queue.empty()) {
    if (my_queue.front() != std_queue.front()) res = false;
    my_queue.pop();
    std_queue.pop();
  }
  return res;
}

TEST(queue, default_constructor) {
  ns::queue<int> A;
  ASSERT_TRUE(A.empty());
  ASSERT_EQ(A.size(), 0);
}

TEST(queue, push_1) {
  ns::queue<int> A{1, 2, 3, 4};
  std::queue<int> B;
  for (int i = 1; i < 5; ++i) B.push(i);
  EXPECT_TRUE(compare_queues(A, B));
}

TEST(queue, push_2) {
  ns::queue<char> A{'a', 'b', 'c'};
  std::queue<char> B;
  for (char i = 'b'; i < 'g'; ++i) B.push(i);
  EXPECT_FALSE(compare_queues(A, B));
}

TEST(queue, copy_constructor_1) {
  ns::queue<char> A{'a', 'b', 'c'};
  ns::queue<char> B(A);
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  std::queue<char> D(C);
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, copy_constructor_2) {
  const ns::queue<char> A{'a', 'b', 'c'};
  const ns::queue<char> B(A);
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::queue<char> D(C);
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, func_move_1) {
  ns::queue<char> A{'a', 'b', 'c'};
  ns::queue<char> B(std::move(A));
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::queue<char> D(std::move(C));
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, copy_operator) {
  ns::queue<char> A{'a', 'b', 'c'};
  ns::queue<char> B = A;
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::queue<char> D = C;
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, copy_constructor_4) {
  ns::queue<char> A{'a', 'b', 'c'};
  ns::queue<char> B = A;
  std::queue<int> C;
  for (int i = 0; i < 2; ++i) C.push(i);
  std::queue<int> D = C;
  EXPECT_FALSE(compare_queues(B, D));
}

TEST(queue, move_constructor_1) {
  ns::queue<char> A{'a', 'b', 'c'};
  ns::queue<char> B = std::move(A);
  std::queue<int> C;
  for (int i = 0; i < 2; ++i) C.push(i);
  std::queue<int> D = std::move(C);
  EXPECT_FALSE(compare_queues(B, D));
}

TEST(queue, move_constructor_2) {
  ns::queue<char> A{'a', 'b', 'c'};
  ns::queue<char> B = std::move(A);
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::queue<char> D = std::move(C);
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, func_front_1) {
  ns::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ('a', A.front());
}

TEST(queue, func_front_2) {
  const ns::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ('a', A.front());
}

TEST(queue, func_back_1) {
  ns::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ('c', A.back());
}
TEST(queue, func_back_2) {
  const ns::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ('c', A.back());
}
TEST(queue, func_size_1) {
  const ns::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ(3, A.size());
}
TEST(queue, func_size_2) {
  const ns::queue<int> A{6, 7, 8, 9, 78};
  EXPECT_EQ(5, A.size());
}

TEST(queue, func_push_1) {
  ns::queue<int> A{6, 7, 8, 9, 78};
  A.push(187);
  EXPECT_EQ(187, A.back());
}

TEST(queue, func_push_2) {
  ns::queue<int> A{6, 7, 8, 9, 78};
  A.push(std::move(187));
  EXPECT_EQ(187, A.back());
}

TEST(queue, func_pop_0) {
  ns::queue<int> A{6, 7, 8, 9, 78};
  A.pop();
  EXPECT_EQ(7, A.front());
}
TEST(queue, func_swap_1) {
  ns::queue<char> A{'a', 'd', 'g'};
  ns::queue<char> B{'c', 'g', 'y'};
  std::queue<char> C;
  C.push('a');
  C.push('d');
  C.push('g');
  std::queue<char> D;
  D.push('c');
  D.push('g');
  D.push('y');
  A.swap(B);
  C.swap(D);
  EXPECT_TRUE(compare_queues(B, D));
  EXPECT_TRUE(compare_queues(A, C));
}

TEST(queue, func_pop_1) {
  ns::queue<char> A{'a', 'd', 'g'};
  A.pop();
  A.pop();
  EXPECT_EQ('g', A.front());
}

TEST(queue, func_insert_many_back_1) {
  std::queue<int> A;
  for (char i = 1; i < 9; ++i) A.push(i);
  ns::queue<int> B{1, 2, 3, 4, 5};

  B.insert_many_back(6, 7, 8);

  EXPECT_EQ(B.size(), A.size());
  EXPECT_TRUE(compare_queues(B, A));
}

TEST(stack, func_insert_many_back_2) {
  std::queue<char> A;
  for (char i = 'a'; i < 'd'; ++i) A.push(i);
  ns::queue<char> B;

  B.insert_many_back('a', 'b', 'c');

  EXPECT_EQ(B.size(), A.size());
  EXPECT_TRUE(compare_queues(B, A));
}
