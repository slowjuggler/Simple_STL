#ifndef UTILS_H_
#define UTILS_H_

namespace ns {

template <typename T1, typename T2>
struct pair {
  using first_type = T1;
  using second_type = T2;
  first_type first;
  second_type second;
  pair() : first(T1()), second(T2()) {}

  template <class U, class V>
  pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

  pair(const first_type& a, const second_type& b) : first(a), second(b) {}

  pair& operator=(const pair& rhs) {
    if (this == &rhs) return (*this);
    first = rhs.first;
    second = rhs.second;
    return (*this);
  }
};

template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first < rhs.first ||
         (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(rhs < lhs);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return rhs < lhs;
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(lhs < rhs);
}

template <class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y) {
  return (pair<T1, T2>(x, y));
}

template <class T>
struct remove_cv {
  using type = T;
};
template <class T>
struct remove_cv<const T> {
  using type = T;
};
template <class T>
struct remove_cv<volatile T> {
  using type = T;
};
template <class T>
struct remove_cv<const volatile T> {
  using type = T;
};
template <class T>
struct remove_const {
  using type = T;
};
template <class T>
struct remove_const<const T> {
  using type = T;
};
template <class T>
struct remove_volatile {
  using type = T;
};
template <class T>
struct remove_volatile<volatile T> {
  using type = T;
};

template <bool Cond, typename Result = void>
struct enable_if {};
template <typename Result>
struct enable_if<true, Result> {
  using type = Result;
};

struct false_type {
  static const bool value = false;
};
struct true_type {
  static const bool value = true;
};

template <typename>
struct is_integral_base : false_type {};
template <>
struct is_integral_base<bool> : true_type {};
template <>
struct is_integral_base<char> : true_type {};
template <>
struct is_integral_base<wchar_t> : true_type {};
template <>
struct is_integral_base<short> : true_type {};
template <>
struct is_integral_base<int> : true_type {};
template <>
struct is_integral_base<long> : true_type {};
template <>
struct is_integral_base<long long> : true_type {};
template <>
struct is_integral_base<unsigned char> : true_type {};
template <>
struct is_integral_base<unsigned short> : true_type {};
template <>
struct is_integral_base<unsigned int> : true_type {};
template <>
struct is_integral_base<unsigned long> : true_type {};
template <>
struct is_integral_base<unsigned long long> : true_type {};
template <typename T>
struct is_integral : is_integral_base<typename ns::remove_cv<T>::type> {
  using value_type = bool;
  using type = is_integral_base<typename ns::remove_cv<T>::type>;
  operator value_type() { return (this->value); }
};

template <bool B, typename T, typename F>
struct conditional {
  using type = T;
};
template <typename T, typename F>
struct conditional<false, T, F> {
  using type = F;
};

template <class T>
struct is_const : false_type {};
template <class T>
struct is_const<const T> : true_type {};
template <class T>
struct add_cv {
  using type = const volatile T;
};
template <class T>
struct add_const {
  using type = const T;
};
template <class T>
struct add_volatile {
  using type = volatile T;
};

template <typename T>
struct is_pair : false_type {};
template <typename T1, typename T2>
struct is_pair<ns::pair<T1, T2> > : true_type {};

}  // namespace ns

#endif  // UTILS_H_
