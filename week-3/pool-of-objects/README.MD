## Pool of objects
In practice, there are often objects that take a long time to create, such as threads, TCP connections, or database connections. Therefore, when such an object becomes unnecessary, it is not destroyed, but put aside to be reused later. In this task, you have to implement the following scheme - you need to write a template for the ObjectPool class:
```cpp
template <class T>
class ObjectPool {
public:
  T* Allocate();
  T* TryAllocate();

  void Deallocate(T* object);

  ~ObjectPool();

private:
  ...
};
```
- An object of the ObjectPool class must support two sets of objects: allocated and released, - initially both sets are empty.
- The Allocate method should work like this:

1. if there is at least one freed object, then it must be transferred to the set of allocated objects and a pointer to it must be returned as the result of the function
2. if there are no freed objects, then a new object is created, placed in the set of allocated ones, and a pointer to it is returned as the result of the function

- The TryAllocate method works the same way, but if there are no freed objects, it should simply return nullptr.
- The Deallocate method transfers an object from the set of allocated to the set of released; if the passed object is not contained in the allocated set, the Deallocate method should throw an invalid_argument exception.
- The Allocate and TryAllocate methods must return objects in FIFO order, i.e. the set of freed objects must be a queue: the [Try] Allocate methods must retrieve objects from its beginning, and the Deallocate method must place the freed object at the end of it.
- The ObjectPool object's destructor must destroy all objects in the pool, both allocated and freed.
