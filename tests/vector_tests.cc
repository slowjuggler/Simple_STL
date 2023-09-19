#include "unit-tests.h"

TEST(vector, default_constructor) {
  std::vector<int> std_vector;
  ns::vector<int> ns_vector;

  EXPECT_EQ(std_vector.size(), ns_vector.size());
}

TEST(vector, parameterized_constructor) {
  std::vector<int> std_vector1(5);
  ns::vector<int> ns_vector1(5);

  EXPECT_EQ(std_vector1.size(), ns_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), ns_vector1.capacity());

  std::vector<int> std_vector2(0);
  ns::vector<int> ns_vector2(0);

  EXPECT_EQ(std_vector2.size(), ns_vector2.size());
  EXPECT_EQ(std_vector2.capacity(), ns_vector2.capacity());
}

TEST(vector, list_constructor) {
  std::vector<int> std_vector = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector.size(), ns_vector.size());
  EXPECT_EQ(std_vector.capacity(), ns_vector.capacity());

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_vector[i], ns_vector[i]);
}

TEST(vector, copy_constructor) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  std::vector<int> std_vector2(std_vector1);
  ns::vector<int> ns_vector2(ns_vector1);

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_vector2[i], ns_vector2[i]);

  EXPECT_EQ(std_vector2.size(), ns_vector2.size());
  EXPECT_EQ(std_vector2.capacity(), ns_vector2.capacity());
}

TEST(vector, move_constructor) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  std::vector<int> std_vector2(std::move(std_vector1));
  ns::vector<int> ns_vector2(std::move(ns_vector1));

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_vector2[i], ns_vector2[i]);

  EXPECT_EQ(std_vector2.size(), ns_vector2.size());
  EXPECT_EQ(std_vector2.capacity(), ns_vector2.capacity());
}

TEST(vector, copy_operator) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  std::vector<int> std_vector2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  ns::vector<int> ns_vector2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  std_vector2 = std_vector1;
  ns_vector2 = ns_vector1;

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_vector2[i], ns_vector2[i]);

  EXPECT_EQ(std_vector2.size(), ns_vector2.size());
  EXPECT_EQ(std_vector2.capacity(), ns_vector2.capacity());

  std::vector<int> std_vector3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  ns::vector<int> ns_vector3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::vector<int> std_vector4 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector4 = {1, 2, 3, 4, 5};

  std_vector4 = std_vector3;
  ns_vector4 = ns_vector3;

  for (int i = 0; i < 9; ++i) EXPECT_EQ(std_vector4[i], ns_vector4[i]);

  EXPECT_EQ(std_vector4.size(), ns_vector4.size());
}

TEST(vector, move_operator_1) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  std::vector<int> std_vector2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  ns::vector<int> ns_vector2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  std_vector2 = std::move(std_vector1);
  ns_vector2 = std::move(ns_vector1);

  for (int i = 0; i < 5; ++i) EXPECT_EQ(std_vector2[i], ns_vector2[i]);

  EXPECT_EQ(std_vector2.size(), ns_vector2.size());
  EXPECT_EQ(std_vector2.capacity(), ns_vector2.capacity());
}

TEST(vector, move_operator_2) {
  std::vector<int> std_vector3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  ns::vector<int> ns_vector3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::vector<int> std_vector4 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector4 = {1, 2, 3, 4, 5};

  std_vector4 = std::move(std_vector3);
  ns_vector4 = std::move(ns_vector3);

  for (int i = 0; i < 9; ++i) EXPECT_EQ(std_vector4[i], ns_vector4[i]);

  EXPECT_EQ(std_vector4.size(), ns_vector4.size());
  EXPECT_EQ(std_vector4.capacity(), ns_vector4.capacity());
}

TEST(vector, at_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(std_vector1.at(i), ns_vector1.at(i));
  }
}

TEST(vector, brackets_operator) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(std_vector1[i], ns_vector1[i]);
  }
}

TEST(vector, front_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector1.front(), ns_vector1.front());
}

TEST(vector, back_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector1.back(), ns_vector1.back());
}

TEST(vector, data_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  EXPECT_TRUE(std_vector1.data() == &std_vector1.front());
  EXPECT_TRUE(ns_vector1.data() == &ns_vector1.front());
}

TEST(vector, begin_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(*std_vector1.begin(), *ns_vector1.begin());
  EXPECT_EQ(*std_vector1.cbegin(), *ns_vector1.cbegin());
}

TEST(vector, empty_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector1.empty(), ns_vector1.empty());

  std::vector<int> std_vector2;
  ns::vector<int> ns_vector2;

  EXPECT_EQ(std_vector2.empty(), ns_vector2.empty());
}

TEST(vector, size_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector1.size(), ns_vector1.size());

  std::vector<int> std_vector2;
  ns::vector<int> ns_vector2;

  EXPECT_EQ(std_vector2.size(), ns_vector2.size());
}

TEST(vector, max_size_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector1.max_size(), ns_vector1.max_size());

  std::vector<int> std_vector2;
  ns::vector<int> ns_vector2;

  EXPECT_EQ(std_vector2.max_size(), ns_vector2.max_size());
}

TEST(vector, capacity_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_vector1.capacity(), ns_vector1.capacity());

  std::vector<int> std_vector2;
  ns::vector<int> ns_vector2;

  EXPECT_EQ(std_vector2.capacity(), ns_vector2.capacity());
}

TEST(vector, push_back_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  std_vector1.push_back(6);
  ns_vector1.push_back(6);

  EXPECT_EQ(std_vector1.size(), ns_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), ns_vector1.capacity());
  EXPECT_EQ(std_vector1[5], ns_vector1[5]);
}

TEST(vector, pop_back_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  std_vector1.pop_back();
  ns_vector1.pop_back();

  EXPECT_EQ(std_vector1.size(), ns_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), ns_vector1.capacity());
}

TEST(vector, shrink_to_fit_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  std_vector1.pop_back();
  ns_vector1.pop_back();

  std_vector1.pop_back();
  ns_vector1.pop_back();

  std_vector1.shrink_to_fit();
  ns_vector1.shrink_to_fit();

  EXPECT_EQ(std_vector1.size(), ns_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), ns_vector1.capacity());
}

TEST(vector, reserve_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  std_vector1.reserve(10);
  ns_vector1.reserve(10);

  EXPECT_EQ(std_vector1.size(), ns_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), ns_vector1.capacity());
}

TEST(vector, clear_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  std_vector1.clear();
  ns_vector1.clear();

  EXPECT_EQ(std_vector1.size(), ns_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), ns_vector1.capacity());
}

TEST(vector, insert_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  std_vector1.insert(std_vector1.begin(), 6);
  ns_vector1.insert(ns_vector1.begin(), 6);

  for (int i = 0; i < 6; ++i) {
    EXPECT_EQ(std_vector1[i], ns_vector1[i]);
  }
  EXPECT_EQ(std_vector1.size(), ns_vector1.size());

  auto std_pos = std_vector1.insert(std_vector1.begin() + 3, 7);
  auto ns_pos = ns_vector1.insert(ns_vector1.begin() + 3, 7);

  for (int i = 0; i < 7; ++i) {
    EXPECT_EQ(std_vector1[i], ns_vector1[i]);
  }

  EXPECT_EQ(*std_pos, *ns_pos);
  EXPECT_EQ(std_vector1.size(), ns_vector1.size());

  std_pos = std_vector1.insert(std_vector1.end(), 8);
  ns_pos = ns_vector1.insert(ns_vector1.end(), 8);

  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(std_vector1[i], ns_vector1[i]);
  }

  EXPECT_EQ(*std_pos, *ns_pos);

  EXPECT_EQ(std_vector1.size(), ns_vector1.size());
}

TEST(vector, erase_function_1) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5, 6, 7, 8};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5, 6, 7, 8};

  std_vector1.erase(std_vector1.begin());
  ns_vector1.erase(ns_vector1.begin());

  int vector_size = (int)ns_vector1.size();
  for (int i = 0; i < vector_size; ++i) {
    EXPECT_EQ(std_vector1[i], ns_vector1[i]);
  }
}

TEST(vector, erase_function_2) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5, 6, 7, 8};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5, 6, 7, 8};

  std_vector1.erase(std_vector1.begin() + 3);
  ns_vector1.erase(ns_vector1.begin() + 3);

  for (int i = 0; i < (int)ns_vector1.size(); ++i) {
    EXPECT_EQ(std_vector1[i], ns_vector1[i]);
  }
}

TEST(vector, erase_function_3) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5, 6, 7, 8};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std_vector1.erase(std_vector1.end() - 1);
  ns_vector1.erase(ns_vector1.end() - 1);

  for (int i = 0; i < (int)ns_vector1.size(); ++i) {
    EXPECT_EQ(std_vector1[i], ns_vector1[i]);
  }

  EXPECT_EQ(std_vector1.size(), ns_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), ns_vector1.capacity());
}

TEST(vector, swap_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3, 4, 5};

  std::vector<int> std_vector2 = {6, 7, 8, 9};
  ns::vector<int> ns_vector2 = {6, 7, 8, 9};

  std_vector2.swap(std_vector1);
  ns_vector2.swap(ns_vector1);

  EXPECT_EQ(std_vector1[0], ns_vector1[0]);
  EXPECT_EQ(std_vector2[0], ns_vector2[0]);

  EXPECT_EQ(std_vector1.size(), ns_vector1.size());
  EXPECT_EQ(std_vector1.capacity(), ns_vector1.capacity());

  EXPECT_EQ(std_vector2.size(), ns_vector2.size());
  EXPECT_EQ(std_vector2.capacity(), ns_vector2.capacity());
}

TEST(vector, insert_many_function) {
  std::vector<int> std_vector1 = {4, 5, 6, 7, 8};
  ns::vector<int> ns_vector1 = {4, 5};

  auto pos = ns_vector1.insert_many(ns_vector1.end(), 6, 7, 8);

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(std_vector1[i], ns_vector1[i]);
  }

  std_vector1 = {1, 2, 3, 4, 5, 6, 7, 8};
  pos = ns_vector1.insert_many(ns_vector1.begin(), 1, 2, 3);

  EXPECT_EQ(4, *pos);

  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(std_vector1[i], ns_vector1[i]);
  }

  std_vector1 = {1, 2, 3, 4, 5, 5, 5, 5, 6, 7, 8};
  pos = ns_vector1.insert_many(ns_vector1.begin() + 4, 5, 5, 5);

  EXPECT_EQ(5, *pos);

  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(std_vector1[i], ns_vector1[i]);
  }
}

TEST(vector, insert_many_back_function) {
  std::vector<int> std_vector1 = {1, 2, 3, 4, 5};
  ns::vector<int> ns_vector1 = {1, 2, 3};

  ns_vector1.insert_many_back(4, 5);

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(std_vector1[i], ns_vector1[i]);
  }

  std_vector1 = {1, 2, 3, 4, 5, 6, 7, 8};
  ns_vector1.insert_many_back(6, 7, 8);

  for (int i = 0; i < 8; ++i) {
    EXPECT_EQ(std_vector1[i], ns_vector1[i]);
  }
}
