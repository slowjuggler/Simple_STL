#include "unit-tests.h"

TEST(array, defaullt_constructor) {
  std::array<int, 5> std_arr1;
  ns::array<int, 5> ns_arr1;
  EXPECT_EQ(std_arr1.size(), ns_arr1.size());

  std::array<int, 0> std_arr2;
  ns::array<int, 0> ns_arr2;
  EXPECT_EQ(std_arr2.size(), ns_arr2.size());
}

TEST(array, list_constructor) {
  std::array<int, 5> std_arr1 = {1, 2, 3};
  ns::array<int, 5> ns_arr1 = {1, 2, 3};
  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr1[i], ns_arr1[i]);

  std::array<int, 5> std_arr2 = {1, 2, 3, 4, 5};
  ns::array<int, 5> ns_arr2 = {1, 2, 3, 4, 5};
  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr2[i], ns_arr2[i]);

  std::array<int, 0> std_arr3 = {};
  ns::array<int, 0> ns_arr3 = {};
  EXPECT_EQ(std_arr3.size(), ns_arr3.size());
}

TEST(array, copy_constructor) {
  std::array<int, 5> std_arr1 = {1, 2, 3};
  ns::array<int, 5> ns_arr1 = {1, 2, 3};

  std::array<int, 5> std_arr2(std_arr1);
  ns::array<int, 5> ns_arr2(ns_arr1);

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr2[i], ns_arr2[i]);
}

TEST(array, move_constructor) {
  std::array<int, 5> std_arr1 = {1, 2, 3};
  ns::array<int, 5> ns_arr1 = {1, 2, 3};

  std::array<int, 5> std_arr2(std::move(std_arr1));
  ns::array<int, 5> ns_arr2(std::move(ns_arr1));

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr2[i], ns_arr2[i]);
}

TEST(array, copy_operator) {
  std::array<int, 5> std_arr1 = {1, 2, 3};
  ns::array<int, 5> ns_arr1 = {1, 2, 3};

  std::array<int, 5> std_arr2;
  ns::array<int, 5> ns_arr2;

  std_arr2 = std_arr1;
  ns_arr2 = ns_arr1;

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr2[i], ns_arr2[i]);
}

TEST(array, move_operator) {
  std::array<int, 5> std_arr1 = {1, 2, 3};
  ns::array<int, 5> ns_arr1 = {1, 2, 3};

  std::array<int, 5> std_arr2;
  ns::array<int, 5> ns_arr2;

  std_arr2 = std::move(std_arr1);
  ns_arr2 = std::move(ns_arr1);

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr2[i], ns_arr2[i]);
  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr1[i], ns_arr1[i]);
}

TEST(array, at_function) {
  std::array<int, 5> std_arr1 = {1, 2, 3};
  ns::array<int, 5> ns_arr1 = {1, 2, 3};

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr1.at(i), ns_arr1.at(i));
}

TEST(array, bracket_operator) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  ns::array<int, 5> ns_arr1 = {5, 4, 3, 2, 1};

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_arr1[i], ns_arr1[i]);
}

TEST(array, front_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  ns::array<int, 5> ns_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.front(), ns_arr1.front());
}

TEST(array, back_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  ns::array<int, 5> ns_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.back(), ns_arr1.back());
}

TEST(array, data_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  ns::array<int, 5> ns_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.data(), &std_arr1[0]);
  EXPECT_EQ(ns_arr1.data(), &ns_arr1[0]);
}

TEST(array, begin_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  ns::array<int, 5> ns_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.begin(), &std_arr1[0]);
  EXPECT_EQ(ns_arr1.begin(), &ns_arr1[0]);
}

TEST(array, cbegin_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  ns::array<int, 5> ns_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.cbegin(), &std_arr1[0]);
  EXPECT_EQ(ns_arr1.cbegin(), &ns_arr1[0]);
}

TEST(array, end_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  ns::array<int, 5> ns_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.end(), &std_arr1[5]);
  EXPECT_EQ(ns_arr1.end(), &ns_arr1[5]);
}

TEST(array, cend_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  ns::array<int, 5> ns_arr1 = {5, 4, 3, 2, 1};

  EXPECT_EQ(std_arr1.cend(), &std_arr1[5]);
  EXPECT_EQ(ns_arr1.cend(), &ns_arr1[5]);
}

TEST(array, empty_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  ns::array<int, 5> ns_arr1 = {5, 4, 3, 2, 1};
  EXPECT_EQ(std_arr1.empty(), ns_arr1.empty());

  std::array<int, 0> std_arr2;
  ns::array<int, 0> ns_arr2;
  EXPECT_EQ(std_arr2.empty(), ns_arr2.empty());
}

TEST(array, size_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  ns::array<int, 5> ns_arr1 = {5, 4, 3, 2, 1};
  EXPECT_EQ(std_arr1.size(), ns_arr1.size());

  std::array<int, 0> std_arr2;
  ns::array<int, 0> ns_arr2;
  EXPECT_EQ(std_arr2.size(), ns_arr2.size());
}

TEST(array, max_size_function) {
  std::array<int, 5> std_arr1 = {5, 4, 3, 2, 1};
  ns::array<int, 5> ns_arr1 = {5, 4, 3, 2, 1};
  EXPECT_EQ(std_arr1.max_size(), ns_arr1.max_size());

  std::array<int, 0> std_arr2;
  ns::array<int, 0> ns_arr2;
  EXPECT_EQ(std_arr2.max_size(), ns_arr2.max_size());
}

class ArrayTest : public ::testing::Test {
 protected:
  void SetUp(void) override {
    for (size_t i = 0; i < 10; ++i) {
      ns_4[i] = 0.99 + i * 17.75;
      std_4[i] = 0.99 + i * 17.75;
      ns_5[i] = 0.99 - i * 17.75;
      std_5[i] = 0.99 - i * 17.75;
    }
  }

  ns::array<int, 1> ns_0;
  ns::array<int, 100> ns_1;
  ns::array<double, 5> ns_2 = {1.1, 2.2, 3.3, 4.4, 5.5};
  ns::array<float, 10> ns_3 = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
  ns::array<float, 10> ns_4;
  ns::array<float, 10> ns_5;
  const ns::array<float, 5> ns_const_array = {1.1, 2.2, 3.3, 4.4, 5.5};

  ns::array<int, 1> std_0;
  std::array<int, 100> std_1;
  std::array<double, 5> std_2 = {1.1, 2.2, 3.3, 4.4, 5.5};
  std::array<float, 10> std_3 = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
  std::array<float, 10> std_4;
  std::array<float, 10> std_5;
  const std::array<float, 5> std_const_array = {1.1, 2.2, 3.3, 4.4, 5.5};
};

TEST_F(ArrayTest, InitializedListCtor) {
  for (size_t i = 0; i < std_2.size(); ++i) {
    EXPECT_EQ(ns_2[i], std_2[i]);
  }
  for (size_t i = 0; i < std_3.size(); ++i) {
    EXPECT_EQ(ns_3[i], std_3[i]) << "i = " << i;
  }

  try {
    ns::array<int, 3> tmp = {1, 2, 3, 4};
    EXPECT_EQ(1, 0);
  } catch (const std::exception &e) {
    EXPECT_EQ(1, 1);
  }
}

TEST_F(ArrayTest, CopyCtor) {
  ns::array<float, 10> ns_tmp(ns_4);
  std::array<float, 10> std_tmp(std_4);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(ns_tmp[i], std_tmp[i]);
  }
}

TEST_F(ArrayTest, MoveCtor) {
  ns::array<float, 10> ns_tmp(std::move(ns_4));
  std::array<float, 10> std_tmp(std::move(std_4));
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(ns_tmp[i], std_tmp[i]);
  }
}

TEST_F(ArrayTest, OperatorAssign) {
  ns::array<float, 10> ns_tmp;
  std::array<float, 10> std_tmp;

  ns_tmp = ns_4;
  std_tmp = std_4;
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(ns_tmp[i], std_tmp[i]);
  }
}

TEST_F(ArrayTest, MoveOperatorAssign) {
  ns::array<float, 10> ns_tmp;
  std::array<float, 10> std_tmp;

  ns_tmp = std::move(ns_4);
  std_tmp = std::move(std_4);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(ns_tmp[i], std_tmp[i]);
  }
}

TEST_F(ArrayTest, Capacity) {
  ns::array<double, 1023> tmp;

  EXPECT_EQ(tmp.size(), 1023);
  EXPECT_EQ(tmp.max_size(), 1023);
  EXPECT_FALSE(tmp.empty());

  ns::array<float, 0> arr;
  EXPECT_EQ(arr.size(), 0);
  EXPECT_EQ(arr.max_size(), 0);
  EXPECT_TRUE(arr.empty());
}

TEST_F(ArrayTest, Swap) {
  ns_4.swap(ns_5);
  std_4.swap(std_5);

  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(ns_4[i], std_4[i]);
    EXPECT_EQ(ns_5[i], std_5[i]);
  }
}

TEST_F(ArrayTest, Fill) {
  ns_4.fill(18.98);
  std_4.fill(18.98);

  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(ns_4[i], std_4[i]);
  }
}
