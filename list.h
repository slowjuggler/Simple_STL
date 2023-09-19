#ifndef LIST_H_
#define LIST_H_

#include "allocator.h"
#include "compare.h"
#include "node.h"
#include "utils.h"

#define SIZE 64  // architecture defined

namespace ns {

template <typename T, typename Allocator = ns::LinearAllocator<T>>
class list {
 public:
  using node_type = ns::ListNode<T>;
  using node_pointer = node_type*;
  using value_type = T;
  using pointer = value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iter = ns::BDIter<T, node_type>;
  using const_iter = ns::BDIter<const T, node_type>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using allocator_type = typename Allocator::template rebind<node_type>::other;

  list(const allocator_type& alloc = allocator_type(),
       const value_type& val = value_type())
      : alloc_(alloc), size_(0), head_(nullptr) {
    head_ = alloc_.allocate(1);
    alloc_.construct(head_, node_type(val));
    head_->prev = head_;
    head_->next = head_;
  }

  list(size_type num, const value_type& val = value_type()) : list() {
    for (size_type i = 0; i < num; ++i) push_back(val);
  }

  list(const std::initializer_list<T>& items) : list() {
    for (const value_type& item : items) push_back(item);
  }

  list(const list& l) : list() {
    const_iter first = l.cbegin();
    const_iter last = l.cend();
    while (first != last) {
      push_back(*first);
      ++first;
    }
  }

  list(list&& l) : list() { swap(l); }

  ~list() {
    clear();
    alloc_.destroy(head_);
    alloc_.deallocate(head_, 1);
  }

  list& operator=(const list& l) {
    if (this != &l) {
      list temp(l);
      swap(temp);
    }
    return (*this);
  }

  list& operator=(list&& l) {
    if (this != &l) {
      swap(l);
    }
    return (*this);
  }

  iter begin() const { return (iter(head_->next)); }
  iter end() const { return (iter(head_)); }

  const_iter cbegin() const { return (const_iter(head_->next)); }
  const_iter cend() const { return (const_iter(head_)); }

  bool empty() const { return (!size()); };

  size_type size() const { return (size_); };

  size_type max_size(void) const { return alloc_.max_size() / 2; };

  reference front() {
    // if (empty()) throw std::logic_error("container is empty");
    return (*begin());
  }
  const_reference front() const {
    // if (empty()) throw std::logic_error("container is empty");
    return (*begin());
  }

  reference back() {
    //  if (empty()) throw std::logic_error("container is empty");
    return (head_->prev->value);
  }
  const_reference back() const {
    //  if (empty()) throw std::logic_error("container is empty");
    return (head_->prev->value);
  }

  iter insert(const iter& pos, const_reference val) {
    node_pointer ptr = NewNode(val);
    ptr->next = pos.operator->();
    ptr->prev = pos.operator->()->prev;
    pos.operator->()->prev->next = ptr;
    pos.operator->()->prev = ptr;
    return (iter(ptr));
  }

  void clear() {
    if (empty()) return;
    node_pointer node = head_->next;
    while (node != head_) {
      node_pointer tmp = node;
      node = node->next;
      DelNode(tmp);
    }
    head_->next = head_;
    head_->prev = head_;
  }

  void erase(const iter& pos) {
    if (empty()) return;
    node_pointer temp = pos.operator->();
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    DelNode(temp);
  }

  void push_back(const_reference val) { insert(end(), val); }

  void pop_back() { erase(--end()); };

  void push_front(const_reference val) { insert(begin(), val); }

  void pop_front() { erase(begin()); };

  void swap(list& other) {
    std::swap(head_, other.head_);
    std::swap(size_, other.size_);
  }

  void reverse() {
    node_pointer node = head_;
    do {
      std::swap(node->prev, node->next);
      node = node->prev;
    } while (node != head_);
  }

  void unique() {
    iter first = begin();
    iter last = end();
    iter it = first;
    while (++it != last) {
      if (*first == *it) {
        erase(it);
        it = first;
      } else {
        first = it;
      }
    }
  }

  void splice(const iter& pos, list& other) {
    Link(pos, other.begin(), other.end());
    other.size_ = 0;
  }

  void merge(list& other) {
    iter it = begin();
    iter last = end();
    iter it_other = other.begin();
    iter last_other = other.end();
    while (it != last && it_other != last_other) {
      if (*it_other < *it) {
        iter cur = it_other;
        ++it_other;
        Link(it, cur, it_other);
      } else {
        ++it;
      }
    }
    if (it_other != last_other) {
      Link(last, it_other, last_other);
    }
    other.size_ = 0;
  }

  void sort() {
    if (empty()) return;
    list item[SIZE] = {};
    int pow = GetPow();
    GetArray(item);
    for (int i = 1; i <= pow; ++i) item[i].merge(item[i - 1]);
    swap(item[pow]);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    insert_many(cbegin(), args...);
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    insert_many(cend(), args...);
  }

  template <typename... Args>
  iter insert_many(const_iter pos, Args&&... args) {
    size_type init_size = size();
    node_pointer ptr = pos.operator->();
    list tmp{args...};
    if (!tmp.empty()) Link(iter(pos.operator->()), tmp.begin(), tmp.end());
    size_type count = size() - init_size;
    while (count--) ptr = ptr->prev;
    return (iter(ptr));
  }

  void print() {
    iter first = begin();
    const iter last = end();
    for (size_type i = 0; i < size_; ++i) {
      std::cout << *first << std::endl;
      ++first;
    }
  }

 private:
  allocator_type alloc_;
  size_type size_;
  node_pointer head_;

  void Link(iter pos, iter first, iter last) {
    if (pos != first && pos != last) {
      node_pointer temp = pos->prev;
      last->prev->next = pos.operator->();
      first->prev->next = last.operator->();
      pos->prev->next = first.operator->();
      pos->prev = last->prev;
      last->prev = first->prev;
      first->prev = temp;
      GetSize();
    }
  }

  void GetSize() {
    size_type n = 0;
    for (const_iter it = cbegin(), last = cend(); it != last; ++it) ++n;
    size_ = n;
  }

  node_pointer NewNode(const_reference val) {
    node_pointer ptr = alloc_.allocate(1);
    alloc_.construct(ptr, node_type(val));
    ++size_;
    return ptr;
  }

  void DelNode(node_pointer ptr) {
    alloc_.destroy(ptr);
    alloc_.deallocate(ptr, 1);
    --size_;
  }

  int GetPow() const {
    int count = size();
    for (int pow = 0; pow < SIZE; ++pow)
      if (count < (1 << pow)) return pow;
    return 0;
  }

  void GetArray(list item[]) {
    while (size()) {
      int i = 0;
      if (item[i].empty()) {
        item[i].push_back(front());
        pop_front();
      } else if (item[i + 1].empty()) {
        item[i + 1].push_back(front());
        pop_front();
        item[i + 1].merge(item[i]);
      } else {
        for (; static_cast<int>(item[i].size()) == (1 << i); ++i)
          ;
        for (; i > 1; --i) item[i].merge(item[i - 1]);
      }
    }
  }
};

template <typename T, typename Node = ListNode<T>>
bool operator<(ns::list<T>& lhs, ns::list<T>& rhs) {
  return ns::lexicographical_compare<ns::BDIter<T, Node>,
                                      ns::BDIter<T, Node>>(
      lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
};

}  // namespace ns

#endif  // LIST_H_
