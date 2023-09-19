#ifndef ALLOCATOR_H_
#define ALLOCATOR_H_

#include <memory>

namespace ns {

template <typename T>
class LinearAllocator {
 public:
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;

  LinearAllocator() throw(){};
  LinearAllocator(const LinearAllocator&) throw(){};
  template <typename U>
  LinearAllocator(const LinearAllocator<U>&) throw(){};
  ~LinearAllocator(){};

  pointer address(reference value) const { return &value; }
  const_pointer address(const_reference value) const { return &value; }

  pointer allocate(size_type n) {
    return static_cast<pointer>(::operator new(n * sizeof(value_type)));
  }

  void deallocate(void* ptr, size_type n) {
    (void)n;
    ::operator delete(static_cast<T*>(ptr));
  }

  template <typename U, typename... Args>
  void construct(U* ptr, Args&&... args) {
    ::new (static_cast<void*>(ptr)) U(std::forward<Args>(args)...);
  }

  void construct(pointer ptr, const T& val) {
    new (static_cast<T*>(ptr)) T(val);
  }

  template <typename U>
  void destroy(U* ptr) {
    ptr->~U();
  }

  void destroy(pointer ptr) { ptr->~T(); }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  template <typename U>
  struct rebind {
    using other = LinearAllocator<U>;
  };
};

}  // namespace ns

#endif  // ALLOCATOR_H_
