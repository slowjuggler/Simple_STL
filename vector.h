#ifndef VECTOR_H_
#define VECTOR_H_

#include "compare.h"
#include "utils.h"

namespace ns {

template <typename T, typename Allocator = ns::LinearAllocator<T>>
class vector {
 public:
  using value_type = T;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using allocator_type = Allocator;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iter = ns::RAIter<T>;
  using const_iter = ns::RAIter<const T>;

  vector(const allocator_type& alloc = allocator_type())
      : alloc_(alloc), ptr_(nullptr), cap_(0), size_(0) {}

  vector(size_type n, const value_type& val = value_type(),
         const allocator_type& alloc = allocator_type())
      : alloc_(alloc), ptr_(nullptr), cap_(0), size_(0) {
    if (n > 0) {
      ptr_ = alloc_.allocate(n);
      cap_ = n;
      size_ = n;
      for (size_type i = 0; i < n; i++) {
        alloc_.construct(ptr_ + i, val);
      }
    }
  }

  vector(std::initializer_list<T> list,
         const allocator_type& alloc = allocator_type())
      : alloc_(alloc), ptr_(nullptr), cap_(0), size_(0) {
    const T* first = list.begin();
    const T* const last = list.end();
    auto count = last - first;

    if (count > 0) {
      ptr_ = alloc_.allocate(count);
      size_ = count;
      cap_ = count;
      for (size_type i = 0; first != last; ++first)
        alloc_.construct(ptr_ + i++, *first);
    }
  }

  vector(const vector& other)
      : alloc_(other.alloc_),
        ptr_(alloc_.allocate(other.cap_)),
        cap_(other.cap_),
        size_(other.size_) {
    for (size_type i = 0; i < size_; i++) alloc_.construct(ptr_ + i, other[i]);
  };

  vector(vector&& other) : ptr_(nullptr), cap_(0), size_(0) {
    std::swap(alloc_, other.alloc_);
    std::swap(ptr_, other.ptr_);
    std::swap(cap_, other.cap_);
    std::swap(size_, other.size_);
  };

  ~vector() {
    clear();
    if (cap_ > 0) alloc_.deallocate(ptr_, cap_);
  };

  vector& operator=(vector& other) {
    if (this != &other) {
      clear();
      Assign(other.begin(), other.end());
    }
    return (*this);
  }

  vector& operator=(const vector& other) {
    if (this != &other) {
      clear();
      Assign(other.cbegin(), other.cend());
    }
    return (*this);
  }

  vector& operator=(vector&& other) {
    if (this != &other) {
      swap(other);
    }
    return (*this);
  }

  reference at(size_type pos) {
    if (pos >= size()) throw std::out_of_range("out of range");
    return ptr_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size()) throw std::out_of_range("out of range");
    return ptr_[pos];
  }

  reference operator[](size_type pos) { return (ptr_[pos]); }

  const_reference operator[](size_type pos) const { return (ptr_[pos]); }

  reference front() {
    if (empty()) throw std::logic_error("container is empty");
    return (*ptr_);
  }

  const_reference front() const {
    if (empty()) throw std::logic_error("container is empty");
    return (*ptr_);
  }

  reference back() {
    if (empty()) throw std::logic_error("container is empty");
    return ptr_[size_ - 1];
  }

  const_reference back() const {
    if (empty()) throw std::logic_error("container is empty");
    return ptr_[size_ - 1];
  }

  pointer data() { return ptr_; }

  iter begin() { return (iter(ptr_)); }
  iter end() { return (iter(ptr_ + size_)); }

  const_iter cbegin() { return (const_iter(ptr_)); }
  const_iter cend() { return (const_iter(ptr_ + size_)); }

  bool empty() const { return (!size()); }

  size_type size() const { return (size_); }

  size_type max_size(void) const { return alloc_.max_size() >> 1; }

  void reserve(size_type size) {
    if (size > max_size()) {
      throw(std::length_error("too much"));
    } else if (size > cap_) {
      pointer new_ptr = alloc_.allocate(size);
      for (size_type i = 0; i < size_; ++i)
        alloc_.construct(new_ptr + i, *(ptr_ + i));
      alloc_.deallocate(ptr_, cap_);
      ptr_ = new_ptr;
      cap_ = size;
    }
  }

  size_type capacity() const { return (cap_); }

  void shrink_to_fit() {
    if (cap_ - size_ > 0) {
      pointer new_ptr = alloc_.allocate(size_);
      for (size_type i = 0; i < size_; ++i)
        alloc_.construct(new_ptr + i, *(ptr_ + i));
      alloc_.deallocate(ptr_, cap_);
      ptr_ = new_ptr;
      cap_ = size_;
    }
  }

  void clear() {
    if (size_ > 0) {
      for (iter it = begin(); it != end(); ++it) alloc_.destroy(&(*it));
      size_ = 0;
    }
  }

  iter insert(iter pos, const value_type& val) {
    size_type idx = pos - begin();
    reserve(size_ + 1);
    pos = begin() + idx;
    ShiftBack(pos);
    alloc_.construct(&(*pos), val);
    size_++;
    return (pos);
  }

  void insert(iter pos, size_type n, const value_type& val) {
    size_type idx = pos - begin();
    reserve(size_ + n);
    pos = begin() + idx;
    ShiftBack(pos, n);
    for (size_type i = 0; i < n; ++i) alloc_.construct(&(*(pos + i)), val);
    size_ += n;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push_back(args), ...);
  }

  template <typename... Args>
  iter insert_many(iter pos, Args&&... args) {
    vector<value_type> temp{args...};
    iter insert_pos = pos;
    for (size_t i = 0; i < temp.size(); ++i, ++insert_pos) {
      insert_pos = insert(insert_pos, temp[i]);
    }
    return insert_pos;
  }

  iter erase(iter pos) {
    if (empty()) return end();
    iter it = pos;
    alloc_.destroy(&(*it));
    iter next_it = it + 1;
    while (next_it != end()) {
      alloc_.construct(&(*it), *next_it);
      it++;
      next_it++;
    }
    pop_back();
    return pos;
  }

  iter erase(iter first, iter last) {
    if (empty()) return (end());
    iter it = begin();
    iter itb = first;
    difference_type dist = last - first;
    while (it != first) it++;
    for (; first != last; ++first) alloc_.destroy(&(*first));
    while (it + dist != end()) {
      alloc_.construct(&(*it), *(it + dist));
      it++;
    }
    while (dist-- > 0) pop_back();
    return itb;
  }

  void push_back(const_reference val) {
    if (size_ == cap_) empty() ? reserve(1) : reserve(size_ * 2);
    alloc_.construct(ptr_ + size_, val);
    size_++;
  }

  void pop_back() {
    if (size_ == 0) return;
    alloc_.destroy(ptr_ + size_ - 1);
    size_--;
    if (size_ < cap_ / 2) {
      reserve(cap_ / 2);
    }
  }

  void swap(vector& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(cap_, other.cap_);
    std::swap(size_, other.size_);
  }

  void Resize(size_type n, value_type val = value_type()) {
    if (n > cap_) reserve(n);
    if (n >= size_) {
      for (size_type i = size_; i < n; ++i) alloc_.construct(ptr_ + i, val);
    } else {
      for (size_type i = n; i < size_; ++i) alloc_.destroy(ptr_ + i);
      size_ = n;
    }
  }

  void Assign(iter begin, iter end) {
    clear();
    for (iter it = begin; it != end; ++it) {
      push_back(*it);
    }
  }

  void PushFront(const_reference val) { insert(begin(), val); }

 private:
  allocator_type alloc_;
  pointer ptr_;
  size_type cap_;
  size_type size_;

  void ShiftBack(iter pos, size_type n = 1) {
    if (pos == end()) return;
    ShiftBack(pos + 1, n);
    alloc_.construct(&(*(pos + n)), *pos);
  }
};

}  // namespace ns

#endif  // VECTOR_H_
