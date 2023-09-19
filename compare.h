#ifndef COMPARE_H_
#define COMPARE_H_

namespace ns {

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
           InputIterator2 last2) {
  while (first1 != last1 && first2 != last2) {
    if (*first1 != *first2) return false;
    ++first1;
    ++first2;
  }
  if (first1 == last1 && first2 == last2) return true;
  return false;
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
  while (first1 != last1) {
    if (first2 == last2 || *first2 < *first1)
      return false;
    else if (*first1 < *first2)
      return true;
    ++first1;
    ++first2;
  }
  return (first2 != last2);
}

}  // namespace ns

#endif  // COMPARE_H_
