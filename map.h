#ifndef MAP_H_
#define MAP_H_

#include <vector>

#include "node.h"
#include "utils.h"
#include "vector.h"

namespace ns {

template <typename Key, typename T, typename Compare = std::less<Key>,
          typename Allocator = ns::LinearAllocator<std::pair<Key, T>>>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;
  using node_type = ns::RBTnode<value_type>;
  using node_pointer = node_type*;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using compare_type = Compare;
  using iter = ns::BDIter<value_type, node_type>;
  using const_iter = ns::BDIter<const value_type, node_type>;
  using allocator_type = Allocator;

  class value_compare {
    friend class map;

   protected:
    compare_type comp_;
    value_compare(compare_type comp) : comp_(comp) {}

   public:
    value_compare() = default;
    bool operator()(const_reference x, const_reference y) const {
      return comp_(x.first, y.first);
    }
  };

  using tree_type = ns::RBTree<value_type, value_compare, allocator_type>;

  map(const allocator_type& alloc = allocator_type(),
      const value_compare& comp = compare_type())
      : tree_(alloc, comp){};

  map(std::initializer_list<value_type> list,
      const allocator_type& alloc = allocator_type(),
      const value_compare& comp = compare_type())
      : tree_(alloc, comp) {
    const value_type* first = list.begin();
    const value_type* last = list.end();
    difference_type count = last - first;
    if (!count) return;
    for (; first != last; first++) insert(*first);
  };

  map(const map& m) : tree_(m.tree_){};

  map(map&& m) : tree_() {
    if (m.empty()) return;
    swap(m);
  }

  ~map(){};

  map& operator=(const map& m) {
    if (this == &m) return *this;
    clear();
    tree_ = m.tree_;
    return (*this);
  };
  map& operator=(map&& m) {
    if (this == &m) return *this;
    clear();
    swap(m);
    return (*this);
  };

  iter begin() const { return (size() ? tree_.start() : nullptr); };
  const_iter cbegin() const {
    return (size() ? const_iter(tree_.cstart()) : nullptr);
  };

  iter end() const { return (size() ? tree_.edge() : nullptr); };

  const_iter cend() const {
    return (size() ? const_iter(tree_.cedge()) : nullptr);
  };

  bool empty() const { return (!size()); };

  size_type size() const { return (tree_.size()); };

  size_type max_size() const { return (tree_.max_size()); };

  mapped_type& at(const key_type& key) {
    if (tree_.find(std::make_pair(key, mapped_type())).second != true)
      throw std::out_of_range("there is no this key in the map");
    return (tree_.find(std::make_pair(key, mapped_type())).first->value.second);
  };

  mapped_type& operator[](const key_type& key) {
    return ((insert(std::make_pair(key, mapped_type()))).first->value.second);
  };

  std::pair<iter, bool> insert(const_reference val) {
    return (tree_.insert(val));
  };

  std::pair<iter, bool> insert(const key_type& key, const mapped_type& obj) {
    return (tree_.insert(std::make_pair(key, obj)));
  };

  std::pair<iter, bool> insert_or_assign(const key_type& key,
                                         const mapped_type& obj) {
    return (tree_.insert_or_assign(std::make_pair(key, obj)));
  };

  template <typename... Args>
  ns::vector<std::pair<iter, bool>> insert_many(Args&&... args) {
    ns::vector<std::pair<iter, bool>> vector;
    (vector.insert_many_back(tree_.insert(std::forward<Args>(args))), ...);
    return vector;
  }

  void erase(iter pos) {
    try {
      tree_.erase(pos);
    } catch (...) {
      throw std::runtime_error("s21::map::erase");
    }
  };

  void merge(map& other) {
    iter first = other.begin();
    const iter last = other.end();
    for (; first != last; ++first) insert(*first);
    insert(*last);
    other.clear();
  };

  void clear() { tree_.clear(); };

  bool IsBalanced() { return (tree_.is_balanced()); };

  bool contains(const key_type& key) {
    return (tree_.find(std::make_pair(key, mapped_type())).second);
  };

  void swap(map& m) { tree_.swap(m.tree_); };

  void print() { tree_.print(); };

 private:
  tree_type tree_;
};

}  // namespace ns

#endif  // MAP_H_
