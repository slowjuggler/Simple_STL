#include "unit-tests.h"

TEST(Vector_Test, test1) {
  EXPECT_ANY_THROW({
    ns::vector<int> v = ns::vector<int>();
    v.at(-2) = 1;
  });
}

TEST(Vector_Test, test1_1) {
  ns::vector<int> v{1, 2, 3};
  ns::vector<int>::iter it = v.begin();
  *it = 555;
  EXPECT_EQ(v[0], 555);
}

TEST(Vector_Test, test2) {
  EXPECT_NO_THROW({
    ns::vector<char> v = ns::vector<char>(3);
    v.at(2) = 'a';
    EXPECT_EQ(v.at(2), 'a');
  });
}

TEST(Vector_Test, construct_test1) {
  EXPECT_NO_THROW({
    ns::vector<char> v = ns::vector<char>();
    EXPECT_EQ(v.size(), 0);
  });
}

TEST(Vector_Test, construct_test2) {
  EXPECT_NO_THROW({
    ns::vector<int> v = ns::vector<int>(10);
    for (size_t i = 0; i < 10; ++i) {
      v.push_back(i + 1);
    }
    ns::vector<int> v2 = ns::vector<int>(v);
    EXPECT_EQ(v.size(), v2.size());
    EXPECT_EQ(v.capacity(), v2.capacity());
    for (size_t i = 0; i < v2.size(); ++i) {
      EXPECT_EQ(v.at(i), v2.at(i));
    }
  });
}

TEST(Vector_Test, size_test) {
  EXPECT_NO_THROW({
    ns::vector<int> v = ns::vector<int>();
    for (size_t i = 0; i < 10; ++i) {
      v.push_back(i + 1);
    }
    EXPECT_EQ(v.size(), 10);
  });
}

TEST(Vector_Test, is_empty_test1) {
  EXPECT_NO_THROW({
    ns::vector<int> v = ns::vector<int>();
    EXPECT_TRUE(v.empty());
    v.push_back(1);
    EXPECT_FALSE(v.empty());
  });
}

TEST(Vector_Test, clear_test1) {
  EXPECT_NO_THROW({
    ns::vector<int> v = ns::vector<int>();
    for (size_t i = 0; i < 10; ++i) {
      v.push_back(i + 1);
    }
    v.clear();
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 16);
    for (size_t i = 0; i < v.size(); ++i) {
      EXPECT_EQ(v.at(i), 0);
    }
  });
}

TEST(Vector_Test, top_test1) {
  EXPECT_ANY_THROW({
    ns::vector<int> v = ns::vector<int>();
    EXPECT_EQ(v.back(), 0);
    for (size_t i = 0; i < 5; ++i) {
      v.push_back(i + 1);
    }
    EXPECT_EQ(v.back(), 5);
  });
}

TEST(Vector_Test, push_back_test1) {
  EXPECT_NO_THROW({
    ns::vector<int> v = ns::vector<int>();
    for (size_t i = 0; i < 4000; ++i) {
      v.push_back(i + 1);
    }
    for (size_t i = 0; i < 4000; ++i) {
      EXPECT_EQ(v.at(i), i + 1);
    }
  });
}

TEST(Vector_Test, push_back_test2) {
  std::string str[5] = {"array", "string", "hello", "ns", "school"};
  ns::vector<std::string> v = ns::vector<std::string>();
  EXPECT_NO_THROW({
    for (int i = 0; i < 5; ++i) {
      v.push_back(str[i]);
    }
    EXPECT_EQ(v.at(0), "array");
    EXPECT_EQ(v.at(1), "string");
    EXPECT_EQ(v.at(2), "hello");
    EXPECT_EQ(v.at(3), "ns");
    EXPECT_EQ(v.at(4), "school");
  });
}

TEST(Vector_Test, push_front_test1) {
  EXPECT_NO_THROW({
    ns::vector<int> v = ns::vector<int>();
    for (size_t i = 0; i < 4000; ++i) {
      v.PushFront(i + 1);
    }
    for (size_t i = 0; i < 4000; ++i) {
      EXPECT_EQ(v.at(i), 4000 - i);
    }
  });
}

TEST(Vector_Test, push_front_test2) {
  std::string str[5] = {"array", "string", "hello", "ns", "school"};
  ns::vector<std::string> v = ns::vector<std::string>();
  EXPECT_NO_THROW({
    for (int i = 0; i < 5; ++i) {
      v.PushFront(str[i]);
      EXPECT_EQ(v.at(0), str[i]);
    }
  });
}

TEST(Vector_Test, pop_back_test1) {
  std::string str[5] = {"array", "string", "hello", "ns", "school"};
  ns::vector<std::string> v = ns::vector<std::string>();
  EXPECT_NO_THROW({
    for (int i = 0; i < 5; ++i) {
      v.PushFront(str[i]);
    }
    v.pop_back();
    EXPECT_EQ(v.capacity(), 5);
  });
}

TEST(Vector_Test, insert_test) {
  ns::vector<int> v1 = {1, 2, 3};
  std::vector<int> v2 = {1, 2, 3};
  EXPECT_NO_THROW({
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    it1 = v1.insert(it1, 1);
    it2 = v2.insert(it2, 1);
    ++it1;
    ++it2;
    it1 = v1.insert(it1, 2);
    it2 = v2.insert(it2, 2);
    ++it1;
    ++it2;
    v1.insert(it1, 3);
    v2.insert(it2, 3);
    EXPECT_EQ(v1.size(), v2.size());
    for (size_t i = 0; i < v1.size(); i++) {
      EXPECT_EQ(v1.at(i), v2.at(i));
    }
  });
}

TEST(Vector_Test, erase_test) {
  ns::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> v2 = {1, 2, 3, 4, 5};
  EXPECT_NO_THROW({
    auto it1 = v1.begin();
    auto it2 = v2.begin();
    EXPECT_EQ(v1.at(4), 5);
    EXPECT_EQ(v2.at(0), 1);
    ++it1;
    ++it2;
    v1.erase(it1);
    v2.erase(it2);
    EXPECT_EQ(v1.size(), v2.size());
    for (size_t i = 0; i < v1.size(); i++) {
      EXPECT_EQ(v1.at(i), v2.at(i));
    }
  });
}

TEST(Vector_Test, max_size_test) {
  ns::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int, ns::LinearAllocator<int>> v2 = {1, 2, 3, 4, 5};
  EXPECT_NO_THROW({ EXPECT_EQ(v1.max_size(), v2.max_size()); });
}

TEST(Vector_Test, shrink_to_fit_test) {
  ns::vector<int> v1 = {1, 2, 3, 4, 5};
  std::vector<int> v2 = {1, 2, 3, 4, 5};
  EXPECT_NO_THROW({
    v1.shrink_to_fit();
    v2.shrink_to_fit();
    EXPECT_EQ(v1.size(), v1.capacity());
    EXPECT_EQ(v1.size(), v2.size());
  });
}

TEST(Vector_Test, swap_test) {
  ns::vector<int> v1 = {1, 2, 3, 4, 5};
  ns::vector<int> v2 = v1;
  EXPECT_NO_THROW({
    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v2.capacity(), 5);
    EXPECT_EQ(v1.size(), 5);
    EXPECT_EQ(v1.capacity(), 5);
    for (size_t i = 0; i < v2.size(); ++i) {
      EXPECT_EQ(v2.at(i), i + 1);
    }
  });
}

TEST(Vector_Test, insert_many_back) {
  ns::vector<int> v = {1, 2, 3};
  EXPECT_NO_THROW({
    v.insert_many_back(4, 5, 6, 7, 8);
    for (size_t i = 0; i < v.size(); ++i) {
      EXPECT_EQ(v.at(i), i + 1);
    }
  });
}

TEST(Vector_Test, insert_many) {
  ns::vector<int> v = {1, 2, 3};
  EXPECT_NO_THROW({
    auto it = v.begin() + 1;
    v.insert_many(it, 4, 5, 6, 7, 8);
    EXPECT_EQ(v.size(), 8);
    EXPECT_EQ(v.at(0), 1);
    EXPECT_EQ(v.at(1), 4);
    EXPECT_EQ(v.at(2), 5);
    EXPECT_EQ(v.at(3), 6);
    EXPECT_EQ(v.at(4), 7);
    EXPECT_EQ(v.at(5), 8);
    EXPECT_EQ(v.at(6), 2);
    EXPECT_EQ(v.at(7), 3);
  });
}

TEST(Vector_Test, push_back_boundary_test) {
  EXPECT_NO_THROW({
    ns::vector<int> v = ns::vector<int>();
    for (size_t i = 0; i < 1000; ++i) {
      v.push_back(i + 1);
    }
    for (size_t i = 0; i < 1000; ++i) {
      EXPECT_EQ(v.at(i), i + 1);
    }
    v.push_back(1001);
    EXPECT_EQ(v.at(1000), 1001);
  });
}

TEST(Vector_Test, push_front_boundary_test) {
  EXPECT_NO_THROW({
    ns::vector<int> v = ns::vector<int>();
    for (size_t i = 0; i < 1000; ++i) {
      v.PushFront(i + 1);
    }
    for (size_t i = 0; i < 1000; ++i) {
      EXPECT_EQ(v.at(i), 1000 - i);
    }
    v.PushFront(1001);
    EXPECT_EQ(v.at(0), 1001);
  });
}

TEST(Queue_Test, test1) {
  EXPECT_ANY_THROW({
    ns::queue<int> q = ns::queue<int>();
    EXPECT_EQ(q.front(), 'a');
  });
}

TEST(Vector_Test, pop_back_exception_test) {
  ns::vector<int> v = ns::vector<int>();

  EXPECT_NO_THROW({ v.pop_back(); });
}

TEST(Queue_Test, test2) {
  EXPECT_NO_THROW({
    ns::queue<char> q = ns::queue<char>();
    q.push('a');
    q.push('b');
    EXPECT_EQ(q.front(), 'a');
  });
}

TEST(Queue_Test, construct_test1) {
  EXPECT_NO_THROW({
    ns::queue<char> q = ns::queue<char>();
    EXPECT_EQ(q.size(), 0);
  });
}

TEST(Queue_Test, construct_test2) {
  EXPECT_NO_THROW({
    ns::queue<int> q = ns::queue<int>();
    for (size_t i = 0; i < 10; ++i) {
      q.push(i + 1);
    }
    ns::queue<int> q2 = ns::queue<int>(q);
    EXPECT_EQ(q.size(), q2.size());
    //    EXPECT_EQ(q.Capacity(), q2.Capacity());
    for (size_t i = 0; i < q2.size(); ++i) {
      EXPECT_EQ(q.front(), q2.front());
      q.pop();
      q2.pop();
    }
  });
}

TEST(Queue_Test, size_test) {
  EXPECT_NO_THROW({
    ns::queue<int> q = ns::queue<int>();
    for (size_t i = 0; i < 10; ++i) {
      q.push(i + 1);
    }
    EXPECT_EQ(q.size(), 10);
    //    EXPECT_EQ(q.Capacity(), 16);
  });
}

TEST(Queue_Test, is_empty_test1) {
  EXPECT_NO_THROW({
    ns::queue<int> q = ns::queue<int>();
    EXPECT_TRUE(q.empty());
    q.push(1);
    EXPECT_FALSE(q.empty());
  });
}

TEST(Queue_Test, clear_test1) {
  EXPECT_NO_THROW({
    ns::queue<int> q = ns::queue<int>();
    for (size_t i = 0; i < 10; ++i) {
      q.push(i + 1);
    }
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.size(), 10);
    //    EXPECT_EQ(q.Capacity(), 16);
    for (size_t i = 0; i < q.size(); ++i) {
      EXPECT_EQ(q.front(), i + 1);
      q.pop();
    }
  });
}

TEST(Queue_Test, top_test1) {
  EXPECT_ANY_THROW({
    ns::queue<int> q = ns::queue<int>();
    EXPECT_EQ(q.back(), 0);
    for (size_t i = 0; i < 5; ++i) {
      q.push(i + 1);
    }
    EXPECT_EQ(q.front(), 1);
  });
}

TEST(Queue_Test, push_back_test1) {
  EXPECT_NO_THROW({
    ns::queue<int> q = ns::queue<int>();
    for (size_t i = 0; i < 4000; ++i) {
      q.push(i + 1);
    }
    for (size_t i = 0; i < 4000; ++i) {
      EXPECT_EQ(q.front(), i + 1);
      q.pop();
    }
  });
}

TEST(Queue_Test, push_back_test2) {
  std::string str[5] = {"array", "string", "hello", "ns", "school"};
  ns::queue<std::string> q = ns::queue<std::string>();
  EXPECT_NO_THROW({
    for (int i = 0; i < 5; ++i) {
      q.push(str[i]);
    }
    EXPECT_EQ(q.front(), "array");
    q.pop();
    EXPECT_EQ(q.front(), "string");
    q.pop();
    EXPECT_EQ(q.front(), "hello");
    q.pop();
    EXPECT_EQ(q.front(), "ns");
    q.pop();
    EXPECT_EQ(q.front(), "school");
    q.pop();
  });
}

TEST(Queue_Test, push_back_test3) {
  EXPECT_NO_THROW({
    ns::queue<int> q = ns::queue<int>();
    for (size_t i = 0; i < 4000; ++i) {
      q.push(i + 1);
    }
    for (size_t i = 0; i < 4000; ++i) {
      EXPECT_EQ(q.front(), i + 1);
      q.pop();
    }
  });
}

TEST(Queue_Test, initializer_test) {
  ns::queue<int> q1 = {1, 2, 3, 4, 5};
  ns::queue<int> q2 = {1, 2, 3, 4, 5};
  EXPECT_NO_THROW({
    EXPECT_EQ(q1.size(), 5);
    EXPECT_EQ(q2.empty(), false);
    for (size_t i = 0; i < q1.size(); i++) {
      EXPECT_EQ(q1.front(), i + 1);
      q1.pop();
    }
  });
}

TEST(Queue_Test, insert_many_back) {
  ns::queue<int> q = {1, 2, 3};
  EXPECT_NO_THROW({
    q.insert_many_back(4, 5, 6, 7, 8);
    EXPECT_EQ(q.size(), 8);
    EXPECT_EQ(q.front(), 1);
    q.pop();
    EXPECT_EQ(q.front(), 2);
    q.pop();
    EXPECT_EQ(q.front(), 3);
    q.pop();
    EXPECT_EQ(q.front(), 4);
    q.pop();
    EXPECT_EQ(q.front(), 5);
    q.pop();
    EXPECT_EQ(q.front(), 6);
    q.pop();
    EXPECT_EQ(q.front(), 7);
    q.pop();
    EXPECT_EQ(q.front(), 8);
    q.pop();
    EXPECT_TRUE(q.empty());
  });
}

TEST(Stack_Test, test1) {
  EXPECT_ANY_THROW({
    ns::stack<int> q = ns::stack<int>();
    EXPECT_EQ(q.top(), 0);
  });
}

TEST(Stack_Test, test2) {
  EXPECT_NO_THROW({
    ns::stack<char> s = ns::stack<char>();
    s.push('a');
    s.push('b');
    EXPECT_EQ(s.top(), 'b');
  });
}

TEST(Stack_Test, construct_test1) {
  EXPECT_NO_THROW({
    ns::stack<char> s = ns::stack<char>();
    EXPECT_EQ(s.size(), 0);
  });
}

TEST(Stack_Test, construct_test2) {
  EXPECT_NO_THROW({
    ns::stack<int> s = ns::stack<int>();
    for (size_t i = 0; i < 10; ++i) {
      s.push(i + 1);
    }
    ns::stack<int> s2 = ns::stack<int>(s);
    EXPECT_EQ(s.size(), s2.size());
    EXPECT_EQ(s.empty(), s2.empty());
    for (size_t i = 0; i < s2.size(); ++i) {
      EXPECT_EQ(s.top(), s2.top());
      s.pop();
      s2.pop();
    }
  });
}

TEST(Stack_Test, size_test) {
  EXPECT_NO_THROW({
    ns::stack<int> s = ns::stack<int>();
    for (size_t i = 0; i < 10; ++i) {
      s.push(i + 1);
    }
    EXPECT_EQ(s.size(), 10);
    EXPECT_EQ(s.empty(), false);
  });
}

TEST(Stack_Test, is_empty_test1) {
  EXPECT_NO_THROW({
    ns::stack<int> s = ns::stack<int>();
    EXPECT_TRUE(s.empty());
    s.push(1);
    EXPECT_FALSE(s.empty());
  });
}

TEST(Stack_Test, clear_test1) {
  EXPECT_NO_THROW({
    ns::stack<int> s = ns::stack<int>();
    for (size_t i = 0; i < 10; ++i) {
      s.push(i + 1);
    }
    EXPECT_FALSE(s.empty());
    for (size_t i = 0; i < s.size(); ++i) {
      EXPECT_EQ(s.top(), 10 - i);
      s.pop();
    }
  });
}

TEST(Stack_Test, top_test1) {
  EXPECT_NO_THROW({
    ns::stack<char> s = ns::stack<char>();
    //    EXPECT_EQ(s.top(), 0);
    for (char i = 'a'; i < 'f'; ++i) {
      s.push(i);
    }
    EXPECT_EQ(s.top(), 'e');
  });
}

TEST(Stack_Test, push_test2) {
  std::string str[5] = {"school", "ns", "hello", "string", "array"};
  ns::stack<std::string> s = ns::stack<std::string>();
  EXPECT_NO_THROW({
    for (int i = 0; i < 5; ++i) {
      s.push(str[i]);
    }
    EXPECT_EQ(s.top(), "array");
    s.pop();
    EXPECT_EQ(s.top(), "string");
    s.pop();
    EXPECT_EQ(s.top(), "hello");
    s.pop();
    EXPECT_EQ(s.top(), "ns");
    s.pop();
    EXPECT_EQ(s.top(), "school");
    s.pop();
  });
}

TEST(Stack_Test, swap_test1) {
  EXPECT_NO_THROW({
    ns::stack<char> s = ns::stack<char>();
    ns::stack<char> s2 = ns::stack<char>();
    for (char i = 'a'; i < 'd'; ++i) {
      s.push(i);
    }
    for (char i = 'd'; i < 'h'; ++i) {
      s2.push(i);
    }
    s.swap(s2);
    EXPECT_EQ(s.top(), 'g');
    EXPECT_EQ(s2.top(), 'c');
  });
}

TEST(Stack_Test, big_push_test3) {
  EXPECT_NO_THROW({
    ns::stack<int> s = ns::stack<int>();
    for (size_t i = 0; i < 4000; ++i) {
      s.push(i + 1);
    }
    for (size_t i = 0; i < 4000; ++i) {
      EXPECT_EQ(s.top(), 4000 - i);
      s.pop();
    }
  });
}

TEST(Stack_Test, list_and_iterators_test) {
  ns::stack<int> s = {0, 1, 2, 3};
  EXPECT_NO_THROW({
    for (size_t i = 0; i < 4; ++i) {
      EXPECT_EQ(s.top(), 3 - i);
      s.pop();
    }
  });
}

TEST(Stack_Test, insert_many_front) {
  ns::stack<int> s = {1, 2, 3};
  EXPECT_NO_THROW({
    s.insert_many_front(4, 5, 6, 7, 8);
    EXPECT_EQ(s.size(), 8);
    EXPECT_EQ(s.top(), 8);
    s.pop();
    EXPECT_EQ(s.top(), 7);
    s.pop();
    EXPECT_EQ(s.top(), 6);
    s.pop();
    EXPECT_EQ(s.top(), 5);
    s.pop();
    EXPECT_EQ(s.top(), 4);
    s.pop();
    EXPECT_EQ(s.top(), 3);
    s.pop();
    EXPECT_EQ(s.top(), 2);
    s.pop();
    EXPECT_EQ(s.top(), 1);
    s.pop();
    EXPECT_TRUE(s.empty());
  });
}

TEST(List_Test_Bad_Init, construct_test1) {
  EXPECT_NO_THROW({
    ns::list<char> l = ns::list<char>(1, 'x');
    EXPECT_EQ(l.size(), 1);
  });
}

TEST(List_Test, construct_test1) {
  EXPECT_NO_THROW({
    ns::list<std::string> l = ns::list<std::string>(8, "list");
    EXPECT_EQ(l.size(), 8);
  });
}

TEST(List_Test, construct_test2) {
  EXPECT_NO_THROW({
    ns::list<std::string> l1 = ns::list<std::string>(8, "list");
    ns::list<std::string> l2 = ns::list<std::string>(1, "glist");
    l2 = l1;
    EXPECT_EQ(l2.size(), 8);
    EXPECT_EQ(l2.back(), "list");
  });
}

TEST(List_Test, construct_test3) {
  EXPECT_NO_THROW({
    ns::list<std::string> l1 = ns::list<std::string>(8, "list");
    ns::list<std::string> l2(l1);
    EXPECT_EQ(l2.size(), 8);
    EXPECT_EQ(l2.back(), "list");
  });
}

TEST(List_Test, list_and_iterators_test) {
  ns::list<int> l = {1, 2, 3, 4, 5};
  //  EXPECT_NO_THROW({
  EXPECT_EQ(l.size(), 5);
  ns::BDIter<int, ns::ListNode<int>> first = l.begin();
  ns::BDIter<int, ns::ListNode<int>> last = l.end();
  for (int i = 1; first != last; ++first) EXPECT_EQ(i++, *first);
  //  });
}

TEST(List_Test, insert_test) {
  ns::list<int> l = {1, 3, 4, 5, 6, 7};
  EXPECT_NO_THROW({
    EXPECT_EQ(l.size(), 6);
    l.insert(l.begin(), 555);
    EXPECT_EQ(l.size(), 7);
    EXPECT_EQ(l.front(), 555);
  });
}

TEST(List_Test, erase_test) {
  ns::list<int> l = {1, 3, 4, 5, 6, 7};
  EXPECT_NO_THROW({
    auto it = l.begin();
    ++it;
    l.erase(it);
    EXPECT_EQ(l.size(), 5);
    EXPECT_EQ(l.begin()->next->value, 4);
  });
}

TEST(List_Test, push_back_test) {
  ns::list<int> l = {1, 3, 4, 5, 6, 7};
  EXPECT_NO_THROW({
    l.push_back(555);
    //  l.print();
    EXPECT_EQ(l.size(), 7);
    EXPECT_EQ(l.back(), 555);
    //  EXPECT_EQ(l.end()->data, 6);
  });
}

TEST(List_Test, pop_back_test) {
  ns::list<int> l = {1, 3, 4, 5, 6, 7};
  EXPECT_NO_THROW({
    l.pop_back();
    //  l.print();
    EXPECT_EQ(l.size(), 5);
    EXPECT_EQ(l.end()->prev->value, 6);
    //  EXPECT_EQ(l.end()->data, 6);
  });
}

TEST(List_Test, push_front_test) {
  ns::list<int> l = {1, 3, 4, 5, 6, 7};
  EXPECT_NO_THROW({
    l.push_front(555);
    //  l.print();
    EXPECT_EQ(l.size(), 7);
    EXPECT_EQ(l.begin()->value, 555);
    //  EXPECT_EQ(l.end()->data, 6);
  });
}

TEST(List_Test, pop_front_test) {
  ns::list<int> l = {1, 3, 4, 5, 6, 7};
  EXPECT_NO_THROW({
    l.pop_front();
    //  l.print();
    EXPECT_EQ(l.size(), 5);
    EXPECT_EQ(l.begin()->value, 3);
    //  EXPECT_EQ(l.end()->data, 6);
  });
}

TEST(List_Test, swap_test) {
  ns::list<int> l1 = {1, 3, 4, 5, 6, 7};
  ns::list<int> l2 = {8, 9, 10, 11, 12, 13, 14};
  EXPECT_NO_THROW({
    l1.swap(l2);
    //  l1.print();
    EXPECT_EQ(l1.size(), 7);
    EXPECT_EQ(l1.front(), 8);
    EXPECT_EQ(l1.back(), 14);
  });
}

TEST(List_Test, reverse_test) {
  ns::list<int> l = {1, 3, 4, 5, 6, 7};
  EXPECT_NO_THROW({
    l.reverse();
    EXPECT_EQ(l.front(), 7);
    EXPECT_EQ(l.back(), 1);
  });
}

TEST(List_Test, reverse_test2) {
  ns::list<std::string> l = {"school", "ns", "hello", "string", "array"};
  EXPECT_NO_THROW({
    l.reverse();
    EXPECT_EQ(l.front(), "array");
    EXPECT_EQ(l.back(), "school");
  });
}

TEST(List_Test, unique_test) {
  ns::list<int> l = {9, 9, 1, 1, 1, 5, 6, 7, 7};
  std::list<int> std_l = {9, 9, 1, 1, 1, 5, 6, 7, 7};
  EXPECT_NO_THROW({
    EXPECT_EQ(l.size(), 9);
    l.unique();
    std_l.unique();
    EXPECT_EQ(l.size(), std_l.size());
    EXPECT_EQ(l.front(), 9);
    EXPECT_EQ(l.back(), 7);
  });
}

TEST(List_Test, insert_many_front) {
  ns::list<int> l = {1, 2, 3};
  EXPECT_NO_THROW({
    l.insert_many_front(4, 5, 6, 7, 8);
    EXPECT_EQ(l.size(), 8);
    EXPECT_EQ(l.front(), 4);
    EXPECT_EQ(l.back(), 3);
  });
}

TEST(List_Test, is_less_test) {
  ns::list<std::string> l1 = {"school", "ns", "hello", "string"};
  ns::list<std::string> l2 = {"school", "ns", "hello", "string", "array"};
  EXPECT_NO_THROW({
    bool answer = l1 < l2;
    EXPECT_EQ(answer, true);
  });
}

TEST(List_Test, push_test2) {
  ns::list<std::string> l = ns::list<std::string>(42, "arr");
  EXPECT_NO_THROW({
    EXPECT_EQ(l.size(), 42);
    EXPECT_EQ(l.front(), "arr");
  });
}

TEST(List_Test, char_print_test) {
  ns::list<std::string> l = ns::list<std::string>(42, "arr");
  std::list<std::string> std_l = std::list<std::string>(42, "arr");
  EXPECT_NO_THROW({
    EXPECT_EQ(l.size(), std_l.size());
    EXPECT_EQ(l.front(), std_l.front());
  });
}

TEST(List_Test, bool_print_test) {
  ns::list<std::string> l1 = ns::list<std::string>(1, "arabesca");
  ns::list<std::string> l2 = ns::list<std::string>(1, "arar");
  EXPECT_NO_THROW({
    bool answer = l1.front() < l2.front();
    EXPECT_EQ(answer, true);
  });
}

TEST(List_Test, is_less_test3) {
  ns::list<int> l1 = {1, 3, 4, 5, 6, 555};
  ns::list<int> l2 = {8, 9, 10, 11, 12, 13, 14};
  EXPECT_NO_THROW({
    bool answer = l1.back() < l2.back();
    EXPECT_EQ(answer, false);
  });
}

TEST(List_Test, splice_test1) {
  ns::list<int> l1 = {1, 2, 3, 4, 5};
  ns::list<int> l2 = {10, 20, 30, 40, 50};
  EXPECT_NO_THROW({
    ns::BDIter it = l1.begin();
    ++it;
    ++it;
    l1.splice(it, l2);
    //  l1.print();
    EXPECT_EQ(l1.size(), 10);
    EXPECT_EQ(l1.back(), 5);
  });
}

TEST(List_Test, merge_test1) {
  ns::list<int> l1 = {2, 3, 3, 5, 9};
  ns::list<int> l2 = {1, 3, 4, 4, 7, 8};
  EXPECT_NO_THROW({
    l1.merge(l2);
    //    l1.print();
    EXPECT_EQ(l1.size(), 11);
    EXPECT_EQ(l2.size(), 0);
    EXPECT_EQ(l1.back(), 9);
    EXPECT_EQ(l1.front(), 1);
  });
}

TEST(List_Test, merge_test2) {
  ns::list<int> l1 = {1, 9, 11, 25};
  ns::list<int> l2 = {2, 4, 8, 10};
  EXPECT_NO_THROW({
    l1.merge(l2);
    //    l1.print();
    EXPECT_EQ(l1.size(), 8);
    EXPECT_EQ(l2.size(), 0);
    EXPECT_EQ(l1.back(), 25);
    EXPECT_EQ(l1.front(), 1);
  });
}

TEST(List_Test, merge_test3) {
  ns::list<int> l1 = {2};
  ns::list<int> l2 = {1};
  EXPECT_NO_THROW({
    l1.merge(l2);
    //    l1.print();
    EXPECT_EQ(l1.size(), 2);
    EXPECT_EQ(l2.size(), 0);
    EXPECT_EQ(l1.back(), 2);
    EXPECT_EQ(l1.front(), 1);
  });
}

TEST(List_Test, merge_test4) {
  ns::list<std::string> l1 = {"aaa", "aab", "abb", "bbb"};
  ns::list<std::string> l2 = {"aaa", "bbb", "ccc", "ddd", "eee"};
  EXPECT_NO_THROW({
    l1.merge(l2);
    //    l1.print();
    EXPECT_EQ(l1.size(), 9);
    EXPECT_EQ(l2.size(), 0);
    EXPECT_EQ(l1.back(), "eee");
    EXPECT_EQ(l1.front(), "aaa");
  });
}

TEST(List_Test, sort_test1) {
  ns::list<int> l = {7,  1,  8,   4,  9, 11, 25,    12,  11,  54, 23,
                      55, 11, -12, 34, 0, 2,  -1000, 200, 500, 555};
  EXPECT_NO_THROW({
    l.sort();
    EXPECT_EQ(l.size(), 21);
    EXPECT_EQ(l.back(), 555);
    EXPECT_EQ(l.front(), -1000);
    //    l.print();
  });
}

TEST(List_Test, sort_test2) {
  ns::list<std::string> l = {"aaa", "aab", "abb", "bbb", "aaa",
                              "bbb", "ccc", "ddd", "eee"};
  EXPECT_NO_THROW({
    l.sort();
    //    l.print();
    EXPECT_EQ(l.size(), 9);
    EXPECT_EQ(l.back(), "eee");
    EXPECT_EQ(l.front(), "aaa");
  });
}

TEST(MapTest2, DefaultConstructor) {
  ns::map<int, std::string> m;
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(0, m.size());
}

TEST(MapTest2, InitializerListConstructor) {
  ns::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(3, m.size());
  EXPECT_EQ("one", m.at(1));
  EXPECT_EQ("two", m.at(2));
  EXPECT_EQ("three", m.at(3));
}

TEST(MapTest2, Merge) {
  ns::map<int, std::string> m1 = {{1, "one"}, {2, "two"}};
  ns::map<int, std::string> m2 = {{3, "three"}, {4, "four"}};

  m1.merge(m2);

  EXPECT_EQ(4, m1.size());
  EXPECT_TRUE(m2.empty());
  EXPECT_EQ("three", m1[3]);
  EXPECT_EQ("four", m1[4]);
}

TEST(MapTest2, BoundaryValueTests) {
  // Test large data set and max_size()
  ns::map<int, std::string> m;
  const int dataSize = 100000;
  for (int i = 1; i <= dataSize; ++i) {
    m.insert({i, "value" + std::to_string(i)});
  }
  EXPECT_EQ(dataSize, m.size());
  // EXPECT_EQ(dataSize, m.max_size()); // Why?

  // Test empty() on non-empty map
  EXPECT_FALSE(m.empty());

  // Test at() on invalid key
  EXPECT_THROW(m.at(0), std::out_of_range);
  EXPECT_THROW(m.at(dataSize + 1), std::out_of_range);

  // Test contains() on valid and invalid keys
  for (int i = 1; i <= dataSize; ++i) {
    EXPECT_TRUE(m.contains(i));
  }
  EXPECT_FALSE(m.contains(0));
  EXPECT_FALSE(m.contains(dataSize + 1));
}

TEST(MapTest2, MoveConstructor) {
  ns::map<int, std::string> m1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  ns::map<int, std::string> m2 = std::move(m1);

  EXPECT_EQ(3, m2.size());
  EXPECT_TRUE(m1.empty());
}

TEST(MapTest2, MoveAssignment) {
  ns::map<int, std::string> m1 = {{1, "one"}, {2, "two"}, {3, "three"}};
  ns::map<int, std::string> m2;
  m2 = std::move(m1);

  EXPECT_EQ(3, m2.size());
  EXPECT_TRUE(m1.empty());
}

TEST(map_test, basic_constr) {
  ns::map<int, char> map_d;
  ns::map<double, char> map_i;
  ns::map<char, std::string> map_c;
  EXPECT_EQ(map_d.size(), 0);
  EXPECT_EQ(map_i.size(), 0);
  EXPECT_EQ(map_c.size(), 0);
}

TEST(map_test, constr_with) {
  ns::map<double, char> map_1{{1.1, 'a'}};
  std::map<double, char> orignal_map_1{{1.1, 'a'}};
  EXPECT_EQ(map_1.size(), 1);
  map_1.insert_or_assign(2.2, 'b');
  map_1.insert_or_assign(3.3, 'c');
  map_1.insert_or_assign(4.4, 'd');
  map_1.insert_or_assign(6.6, 'e');
  EXPECT_EQ(map_1.size(), 5);
  map_1.clear();
  EXPECT_EQ(map_1.size(), 0);
  EXPECT_EQ(orignal_map_1.size(), 1);
}

TEST(map_test, constr_with_indefinite_number_of_elements) {
  ns::map<double, char> map_1({{1.1, 'a'},
                                {2.2, 'b'},
                                {3.3, 'c'},
                                {4.4, 'd'},
                                {5.5, 'e'},
                                {3.3, 'c'},
                                {4.4, 'd'},
                                {5.5, 'e'}});
  std::map<double, char> orignal_map_1({{1.1, 'a'},
                                        {2.2, 'b'},
                                        {3.3, 'c'},
                                        {4.4, 'd'},
                                        {5.5, 'e'},
                                        {3.3, 'c'},
                                        {4.4, 'd'},
                                        {5.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);
  auto it = map_1.begin();
  EXPECT_EQ((*it).first, 1.1);
  EXPECT_EQ((*it).second, 'a');
  ++it;
  EXPECT_EQ((*it).first, 2.2);
  EXPECT_EQ((*it).second, 'b');
  ++it;
  EXPECT_EQ((*it).first, 3.3);
  EXPECT_EQ((*it).second, 'c');
  ++it;
  EXPECT_EQ((*it).first, 4.4);
  EXPECT_EQ((*it).second, 'd');
  ++it;
  EXPECT_EQ((*it).first, 5.5);
  EXPECT_EQ((*it).second, 'e');

  it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
  EXPECT_EQ(map_1.IsBalanced(), true);
}

TEST(map_test, constr_with_indefinite_number_of_elements_string) {
  ns::map<double, std::string> map_1(
      {{5, "apple"},  {3, "banana"},      {10, "orange"},  {2, "grape"},
       {7, "dog"},    {1, "cat"},         {8, "elephant"}, {4, "giraffe"},
       {2, "zebra"},  {6, "lion"},        {3, "cherry"},   {9, "peach"},
       {4, "pear"},   {11, "watermelon"}, {1, "turtle"},   {12, "frog"},
       {6, "spider"}, {15, "snake"},      {13, "koala"},   {16, "monkey"}});
  std::map<double, std::string> orignal_map_1(
      {{5, "apple"},  {3, "banana"},      {10, "orange"},  {2, "grape"},
       {7, "dog"},    {1, "cat"},         {8, "elephant"}, {4, "giraffe"},
       {2, "zebra"},  {6, "lion"},        {3, "cherry"},   {9, "peach"},
       {4, "pear"},   {11, "watermelon"}, {1, "turtle"},   {12, "frog"},
       {6, "spider"}, {15, "snake"},      {13, "koala"},   {16, "monkey"}});
  EXPECT_EQ(map_1.size(), 15);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());
  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
  EXPECT_EQ(map_1.IsBalanced(), true);
}

TEST(map_test, copy_constr) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);
  ns::map<double, char> map_2(map_1);

  EXPECT_EQ(map_1.size(), 5);
  EXPECT_EQ(map_2.size(), 5);

  auto it = map_1.begin();
  auto it_2 = map_2.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, copy_operator_01) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);
  ns::map<double, char> map_2(
      {{1.5, 's'}, {2.9, 'a'}, {3.5, 'c'}, {0.4, 'o'}, {0.5, 'e'}});
  EXPECT_EQ(map_2.size(), 5);

  map_1 = map_2;
  EXPECT_EQ(map_1.size(), 5);
  EXPECT_EQ(map_2.size(), 5);
  auto it = map_1.begin();
  auto it_2 = map_2.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, copy_operator_06) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {1.1, 'a'}, {2.2, 'b'}});
  ns::map<double, char> map_2;

  EXPECT_EQ(map_1.size(), 2);

  map_1 = map_2;
  EXPECT_EQ(map_1.size(), 0);
  EXPECT_EQ(map_2.size(), 0);
}

TEST(map_test, copy_operator_05) {
  ns::map<double, char> map_1;
  ns::map<double, char> map_2;

  EXPECT_EQ(map_1.size(), 0);

  map_1 = map_2;
  EXPECT_EQ(map_1.size(), 0);
  EXPECT_EQ(map_2.size(), 0);
}

TEST(map_test, copy_operator_03) {
  ns::map<double, char> map_1({{1.1, 'a'}, {2.2, 'b'}});
  ns::map<double, char> map_2({{11, 'a'}, {22, 'b'}, {33, 'b'}});

  EXPECT_EQ(map_1.size(), 2);
  EXPECT_EQ(map_2.size(), 3);

  map_1 = map_2;
  EXPECT_EQ(map_1.size(), 3);
  EXPECT_EQ(map_2.size(), 3);

  auto it = map_1.begin();
  EXPECT_EQ((*it).first, 11);
  EXPECT_EQ((*it).second, 'a');
  ++it;
  EXPECT_EQ((*it).first, 22);
  EXPECT_EQ((*it).second, 'b');
  ++it;
  EXPECT_EQ((*it).first, 33);
  EXPECT_EQ((*it).second, 'b');
  it = map_1.begin();
  auto it_2 = map_2.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_EQ(*it, *it_2);
    ++it_2;
  }
}

TEST(map_test, copy_operator_04) {
  ns::map<double, char> map_1({{1.1, 'a'}, {2.2, 'b'}});

  EXPECT_EQ(map_1.size(), 2);

  map_1 = map_1;
  EXPECT_EQ(map_1.size(), 2);
}

TEST(map_test, move_constr) {
  ns::map<double, char> map_1(
      {{1.5, 's'}, {2.9, 'a'}, {3.5, 'c'}, {0.4, 'o'}, {0.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);
  ns::map<double, char> map_2(map_1);

  EXPECT_EQ(map_1.size(), 5);
  EXPECT_EQ(map_2.size(), 5);

  std::map<double, char> orignal_list_1(
      {{1.5, 's'}, {2.9, 'a'}, {3.5, 'c'}, {0.4, 'o'}, {0.5, 'e'}});

  auto it = map_2.begin();
  EXPECT_DOUBLE_EQ((*it).first, 0.4);
  EXPECT_EQ((*it).second, 'o');
  ++it;
  EXPECT_DOUBLE_EQ((*it).first, 0.5);
  EXPECT_EQ((*it).second, 'e');
  ++it;
  EXPECT_DOUBLE_EQ((*it).first, 1.5);
  EXPECT_EQ((*it).second, 's');
  ++it;
  EXPECT_DOUBLE_EQ((*it).first, 2.9);
  EXPECT_EQ((*it).second, 'a');
  ++it;
  EXPECT_DOUBLE_EQ((*it).first, 3.5);
  EXPECT_EQ((*it).second, 'c');

  it = map_2.begin();
  auto it_2 = orignal_list_1.begin();
  for (; it != map_2.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, move_operator) {
  ns::map<double, char> map_1({{1.1, 'a'}, {2.2, 'b'}});
  EXPECT_EQ(map_1.size(), 2);
  ns::map<double, char> map_2({{11, 'a'}, {22, 'b'}, {33, 'b'}});
  EXPECT_EQ(map_2.size(), 3);

  map_1 = std::move(map_2);

  EXPECT_EQ(map_1.size(), 3);
  EXPECT_EQ(map_2.size(), 0);

  auto it = map_1.begin();
  EXPECT_EQ((*it).first, 11);
  EXPECT_EQ((*it).second, 'a');
  ++it;
  EXPECT_EQ((*it).first, 22);
  EXPECT_EQ((*it).second, 'b');
  ++it;
  EXPECT_EQ((*it).first, 33);
  EXPECT_EQ((*it).second, 'b');
}

TEST(map_test, test_size) {
  ns::map<double, char> map_1(
      {{1.5, 's'}, {2.9, 'a'}, {3.5, 'c'}, {0.4, 'o'}, {0.5, 'e'}});
  std::map<double, char> orignal_map_1(
      {{1.5, 's'}, {2.9, 'a'}, {3.5, 'c'}, {0.4, 'o'}, {0.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());
}

TEST(map_test, test_max_size) {
  ns::map<double, char> map_1;
  std::map<double, char> orignal_map_1;
  EXPECT_EQ(map_1.max_size() >> 1, orignal_map_1.max_size());
}

TEST(map_test, test_merge) {
  ns::map<int, char> map_1({{1, 'a'}, {3, 'b'}, {5, 'b'}});
  ns::map<int, char> map_2({{2, 'l'}, {4, 'o'}, {6, 'b'}, {8, 's'}});

  EXPECT_EQ(map_1.size(), 3);
  EXPECT_EQ(map_2.size(), 4);

  std::map<int, char> orignal_map_1(
      {{1, 'a'}, {3, 'b'}, {5, 'b'}, {2, 'l'}, {4, 'o'}, {6, 'b'}, {8, 's'}});

  map_1.merge(map_2);

  EXPECT_EQ(map_1.size(), 7);
  EXPECT_EQ(map_2.size(), 0);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_merge_02) {
  ns::map<int, char> map_1({{2, 'l'}, {4, 'o'}, {6, 'b'}, {8, 's'}});
  ns::map<int, char> map_2({{1, 'a'}, {3, 'b'}, {5, 'b'}});

  EXPECT_EQ(map_1.size(), 4);
  EXPECT_EQ(map_2.size(), 3);

  std::map<int, char> orignal_map_1(
      {{1, 'a'}, {3, 'b'}, {5, 'b'}, {2, 'l'}, {4, 'o'}, {6, 'b'}, {8, 's'}});

  map_1.merge(map_2);

  EXPECT_EQ(map_1.size(), 7);
  EXPECT_EQ(map_2.size(), 0);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_merge_03) {
  ns::map<int, char> map_1;
  ns::map<int, char> map_2({{1, 'a'}, {3, 'b'}, {5, 'b'}});

  EXPECT_EQ(map_1.size(), 0);
  EXPECT_EQ(map_2.size(), 3);

  std::map<int, char> orignal_map_1({{1, 'a'}, {3, 'b'}, {5, 'b'}});

  map_1.merge(map_2);

  EXPECT_EQ(map_1.size(), 3);
  EXPECT_EQ(map_2.size(), 0);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, move_operator_05) {
  ns::map<double, char> map_1({{1.1, 'a'}, {2.2, 'b'}});
  EXPECT_EQ(map_1.size(), 2);
  ns::map<double, char> map_2({{11, 'a'}, {22, 'b'}, {33, 'b'}});
  EXPECT_EQ(map_2.size(), 3);

  std::map<double, char> original_map_1({{1.1, 'a'}, {2.2, 'b'}});
  EXPECT_EQ(map_1.size(), 2);
  std::map<double, char> original_map_2({{11, 'a'}, {22, 'b'}, {33, 'b'}});
  map_2 = std::move(map_1);
  original_map_2 = std::move(original_map_1);

  EXPECT_EQ(map_1.size(), 0);
  EXPECT_EQ(map_2.size(), 2);
  EXPECT_EQ(map_1.size(), original_map_1.size());
  EXPECT_EQ(map_2.size(), original_map_2.size());

  auto it = map_2.begin();
  EXPECT_EQ((*it).first, 1.1);
  EXPECT_EQ((*it).second, 'a');
  ++it;
  EXPECT_EQ((*it).first, 2.2);
  EXPECT_EQ((*it).second, 'b');
  it = map_2.begin();
  auto it_2 = original_map_2.begin();
  for (; it != map_2.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, move_operator_to_yourself) {
  ns::map<double, char> map_1({{1.1, 'a'}, {2.2, 'b'}});
  EXPECT_EQ(map_1.size(), 2);
  map_1 = std::move(map_1);
  EXPECT_EQ(map_1.size(), 2);
}

TEST(map_test, move_operator_03) {
  ns::map<double, char> map_1;
  EXPECT_EQ(map_1.size(), 0);
  ns::map<double, char> map_2;
  EXPECT_EQ(map_2.size(), 0);

  map_2 = std::move(map_1);

  EXPECT_EQ(map_1.size(), 0);
  EXPECT_EQ(map_2.size(), 0);
}

TEST(map_test, move_operator_04) {
  ns::map<double, char> map_1({{1.1, 'a'}, {2.2, 'b'}});
  EXPECT_EQ(map_1.size(), 2);
  ns::map<double, char> map_2;
  EXPECT_EQ(map_2.size(), 0);

  map_1 = std::move(map_2);

  EXPECT_EQ(map_1.size(), 0);
  EXPECT_EQ(map_2.size(), 0);
}

TEST(map_test, test_empty) {
  ns::map<int, char> map_1({{2, 'l'}, {4, 'o'}, {6, 'b'}, {8, 's'}});
  ns::map<int, char> map_2;

  EXPECT_EQ(map_1.empty(), false);
  EXPECT_EQ(map_2.empty(), true);
}

TEST(map_test, test_insert) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  std::map<double, char> orignal_map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);

  auto res_test_1 = map_1.insert({3.2, 'b'});
  EXPECT_EQ(res_test_1.second, true);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first, 3.2);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().second, 'b');

  auto res_orignal_set_1 = orignal_map_1.insert({3.2, 'b'});
  EXPECT_EQ(res_test_1.second, res_orignal_set_1.second);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first,
                   res_orignal_set_1.first.operator*().first);
  EXPECT_EQ(res_test_1.first.operator*().second,
            res_orignal_set_1.first.operator*().second);

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_insert_03) {
  ns::map<double, char> map_1;
  std::map<double, char> orignal_map_1;
  EXPECT_EQ(map_1.size(), 0);

  auto res_test_1 = map_1.insert({3.2, 'b'});
  EXPECT_EQ(res_test_1.second, true);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first, 3.2);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().second, 'b');

  auto res_orignal_set_1 = orignal_map_1.insert({3.2, 'b'});
  EXPECT_EQ(res_test_1.second, res_orignal_set_1.second);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first,
                   res_orignal_set_1.first.operator*().first);
  EXPECT_EQ(res_test_1.first.operator*().second,
            res_orignal_set_1.first.operator*().second);

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_insert_04) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  std::map<double, char> orignal_map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);

  auto res_test_1 = map_1.insert(3.2, 'b');
  EXPECT_EQ(res_test_1.second, true);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first, 3.2);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().second, 'b');

  auto res_orignal_set_1 = orignal_map_1.insert({3.2, 'b'});
  EXPECT_EQ(res_test_1.second, res_orignal_set_1.second);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first,
                   res_orignal_set_1.first.operator*().first);
  EXPECT_EQ(res_test_1.first.operator*().second,
            res_orignal_set_1.first.operator*().second);

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_insert_02) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  std::map<double, char> orignal_map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);

  auto res_test_1 = map_1.insert({3.3, 'b'});
  EXPECT_EQ(res_test_1.second, false);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first, 3.3);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().second, 'c');
  //  map_1.print();

  auto res_orignal_set_1 = orignal_map_1.insert({3.3, 'b'});
  EXPECT_EQ(res_test_1.second, res_orignal_set_1.second);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first,
                   res_orignal_set_1.first.operator*().first);
  EXPECT_EQ(res_test_1.first.operator*().second,
            res_orignal_set_1.first.operator*().second);

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_insert_06) {
  ns::map<double, char> map_1;
  std::map<double, char> orignal_map_1;
  EXPECT_EQ(map_1.size(), 0);

  auto res_test_1 = map_1.insert(3.2, 'b');
  EXPECT_EQ(res_test_1.second, true);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first, 3.2);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().second, 'b');

  auto res_orignal_set_1 = orignal_map_1.insert({3.2, 'b'});
  EXPECT_EQ(res_test_1.second, res_orignal_set_1.second);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first,
                   res_orignal_set_1.first.operator*().first);
  EXPECT_EQ(res_test_1.first.operator*().second,
            res_orignal_set_1.first.operator*().second);

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_insert_or_assign) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  std::map<double, char> orignal_map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'b'}, {4.4, 'd'}, {5.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);

  auto res_test_1 = map_1.insert_or_assign(3.3, 'b');
  EXPECT_EQ(res_test_1.second, false);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first, 3.3);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().second, 'b');

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_insert_or_assign_02) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  std::map<double, char> orignal_map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);

  auto res_test_1 = map_1.insert_or_assign(3.4, 'b');
  EXPECT_EQ(res_test_1.second, true);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first, 3.4);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().second, 'b');

  auto res_orignal_set_1 = orignal_map_1.insert({3.4, 'b'});
  EXPECT_EQ(res_test_1.second, res_orignal_set_1.second);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first,
                   res_orignal_set_1.first.operator*().first);
  EXPECT_EQ(res_test_1.first.operator*().second,
            res_orignal_set_1.first.operator*().second);

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_insert_or_assign_03) {
  ns::map<double, char> map_1;
  std::map<double, char> orignal_map_1;
  EXPECT_EQ(map_1.size(), 0);

  auto res_test_1 = map_1.insert_or_assign(3.4, 'b');
  EXPECT_EQ(res_test_1.second, true);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first, 3.4);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().second, 'b');

  auto res_orignal_set_1 = orignal_map_1.insert({3.4, 'b'});
  EXPECT_EQ(res_test_1.second, res_orignal_set_1.second);
  EXPECT_DOUBLE_EQ(res_test_1.first.operator*().first,
                   res_orignal_set_1.first.operator*().first);
  EXPECT_EQ(res_test_1.first.operator*().second,
            res_orignal_set_1.first.operator*().second);

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_operator_sq) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  std::map<double, char> orignal_map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);

  EXPECT_EQ(map_1[4.4], 'd');
  EXPECT_EQ(orignal_map_1[4.4], map_1[4.4]);

  map_1[4.4] = 'a';
  orignal_map_1[4.4] = 'a';

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_operator_sq_02) {
  ns::map<double, char> map_1;
  std::map<double, char> orignal_map_1;
  EXPECT_EQ(map_1.size(), 0);

  EXPECT_EQ(orignal_map_1[4.4], map_1[4.4]);

  map_1[4.4] = 'a';
  orignal_map_1[4.4] = 'a';

  EXPECT_EQ(map_1[4.4], 'a');
  EXPECT_EQ(orignal_map_1[4.4], map_1[4.4]);

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_contains) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  ns::map<double, char> map_2;
  EXPECT_EQ(map_1.size(), 5);

  auto res_test_1 = map_1.contains(3.3);
  EXPECT_EQ(res_test_1, true);
  res_test_1 = map_1.contains(3.2);
  EXPECT_EQ(res_test_1, false);

  auto res_test_2 = map_2.contains(3.3);
  EXPECT_EQ(res_test_2, false);
}

TEST(map_test, test_clear_full) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  std::map<double, char> orignal_map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);
  EXPECT_EQ(map_1.IsBalanced(), true);
  map_1.clear();
  orignal_map_1.clear();
  EXPECT_EQ(map_1.size(), 0);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
  EXPECT_EQ(map_1.IsBalanced(), true);
}

TEST(map_test, test_clear_empty) {
  ns::map<double, char> map_1;
  std::map<double, char> orignal_map_1;
  EXPECT_EQ(map_1.size(), 0);

  map_1.clear();
  orignal_map_1.clear();
  EXPECT_EQ(map_1.size(), 0);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
  EXPECT_EQ(map_1.IsBalanced(), true);
}

TEST(map_test, test_erase) {
  ns::map<int, char> map_1;
  std::map<int, char> orignal_map_1;

  for (int i = 1; i < 21; i++) {
    map_1.insert({i, 'a'});
    orignal_map_1.insert({i, 'a'});
  }
  EXPECT_EQ(map_1.size(), 20);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  auto it = map_1.insert({25, 'b'}).first;
  auto it_2 = orignal_map_1.insert({25, 'b'}).first;
  EXPECT_EQ(map_1.size(), 21);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  map_1.erase(it);
  orignal_map_1.erase(it_2);
  EXPECT_EQ(map_1.size(), 20);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  it = map_1.begin();
  it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
  EXPECT_EQ(map_1.IsBalanced(), true);
}

TEST(map_test, test_erase_03) {
  ns::map<int, char> map_1;
  std::map<int, char> orignal_map_1;

  EXPECT_EQ(map_1.size(), 0);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  auto it = map_1.begin();

  map_1.erase(it);
  EXPECT_EQ(map_1.size(), 0);

  EXPECT_EQ(map_1.IsBalanced(), true);
}

TEST(map_test, test_iter_end) {
  ns::map<double, char> map_1({{1.1, 'a'},
                                {2.2, 'b'},
                                {3.3, 'c'},
                                {4.4, 'd'},
                                {5.5, 'e'},
                                {3.3, 'c'},
                                {4.4, 'd'},
                                {5.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);
  std::map<double, char> orignal_map_1({{1.1, 'a'},
                                        {2.2, 'b'},
                                        {3.3, 'c'},
                                        {4.4, 'd'},
                                        {5.5, 'e'},
                                        {3.3, 'c'},
                                        {4.4, 'd'},
                                        {5.5, 'e'}});

  ns::map<double, char>::iter it = map_1.end();
  std::map<double, char>::iterator it_2 = orignal_map_1.end();
  --it;
  --it_2;
  EXPECT_DOUBLE_EQ((*it).first, 4.4);
  EXPECT_EQ((*it).second, 'd');
  map_1.erase(it);
  EXPECT_EQ(map_1.size(), 4);
  //  map_1.print();
  EXPECT_EQ(map_1.IsBalanced(), true);
}

TEST(map_test, test_erase_01) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  std::map<double, char> orignal_map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});

  EXPECT_EQ(map_1.size(), 5);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  auto it = map_1.begin();
  ++it;
  ++it;
  auto it_2 = orignal_map_1.begin();
  ++it_2;
  ++it_2;
  EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
  EXPECT_EQ((*it).second, (*it_2).second);
  map_1.erase(it);
  orignal_map_1.erase(it_2);
  EXPECT_EQ(map_1.size(), 4);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  it = map_1.begin();
  it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
  EXPECT_EQ(map_1.IsBalanced(), true);
}

TEST(map_test, test_at) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  EXPECT_EQ(map_1.size(), 5);
  EXPECT_EQ(map_1.at(3.3), 'c');
  EXPECT_EQ(map_1.IsBalanced(), true);
}

TEST(map_test, test_at_2) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  EXPECT_ANY_THROW({
    EXPECT_EQ(map_1.size(), 5);
    EXPECT_EQ(map_1.at(7.7), 0);
  });
}

TEST(map_test, test_at_3) {
  ns::map<double, char> map_1(
      {{1.1, 'a'}, {2.2, 'b'}, {3.3, 'c'}, {4.4, 'd'}, {5.5, 'e'}});
  ns::map<double, char> map_2;
  EXPECT_EQ(map_1.size(), 5);
  auto res_test_1 = map_1.at(3.3);
  EXPECT_EQ(res_test_1, 'c');
  EXPECT_THROW(map_1.at(3.2), std::out_of_range);
  EXPECT_THROW(map_2.at(3.3), std::out_of_range);
}

TEST(map_test, test_const_iter_end_empty) {
  ns::map<double, char> map_1;
  ns::map<double, char>::const_iter it = map_1.cend();
  ++it;
  it = map_1.cbegin();
  --it;
  it--;
  it = map_1.cend();
  ++it;
  it++;
}

TEST(map_test, test_const_iter_end_pref) {
  ns::map<double, char> map_1({{1.1, 'a'},
                                {2.2, 'b'},
                                {3.3, 'c'},
                                {4.4, 'd'},
                                {5.5, 'e'},
                                {3.3, 'c'},
                                {4.4, 'd'},
                                {5.5, 'e'}});
  std::map<double, char> orignal_map_1({{1.1, 'a'},
                                        {2.2, 'b'},
                                        {3.3, 'c'},
                                        {4.4, 'd'},
                                        {5.5, 'e'},
                                        {3.3, 'c'},
                                        {4.4, 'd'},
                                        {5.5, 'e'}});
  ns::map<double, char>::const_iter it = map_1.cend();
  std::map<double, char>::const_iterator it_2 = orignal_map_1.cend();
  // --it;
  --it_2;
  EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
  EXPECT_EQ((*it).second, (*it_2).second);
}

TEST(map_test, test_swap) {
  ns::map<int, char> map_1({{1, 'a'}, {3, 'b'}, {5, 'b'}});
  ns::map<int, char> map_2({{2, 'l'}, {4, 'o'}, {6, 'b'}, {8, 's'}});

  EXPECT_EQ(map_1.size(), 3);
  EXPECT_EQ(map_2.size(), 4);

  std::map<int, char> orignal_map_1({{1, 'a'}, {3, 'b'}, {5, 'b'}});
  std::map<int, char> orignal_map_2({{2, 'l'}, {4, 'o'}, {6, 'b'}, {8, 's'}});

  map_1.swap(map_2);
  orignal_map_1.swap(orignal_map_2);

  EXPECT_EQ(map_1.size(), 4);
  EXPECT_EQ(map_2.size(), 3);
  EXPECT_EQ(map_1.size(), orignal_map_1.size());
  EXPECT_EQ(map_2.size(), orignal_map_2.size());

  auto it = map_1.begin();
  auto it_2 = orignal_map_1.begin();
  for (; it != map_1.end(); ++it) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it_2;
  }
}

TEST(map_test, test_iter_plus) {
  ns::map<double, char> map_1({{1.1, 'a'},
                                {2.2, 'b'},
                                {3.3, 'c'},
                                {4.4, 'd'},
                                {5.5, 'e'},
                                {3.3, 'c'},
                                {4.4, 'd'},
                                {5.5, 'e'}});
  std::map<double, char> orignal_map_1({{1.1, 'a'},
                                        {2.2, 'b'},
                                        {3.3, 'c'},
                                        {4.4, 'd'},
                                        {5.5, 'e'},
                                        {3.3, 'c'},
                                        {4.4, 'd'},
                                        {5.5, 'e'}});

  ns::map<double, char>::iter it = map_1.begin();
  std::map<double, char>::iterator it_2 = orignal_map_1.begin();
  for (; it != map_1.end() && it_2 != orignal_map_1.end();) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    ++it;
    ++it_2;
  }
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  it = map_1.begin();
  it_2 = orignal_map_1.begin();
  for (; it != map_1.end() && it_2 != orignal_map_1.end();) {
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
    it++;
    it_2++;
  }
  EXPECT_EQ(map_1.size(), orignal_map_1.size());
}

TEST(map_test, test_iter_minus) {
  ns::map<double, char> map_1({{1.1, 'a'},
                                {2.2, 'b'},
                                {3.3, 'c'},
                                {4.4, 'd'},
                                {5.5, 'e'},
                                {3.3, 'c'},
                                {4.4, 'd'},
                                {5.5, 'e'}});
  std::map<double, char> orignal_map_1({{1.1, 'a'},
                                        {2.2, 'b'},
                                        {3.3, 'c'},
                                        {4.4, 'd'},
                                        {5.5, 'e'},
                                        {3.3, 'c'},
                                        {4.4, 'd'},
                                        {5.5, 'e'}});

  ns::map<double, char>::iter it = map_1.end();
  std::map<double, char>::iterator it_2 = orignal_map_1.end();
  --it_2;
  for (; it != map_1.begin() && it_2 != orignal_map_1.begin();) {
    --it;
    --it_2;
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
  }
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  it = map_1.end();
  it_2 = orignal_map_1.end();
  it_2--;
  for (; it != map_1.begin() && it_2 != orignal_map_1.begin();) {
    it--;
    it_2--;
    EXPECT_DOUBLE_EQ((*it).first, (*it_2).first);
    EXPECT_EQ((*it).second, (*it_2).second);
  }
  EXPECT_EQ(map_1.size(), orignal_map_1.size());

  it = map_1.begin();
  it_2 = orignal_map_1.begin();
  --it;
  --it_2;
  it--;
  it_2--;
  it = map_1.end();
  it_2 = orignal_map_1.end();
  ++it;
  ++it_2;
  it++;
  it_2++;
}

TEST(MapComparison, InsertAndAccess) {
  ns::map<int, int> customMap;
  std::map<int, int> stdMap;

  for (int i = 0; i < 1000; ++i) {
    customMap[i] = i * 2;
    stdMap[i] = i * 2;
  }

  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(customMap[i], stdMap[i]);
  }
}

TEST(array_Test, test1) {
  ns::array<int, 5> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.at(4), 5);
}

TEST(array_Test, test2) {
  //  EXPECT_NO_THROW({
  ns::array<char, 3> v = ns::array<char, 3>();
  //    v.at(2) = 'a';
  EXPECT_EQ(v.at(2), 0);
  //  });
}

TEST(array_Test, construct_test1) {
  // EXPECT_NO_THROW({
  ns::array<char, 8> v = ns::array<char, 8>();
  std::cout << v.size() << std::endl;
  EXPECT_EQ(v.size(), 8);
  // });
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
