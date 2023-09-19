#ifndef STACK_H_
#define STACK_H_

#include "vector.h"

namespace ns {

template <typename T, typename Container = ns::vector<T>>
class stack {
 public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  explicit stack() : cont_(0) {}

  stack(std::initializer_list<T> list,
        const container_type& cont = container_type())
      : cont_(cont) {
    const T* first = list.begin();
    const T* const last = list.end();
    for (; first != last; ++first) push(*first);
  };

  stack(const stack& s) : cont_(s.cont_){};

  stack(stack&& s) { std::swap(cont_, s.cont_); };

  ~stack() {
    while (!empty()) {
      pop();
    }
    cont_.clear();
  };

  stack& operator=(const stack& s) {
    if (this != &s) {
      cont_.clear();
      cont_.Assign(s.begin(), s.end());
    }
    return (*this);
  }

  stack& operator=(stack&& s) {
    if (this != &s) {
      *this = std::move(s);
    }
    return (*this);
  }

  bool empty() const { return (!cont_.size()); }

  size_type size() const { return (cont_.size()); }

  reference& top() { return (cont_.back()); }
  const_reference& top() const { return (cont_.back()); }

  void push(const const_reference& val) { return (cont_.push_back(val)); }

  void pop() { return (cont_.pop_back()); }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    (cont_.push_back(args), ...);
  }

  void swap(stack& other) { cont_.swap(other.cont_); }

 protected:
  container_type cont_;
};

}  // namespace ns

#endif  // STACK_H_
