## Maximal element by predicate

Implement function
```cpp
template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(
  ForwardIterator first, ForwardIterator last, UnaryPredicate pred);
```
which returns an iterator to the maximum element in the range [first, last) for which pred returns true. If the range contains multiple matching elements with a maximum value, the result is the first occurrence of that element. If the range contains no matching elements, then the function should return last.
It is guaranteed that:
- pred takes an argument of the type that the elements of the range have
- Operators ++, ==,! =, * (dereference) are defined for ForwardIterator
- operator <("less than") is defined for the type pointed to by the iterator
