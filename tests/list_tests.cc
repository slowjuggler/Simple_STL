#include <string>

#include "unit-tests.h"

TEST(list, default_constructor) {
  std::list<int> std_list;
  ns::list<int> ns_list;

  EXPECT_EQ(std_list.size(), ns_list.size());
}

TEST(list, parameterized_constructor) {
  std::list<int> std_list(3);
  ns::list<int> ns_list(3);

  auto ns_it = ns_list.begin();
  for (auto std_it = std_list.begin(); std_it != std_list.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  EXPECT_EQ(std_list.size(), ns_list.size());
}

TEST(list, list_constructor) {
  std::list<int> std_list = {1, 2, 3};
  ns::list<int> ns_list = {1, 2, 3};

  auto ns_it = ns_list.begin();
  for (auto std_it = std_list.begin(); std_it != std_list.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  EXPECT_EQ(std_list.size(), ns_list.size());
}

TEST(list, copy_constructor) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  std::list<int> std_list2(std_list1);
  ns::list<int> ns_list2(ns_list1);

  auto ns_it = ns_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  EXPECT_EQ(std_list2.size(), ns_list2.size());
}

TEST(list, move_constructor) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  std::list<int> std_list2(std::move(std_list1));
  ns::list<int> ns_list2(std::move(ns_list1));

  auto ns_it = ns_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  EXPECT_EQ(std_list2.size(), ns_list2.size());
}

TEST(list, copy_operator) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  std::list<int> std_list2 = {5, 4, 3, 2, 1};
  ns::list<int> ns_list2 = {5, 4, 3, 2, 1};

  std_list2 = std_list1;
  ns_list2 = ns_list1;

  auto ns_it = ns_list2.begin();
  for (auto std_it = std_list2.begin();
       ns_it != ns_list2.end(), std_it != std_list2.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  EXPECT_EQ(std_list2.size(), ns_list2.size());
}

TEST(list, move_operator) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  std::list<int> std_list2 = {5, 4, 3, 2, 1};
  ns::list<int> ns_list2 = {5, 4, 3, 2, 1};

  std_list2 = std::move(std_list1);
  ns_list2 = std::move(ns_list1);

  auto ns_it = ns_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  EXPECT_EQ(std_list2.size(), ns_list2.size());
}

TEST(list, front_function) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.front(), ns_list1.front());

  std::list<int> std_list2;
  ns::list<int> ns_list2;

  EXPECT_EQ(std_list2.front(), ns_list2.front());
}

TEST(list, back_function) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.back(), ns_list1.back());

  std::list<int> std_list2;
  ns::list<int> ns_list2;

  EXPECT_EQ(std_list2.back(), ns_list2.back());
}

TEST(list, begin_function_1) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  EXPECT_EQ(*std_list1.begin(), *ns_list1.begin());
}

TEST(list, begin_function_2) {
  std::list<char> std_list2;
  ns::list<char> ns_list2;
  EXPECT_EQ(*std_list2.begin(), *ns_list2.begin());
}

TEST(list, cbegin_function) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  EXPECT_EQ(*std_list1.cbegin(), *ns_list1.cbegin());

  std::list<int> std_list2;
  ns::list<int> ns_list2;

  EXPECT_EQ(*std_list2.cbegin(), *ns_list2.cbegin());
}

TEST(list, end_function) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  EXPECT_EQ(*(--std_list1.end()),
            *(--ns_list1.end()));  // другая реализация end()

  std::list<int> std_list2;
  ns::list<int> ns_list2;

  EXPECT_EQ(*std_list2.end(), *ns_list2.end());
}

TEST(list, cend_function) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  EXPECT_EQ(*(--std_list1.cend()),
            *(--ns_list1.cend()));  // другая реализация cend()

  std::list<int> std_list2;
  ns::list<int> ns_list2;

  EXPECT_EQ(*std_list2.cend(), *ns_list2.cend());
}

TEST(list, empty_function) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.empty(), ns_list1.empty());

  std::list<int> std_list2;
  ns::list<int> ns_list2;

  EXPECT_EQ(std_list2.empty(), ns_list2.empty());
}

TEST(list, size_function) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  std::list<int> std_list2;
  ns::list<int> ns_list2;

  EXPECT_EQ(std_list2.size(), ns_list2.size());
}

TEST(list, max_size_function) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.max_size(), ns_list1.max_size());

  std::list<int> std_list2;
  ns::list<int> ns_list2;

  EXPECT_EQ(std_list2.max_size(), ns_list2.max_size());
}

TEST(list, clear_function) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  std_list1.clear();
  ns_list1.clear();

  EXPECT_EQ(std_list1.size(), ns_list1.size());
}

TEST(list, insert_function) {
  std::list<int> std_list1 = {1, 2, 3};
  ns::list<int> ns_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  auto std_pos = std_list1.insert(std_list1.begin(), 0);
  auto ns_pos = ns_list1.insert(ns_list1.begin(), 0);

  EXPECT_EQ(std_list1.size(), ns_list1.size());
  EXPECT_EQ(*std_pos, *ns_pos);

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  std_pos = std_list1.insert(--std_list1.end(), 0);
  ns_pos = ns_list1.insert(--ns_list1.end(), 0);  // разная реализация end()

  EXPECT_EQ(std_list1.size(), ns_list1.size());
  EXPECT_EQ(*std_pos, *ns_pos);

  ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, erase_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  ns::list<int> ns_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  std_list1.erase(std_list1.begin());
  ns_list1.erase(ns_list1.begin());

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  std_list1.erase(--std_list1.end());
  ns_list1.erase(--ns_list1.end());  // разница реализации end()

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, push_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  ns::list<int> ns_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  std_list1.push_back(6);
  ns_list1.push_back(6);

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, pop_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  ns::list<int> ns_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  std_list1.pop_back();
  ns_list1.pop_back();

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, push_front_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  ns::list<int> ns_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  std_list1.push_front(6);
  ns_list1.push_front(6);

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, pop_front_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  ns::list<int> ns_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  std_list1.pop_front();
  ns_list1.pop_front();

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, swap_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  ns::list<int> ns_list1 = {1, 2, 3, 4, 5};

  std::list<int> std_list2 = {5, 4, 3, 2, 1};
  ns::list<int> ns_list2 = {5, 4, 3, 2, 1};

  std_list1.swap(std_list2);
  ns_list1.swap(ns_list2);

  EXPECT_EQ(std_list1.size(), ns_list1.size());
  EXPECT_EQ(std_list2.size(), ns_list2.size());

  EXPECT_EQ(*std_list1.begin(), *ns_list1.begin());
  EXPECT_EQ(*std_list2.begin(), *ns_list2.begin());
}

TEST(list, merge_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  ns::list<int> ns_list1 = {1, 2, 3, 4, 5};

  std::list<int> std_list2 = {9, 8, 7};
  ns::list<int> ns_list2 = {9, 8, 7};

  std_list1.merge(std_list2);
  ns_list1.merge(ns_list2);

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  std_list1 = {9, 8, 7};
  ns_list1 = {9, 8, 7};

  std_list2 = {1, 2, 3, 4, 5};
  ns_list2 = {1, 2, 3, 4, 5};

  std_list1.merge(std_list2);
  ns_list1.merge(ns_list2);

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  std_list1 = {1, 2, 3, 4, 5};
  ns_list1 = {1, 2, 3, 4, 5};

  std_list2 = {1, 2, 3, 4, 5};
  ns_list2 = {1, 2, 3, 4, 5};

  std_list1.merge(std_list2);
  ns_list1.merge(ns_list2);

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, splice_function) {
  std::list<int> std_list1 = {1, 2, 3, 4};
  ns::list<int> ns_list1 = {1, 2, 3, 4};

  std::list<int> std_list2 = {9, 8, 7};
  ns::list<int> ns_list2 = {9, 8, 7};

  std_list1.splice(std_list1.end(), std_list2);
  ns_list1.splice(ns_list1.end(), ns_list2);

  EXPECT_EQ(std_list1.size(), ns_list1.size());
  EXPECT_EQ(std_list2.size(), ns_list2.size());

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  std_list2.splice(std_list2.begin(), std_list1);
  ns_list2.splice(ns_list2.begin(), ns_list1);  // cbegin

  EXPECT_EQ(std_list1.size(), ns_list1.size());
  EXPECT_EQ(std_list2.size(), ns_list2.size());

  ns_it = ns_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, reverse_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  ns::list<int> ns_list1 = {1, 2, 3, 4, 5};

  std_list1.reverse();
  ns_list1.reverse();

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, unique_function) {
  std::list<int> std_list1 = {1, 1, 2, 2, 3, 4, 5, 5, 5, 2};
  ns::list<int> ns_list1 = {1, 1, 2, 2, 3, 4, 5, 5, 5, 2};

  std_list1.unique();
  ns_list1.unique();

  EXPECT_EQ(std_list1.size(), ns_list1.size());
  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, sort_function) {
  std::list<int> std_list1 = {2, 7, 1, 3, 8, 2};
  ns::list<int> ns_list1 = {2, 7, 1, 3, 8, 2};

  std_list1.sort();
  ns_list1.sort();

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  std_list1 = {9, 8, 7, 6, 5};
  ns_list1 = {9, 8, 7, 6, 5};

  std_list1.sort();
  ns_list1.sort();

  EXPECT_EQ(std_list1.size(), ns_list1.size());

  ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, insert_many_function) {
  std::list<int> std_list1 = {1, 6, 7, 8, 2, 3, 4, 5};
  ns::list<int> ns_list1 = {1, 2, 3, 4, 5};

  auto pos = ns_list1.insert_many(++ns_list1.cbegin(), 6, 7, 8);

  EXPECT_EQ(8, ns_list1.size());
  EXPECT_EQ(6, *pos);

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }

  std_list1 = {1, 6, 7, 8, 2, 3, 4, 0, 0, 0, 5};

  pos = ns_list1.insert_many(--ns_list1.cend(), 0, 0, 0);

  EXPECT_EQ(11, ns_list1.size());
  EXPECT_EQ(0, *pos);

  ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, insert_many_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5, 6, 7, 8};
  ns::list<int> ns_list1 = {1, 2, 3, 4, 5};

  ns_list1.insert_many_back(6, 7, 8);

  EXPECT_EQ(8, ns_list1.size());

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}

TEST(list, insert_many_front_function) {
  std::list<int> std_list1 = {6, 7, 8, 1, 2, 3, 4, 5};
  ns::list<int> ns_list1 = {1, 2, 3, 4, 5};

  ns_list1.insert_many_front(6, 7, 8);

  EXPECT_EQ(8, ns_list1.size());

  auto ns_it = ns_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++ns_it) {
    EXPECT_EQ(*std_it, *ns_it);
  }
}
