#ifndef ARRAY_H_
#define ARRAY_H_

#include <cmath>
#include <iostream>
#include <memory>

#include "allocator.h"
#include "compare.h"
#include "iterator.h"
#include "utils.h"

namespace ns {

template <class T, std::size_t N>
class array {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using iter = ns::RAIter<T>;
  using const_iter = ns::RAIter<const T>;

  array() = default;

  array(std::initializer_list<T> list) {
    if (list.size() > N)
      throw std::invalid_argument("too many initializer values");

    auto first = list.begin();
    for (size_type i = 0; i < list.size(); i++) data_[i] = *first++;
    SetArrayValue(list.size(), N, value_type{});
  };

  array(const array& v) : size_(v.size_) {
    for (size_type i = 0; i < size_; i++) {
      data_[i] = v.data_[i];
    }
  };

  array(array&& other) : size_(other.size_) {
    std::swap(data_, other.data_);
    other.size_ = 0;
  };

  ~array(){};

  array& operator=(const array& other) {
    if (this != &other) {
      for (size_type i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
      }
    }
    return (*this);
  }

  iter begin() { return (iter(data_)); }
  iter end() { return (iter(data_ + size_)); }

  const_iter begin() const { return (const_iter(data_)); }
  const_iter end() const { return (const_iter(data_ + size_)); }

  const_iter cbegin() const { return data_; }
  const_iter cend() const { return data_ + size_; }

  iter data() { return data_; }

  reference operator[](size_type n) { return (data_[n]); }
  const_reference operator[](size_type n) const { return (data_[n]); }

  size_type size() const { return (size_); }
  size_type max_size() const { return (size_); }

  reference at(size_type n) {
    if (n >= size()) throw std::out_of_range("out of range");
    return data_[n];
  }
  const_reference at(size_type n) const {
    if (n >= size()) throw std::out_of_range("out of range");
    return data_[n];
  }

  const_reference front() const { return data_[0]; }
  const_reference back() const { return data_[size_ - 1]; }

  bool empty() const { return size_ == 0; }

  void swap(array& other) {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < size_; ++i) {
      data_[i] = value;
    }
  }

 private:
  size_type size_ = N;
  T data_[N];

  void SetArrayValue(size_type start_index, size_type end_index,
                     const_reference value) {
    for (size_type i = start_index; i < end_index; ++i) data_[i] = value;
  }
};
}  // namespace ns

#endif  // ARRAY_H_
