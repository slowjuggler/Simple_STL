#ifndef MULTISET_H_
#define MULTISET_H_

#include "node.h"
#include "utils.h"
#include "vector.h"

namespace ns {

template <typename Key, typename Compare = std::less_equal<Key>,
          typename Allocator = ns::LinearAllocator<Key>>
class multiset {
 public:
  using compare_type = Compare;
  using key_type = Key;
  using value_type = Key;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;
  using node_type = ns::RBTnode<value_type>;
  using node_pointer = node_type*;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using allocator_type = Allocator;
  using tree_type =
      ns::RBTree<value_type, std::less<value_type>, allocator_type>;
  using iter = ns::BDIter<value_type, node_type>;
  using const_iter = ns::BDIter<const value_type, node_type>;

  multiset(const allocator_type& alloc = allocator_type()) : tree_(alloc){};

  multiset(std::initializer_list<value_type> list,
           const allocator_type& alloc = allocator_type())
      : tree_(alloc) {
    for (const value_type& val : list) {
      tree_.insert_all(val);
    }
  };

  multiset(const multiset& other) : tree_(other.tree_){};

  multiset(multiset&& other) : tree_(std::move(other.tree_)){};

  ~multiset(){};

  multiset& operator=(const multiset& other) {
    if (this == &other) return *this;
    clear();
    tree_ = other.tree_;
    return (*this);
  };

  multiset& operator=(multiset&& other) {
    tree_ = std::move(other.tree_);
    return *this;
  };

  size_type size() const { return (tree_.size()); };

  size_type max_size() const {
    return (std::numeric_limits<size_type>::max() / (20 * sizeof(value_type)));
  };

  iter begin() { return (size() ? iter(tree_.start()) : nullptr); };

  const_iter begin() const {
    return (size() ? const_iter(tree_.cstart()) : nullptr);
  };

  const_iter cbegin() const { return begin(); }

  iter end() { return (size() ? iter(tree_.edge()) : nullptr); };

  const_iter end() const {
    return (size() ? const_iter(tree_.cedge()) : nullptr);
  };

  const_iter cend() const { return end(); }

  bool empty() const { return (!size()); };

  iter insert(const_reference& val) {
    auto result = tree_.insert_all(val);
    return result.first;
  }

  template <typename... Args>
  ns::vector<std::pair<iter, bool>> insert_many(Args&&... args) {
    ns::vector<std::pair<iter, bool>> vector;
    (vector.insert_many_back(tree_.insert_all(std::forward<Args>(args))), ...);
    return vector;
  };

  void erase(iter pos) {
    try {
      tree_.erase(pos);
    } catch (...) {
      throw std::runtime_error("s21::multiset::erase");
    }
  };

  void clear() { tree_.clear(); };

  bool IsBalanced() { return (tree_.is_balanced()); };

  void swap(multiset& other) { tree_.swap(other.tree_); };

  void print() { tree_.print_mult(); };

  size_type count(const key_type& key) {
    iter it = lower_bound(key);
    iter last = upper_bound(key);
    size_type n = 0;

    while (it != last) {
      ++n;
      ++it;
    }

    return n;
  }

  iter lower_bound(const key_type& key) { return tree_.lower_bound(key); };

  const_iter lower_bound(const key_type& key) const {
    return tree_.lower_bound(key);
  };

  iter upper_bound(const key_type& key) { return tree_.upper_bound(key); };

  const_iter upper_bound(const key_type& key) const {
    return tree_.upper_bound(key);
  };

  std::pair<const_iter, const_iter> equal_range(const key_type& key) const {
    return tree_.equal_range(key);
  };

  std::pair<iter, iter> equal_range(const key_type& key) {
    return tree_.equal_range(key);
  };

  iter find(const key_type& key) {
    return (contains(key) ? tree_.find(key).first : nullptr);
  };

  bool contains(const key_type& key) { return (tree_.find(key).second); };

  void merge(multiset& other) {
    iter first = other.begin();
    const iter last = other.end();
    for (; first != last; ++first) insert(*first);
    insert(*last);
    other.clear();
  };

 private:
  tree_type tree_;
};

}  // namespace ns

#endif  // MULTISET_H_
