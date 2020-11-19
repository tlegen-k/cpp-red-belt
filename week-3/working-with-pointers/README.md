## Working with pointers
In this task, you need to implement three templated functions:

- template <typename T> void Swap (T * first, T * second) - swaps the values ​​pointed to by first and second
- template <typename T> void SortPointers (vector <T *> & pointers) - sorts pointers by the values ​​they point to
- template <typename T> void ReversedCopy (T * src, size_t count, T * dst) - copies count elements in reverse order, starting from the address in the src pointer, to the memory area starting at dst. Wherein
1. each object from the range [src; src + count) must be copied at most once;
2. ranges [src; src + count) and [dst; dst + count) may overlap;
3. elements in part of the range [src; src + count) that does not intersect with [dst; dst + count) must remain unchanged.

For examples of using templates, see the tests in the solution template
