#ifndef ITERATOR_H_
#define ITERATOR_H_

#include "utils.h"

namespace ns {

template <typename T>
class RAIter {
 public:
  using value_type = T;
  using difference_type = ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;

  RAIter() : elem_(nullptr){};
  RAIter(const pointer other) : elem_(other){};
  RAIter(const RAIter<typename remove_cv<T>::type>& other) : elem_(&(*other)){};
  ~RAIter(){};

  RAIter& operator=(const RAIter& other) {
    if (this == &other) return (*this);
    elem_ = other.elem_;
    return (*this);
  }

  typename ns::conditional<ns::is_const<T>::value, const_reference,
                            reference>::type
  operator*() const {
    return (*elem_);
  }

  pointer operator->() { return &(operator*()); };
  reference operator->() const { return (operator*()); };
  reference operator[](difference_type i) const { return (elem_[i]); };

  RAIter& operator++() {
    elem_++;
    return (*this);
  }

  RAIter& operator--() {
    elem_--;
    return (*this);
  }

  RAIter operator++(int) {
    RAIter temp = *this;
    elem_++;
    return (temp);
  }

  RAIter operator--(int) {
    RAIter temp = *this;
    elem_--;
    return (temp);
  }

  difference_type operator-(const RAIter& rhs) const {
    return elem_ - rhs.elem_;
  }

  RAIter& operator+=(const difference_type diff) {
    elem_ += diff;
    return (*this);
  }

  RAIter& operator-=(const difference_type diff) {
    elem_ -= diff;
    return (*this);
  }

  friend bool operator==(const RAIter& lhs, const RAIter& rhs) {
    return (lhs.elem_ == rhs.elem_);
  }

  friend bool operator!=(const RAIter& lhs, const RAIter& rhs) {
    return (lhs.elem_ != rhs.elem_);
  }

  friend bool operator<(const RAIter& lhs, const RAIter& rhs) {
    return (lhs.elem_ < rhs.elem_);
  }

  friend bool operator>(const RAIter& lhs, const RAIter& rhs) {
    return (lhs.elem_ > rhs.elem_);
  }

  friend bool operator<=(const RAIter& lhs, const RAIter& rhs) {
    return (lhs.elem_ <= rhs.elem_);
  }

  friend bool operator>=(const RAIter& lhs, const RAIter& rhs) {
    return (lhs.elem_ >= rhs.elem_);
  }

 private:
  pointer elem_;
};

template <typename T>
RAIter<T> operator-(const typename RAIter<T>::difference_type lhs,
                    const RAIter<T>& rhs) {
  RAIter<T> temp(rhs);
  return temp -= lhs;
}

template <typename T, typename Node>
class BDIter {
 public:
  using value_type = T;
  using pointer = value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;
  using node_type = Node;
  using node_pointer = node_type*;

  BDIter() : elem_(nullptr){};
  BDIter(const node_pointer ptr) : elem_(ptr){};
  BDIter(const BDIter& other) : elem_(other.elem_){};
  ~BDIter(){};

  BDIter& operator=(const BDIter& other) {
    if (this == &other) return (*this);
    elem_ = other.elem_;
    return (*this);
  };

  typename ns::conditional<ns::is_const<T>::value, const_reference,
                            reference>::type
  operator*() const {
    return (elem_->value);
  }

  bool operator==(const BDIter& other) const { return (elem_ == other.elem_); };
  bool operator!=(const BDIter& other) const { return (elem_ != other.elem_); };

  node_pointer operator->() const { return elem_; };
  BDIter& operator++() {
    if (elem_->forward() != nullptr) elem_ = elem_->forward();
    return (*this);
  }

  BDIter& operator--() {
    if (elem_->back() != nullptr) elem_ = elem_->back();
    return (*this);
  }

  BDIter operator++(int) {
    BDIter temp = *this;
    if (elem_->forward() != nullptr) ++(*this);
    return temp;
  }

  BDIter operator--(int) {
    BDIter temp = *this;
    if (elem_->back() != nullptr) --(*this);
    return (temp);
  }

 private:
  node_pointer elem_;
};

template <typename T>
RAIter<T> operator+(const RAIter<T>& lhs,
                    const typename RAIter<T>::difference_type rhs) {
  RAIter<T> temp(lhs);
  return temp += rhs;
}

template <typename T>
RAIter<T> operator-(const RAIter<T>& lhs,
                    const typename RAIter<T>::difference_type rhs) {
  RAIter<T> temp(lhs);
  return temp -= rhs;
}

template <typename T>
RAIter<T> operator+(const typename RAIter<T>::difference_type lhs,
                    const RAIter<T>& rhs) {
  RAIter<T> temp(rhs);
  return temp += lhs;
}

}  // namespace ns

#endif  // ITERATOR_H_
