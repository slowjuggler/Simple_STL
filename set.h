#ifndef SET_H_
#define SET_H_

#include "node.h"
#include "utils.h"
#include "vector.h"

namespace ns {

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = ns::LinearAllocator<Key>>
class set {
 public:
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
  using compare_type = Compare;
  using iter = ns::BDIter<value_type, node_type>;
  using const_iter = ns::BDIter<const value_type, node_type>;
  using allocator_type = Allocator;
  using tree_type = ns::RBTree<value_type, compare_type, allocator_type>;

  set(const allocator_type& alloc = allocator_type(),
      const compare_type& comp = compare_type())
      : tree_(alloc, comp){};

  set(std::initializer_list<value_type> list,
      const allocator_type& alloc = allocator_type(),
      const compare_type& comp = compare_type())
      : tree_(alloc, comp) {
    const value_type* first = list.begin();
    const value_type* last = list.end();
    difference_type count = last - first;
    if (!count) return;
    for (; first != last; first++) insert(*first);
  };

  set(const set& s) : tree_(s.tree_){};

  set(set&& s) : tree_() {
    if (s.empty()) return;
    swap(s);
  };

  ~set(){};

  set& operator=(const set& s) {
    if (this == &s) return *this;
    clear();
    tree_ = s.tree_;
    return (*this);
  }

  set& operator=(set&& s) {
    if (this == &s) return *this;
    clear();
    swap(s);
    return (*this);
  }

  size_type size() const { return (tree_.size()); }

  size_type max_size() const {
    return (std::numeric_limits<size_type>::max() / (20 * sizeof(value_type)));
  }

  iter begin() { return (size() ? tree_.start() : nullptr); }

  const_iter cbegin() const {
    return (size() ? const_iter(tree_.cstart()) : nullptr);
  }

  iter end() { return (size() ? tree_.edge() : nullptr); }

  const_iter cend() const {
    return (size() ? const_iter(tree_.cedge()) : nullptr);
  }

  bool empty() const { return (!size()); };

  std::pair<iter, bool> insert(const_reference val) {
    return (tree_.insert(val));
  }

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
      throw std::runtime_error("s21::set::erase");
    }
  }

  void clear() { tree_.clear(); };

  bool IsBalanced() { return (tree_.is_balanced()); };

  void swap(set& other) { tree_.swap(other.tree_); };

  iter find(const Key& key) {
    return (contains(key) ? tree_.find(key).first : nullptr);
  }

  bool contains(const Key& key) { return (tree_.find(key).second); };

  void merge(set& other) {
    iter first = other.begin();
    const iter last = other.end();
    for (; first != last; ++first) insert(*first);
    insert(*last);
    other.clear();
  }

  void Print() { tree_.print(); };

 private:
  tree_type tree_;
};

}  // namespace ns

#endif  // SET_H_
