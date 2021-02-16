# Stack Vector

In the block about the memory model, we said that dynamic memory is needed to store those objects that should live longer than the function that created them. In addition, we said that you can create a vector that does not use memory from the heap, but stores all its objects on the stack. In this task you have to do it. You just recently became familiar with the array container, which stores all of its data on the stack. Implement the vector interface on top of it. More formally, implement the class template template <typename T, size_t N> StackVector <T, N>, where T is the vector element type and N is its maximum capacity. The StackVector class must have the following interface:
```cpp
template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0);

  T& operator[](size_t index);
  const T& operator[](size_t index) const;

  ??? begin();
  ??? end();
  ??? begin() const;
  ??? end() const;

  size_t Size() const;
  size_t Capacity() const;

  void PushBack(const T& value);
  T PopBack();
};
```

The Capacity method should return the capacity of the vector, that is, the number of objects that can in principle fit into it.
-    Size method should return the current number of objects in the vector
-    The constructor takes the size of a vector (similar to a standard vector). If the constructor argument is larger than the vector's capacity, the constructor should throw invalid_argument exception
-    The begin / end methods must return iterators to the beginning and current end of the vector; their type is not specified, you must choose it yourself
-    The PushBack method adds a new element to the end of the vector. If the current size of the vector is equal to its capacity, the PushBack method should throw the standard overflow_error exception
-    The PopBack method decreases the size of the vector by one and returns the last element of the vector. If the vector is empty, the PopBack method should throw the standard underflow_error exception

The StackVector class interface is described in the stack_vector.h file attached to this task. Some of the requirements for it are formulated as unit tests in the stack_vector.cpp file.

Notice how the behavior of the PushBack method in the StackVector class differs from the PushBack method in the SimpleVector class, which you implemented earlier in the block about the memory model. SimpleVector :: PushBack allocated additional memory on the heap if the vector size was equal to the capacity. In the case of the StackVector class, at the compilation stage, we must set the maximum capacity of the vector, and if it is exhausted, we have nowhere else to take memory, and we just throw an exception. This is the disadvantage of implementing a vector on a stack as compared to a regular vector.

On the other hand, the stack_vector.cpp file contains a benchmark that demonstrates the superiority of StackVector over a regular vector. This benchmark simulates the situation when we read the number of objects N from the stream, and then add N objects to the vector using the push_back method (test data is decomposed into vector <vector <int>> to exclude the time required for parsing from the benchmark). When you implement the StackVector pattern, compare its performance to a vector.

Send the header file with the implementation of the StackVector template for verification.
