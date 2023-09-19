#include "unit-tests.h"

template <typename value_type1, typename value_type2>
bool compare_stacks(ns::stack<value_type1> my_stack,
                    std::stack<value_type2> std_stack) {
  bool res = (my_stack.size() == std_stack.size());
  while (!my_stack.empty() && !std_stack.empty()) {
    if (my_stack.top() != std_stack.top()) res = false;
    my_stack.pop();
    std_stack.pop();
  }
  return res;
}

TEST(stack, default_constructor) {
  ns::stack<int> A;
  ASSERT_TRUE(A.empty());
  ASSERT_EQ(A.size(), 0);
}

TEST(stack, push_1) {
  ns::stack<int> A{1, 2, 3, 4};
  std::stack<int> B;
  for (int i = 1; i < 5; ++i) B.push(i);
  EXPECT_TRUE(compare_stacks(A, B));
}

TEST(stack, push_2) {
  ns::stack<char> A{'a', 'b', 'c'};
  std::stack<char> B;
  for (char i = 'b'; i < 'g'; ++i) B.push(i);
  EXPECT_FALSE(compare_stacks(A, B));
}

TEST(stack, copy_constructor_1) {
  ns::stack<char> A{'a', 'b', 'c'};
  ns::stack<char> B(A);
  std::stack<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  std::stack<char> D(C);
  EXPECT_TRUE(compare_stacks(B, D));
}

TEST(stack, copy_constructor_2) {
  ns::stack<char> A{'a', 'b', 'c'};
  ns::stack<char> B(A);
  std::stack<int> C;
  for (int i = 0; i < 2; ++i) C.push(i);
  std::stack<int> D(C);
  EXPECT_FALSE(compare_stacks(B, D));
}

TEST(stack, copy_constructor_3) {
  const ns::stack<char> A{'a', 'b', 'c'};
  const ns::stack<char> B(A);
  std::stack<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::stack<char> D(C);
  EXPECT_TRUE(compare_stacks(B, D));
}

TEST(stack, func_move_1) {
  ns::stack<char> A{'a', 'b', 'c'};
  ns::stack<char> B(std::move(A));
  std::stack<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::stack<char> D(std::move(C));
  EXPECT_TRUE(compare_stacks(B, D));
}

TEST(stack, copy_operator_1) {
  ns::stack<char> A{'a', 'b', 'c'};
  ns::stack<char> B = A;
  std::stack<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::stack<char> D = C;
  EXPECT_TRUE(compare_stacks(B, D));
}

TEST(stack, copy_operator_2) {
  ns::stack<char> A{'a', 'b', 'c'};
  ns::stack<char> B = A;
  std::stack<int> C;
  for (int i = 0; i < 2; ++i) C.push(i);
  std::stack<int> D = C;
  EXPECT_FALSE(compare_stacks(B, D));
}

TEST(stack, move_operator_1) {
  ns::stack<char> A{'a', 'b', 'c'};
  ns::stack<char> B = std::move(A);
  std::stack<int> C;
  for (int i = 0; i < 2; ++i) C.push(i);
  std::stack<int> D = std::move(C);
  EXPECT_FALSE(compare_stacks(B, D));
}

TEST(stack, move_operator_2) {
  ns::stack<char> A{'a', 'b', 'c'};
  ns::stack<char> B = std::move(A);
  std::stack<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::stack<char> D = std::move(C);
  EXPECT_TRUE(compare_stacks(B, D));
}

TEST(stack, func_top_1) {
  ns::stack<char> A{'a', 'b', 'c'};
  EXPECT_EQ('c', A.top());
}

TEST(stack, func_top_2) {
  const ns::stack<char> A{'a', 'b', 'c'};
  EXPECT_EQ('c', A.top());
}

TEST(stack, func_size_1) {
  const ns::stack<char> A{'a', 'b', 'c'};
  EXPECT_EQ(3, A.size());
}
TEST(stack, func_size_2) {
  const ns::stack<int> A{6, 7, 8, 9, 78};
  EXPECT_EQ(5, A.size());
}

TEST(stack, func_push_1) {
  ns::stack<int> A{6, 7, 8, 9, 78};
  A.push(187);
  EXPECT_EQ(187, A.top());
}

TEST(stack, func_push_2) {
  ns::stack<int> A{6, 7, 8, 9, 78};
  A.push(std::move(187));
  EXPECT_EQ(187, A.top());
}

TEST(stack, func_pop_1) {
  ns::stack<int> A{6, 7, 8, 9, 78};
  A.pop();
  EXPECT_EQ(9, A.top());
}
TEST(stack, func_swap_1) {
  ns::stack<char> A{'a', 'd', 'g'};
  ns::stack<char> B{'c', 'g', 'y'};
  std::stack<char> C;
  C.push('a');
  C.push('d');
  C.push('g');
  std::stack<char> D;
  D.push('c');
  D.push('g');
  D.push('y');
  A.swap(B);
  C.swap(D);
  EXPECT_TRUE(compare_stacks(B, D));
  EXPECT_TRUE(compare_stacks(A, C));
}

TEST(stack, func_pop_2) {
  ns::stack<char> A{'a', 'd', 'g'};
  A.pop();
  A.pop();
  EXPECT_EQ('a', A.top());
}

TEST(stack, func_insert_many_front_1) {
  std::stack<int> A;
  for (char i = 1; i < 9; ++i) A.push(i);
  ns::stack<int> B{1, 2, 3, 4, 5};

  B.insert_many_front(6, 7, 8);

  EXPECT_EQ(B.size(), A.size());
  EXPECT_TRUE(compare_stacks(B, A));
}

TEST(stack, func_insert_many_front_2) {
  std::stack<char> A;
  for (char i = 'a'; i < 'd'; ++i) A.push(i);
  ns::stack<char> B;

  B.insert_many_front('a', 'b', 'c');

  EXPECT_EQ(B.size(), A.size());
  EXPECT_TRUE(compare_stacks(B, A));
}
