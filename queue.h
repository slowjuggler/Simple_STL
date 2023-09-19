#ifndef QUEUE_H_
#define QUEUE_H_

#include "vector.h"

namespace ns {

template <typename T, typename Container = ns::vector<T>>
class queue {
 public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  explicit queue() : cont_(0) {}
  queue(std::initializer_list<T> list,
        const container_type& cont = container_type())
      : cont_(cont) {
    const T* first = list.begin();
    const T* const last = list.end();
    for (; first != last; ++first) push(*first);
  }

  queue(const queue& q) : cont_(q.cont_) {}

  queue(queue&& q) { std::swap(cont_, q.cont_); }

  ~queue() {}

  queue& operator=(const queue& q) {
    if (this != &q) {
      cont_.clear();
      cont_.Assign(q.begin(), q.end());
    }
    return (*this);
  }

  queue& operator=(queue&& q) {
    if (this != &q) {
      *this = std::move(q);
    }
    return (*this);
  }

  const_reference front() const {
    if (cont_.empty()) {
      throw std::logic_error("the container is empty");
    }
    return (cont_.back());
  }

  const_reference back() const {
    if (cont_.empty()) {
      throw std::logic_error("the container is empty");
    }
    return (cont_.front());
    ;
  }

  bool empty() const { return (cont_.empty()); }

  size_type size() const { return (cont_.size()); }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push(args), ...);
  }

  void push(const_reference val) { cont_.PushFront(val); }

  void pop() { cont_.pop_back(); }

  void swap(queue& other) { cont_.swap(other.cont_); }

 protected:
  container_type cont_;
};

}  // namespace ns

#endif  // QUEUE_H_
