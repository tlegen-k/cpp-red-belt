## Own vector
Condition

In the lectures, we have already begun to implement our vector. In this task, you need to develop it: add the Size, Capacity and PushBack methods. Send for review the header file simple_vector.h containing the declaration and definition of the SimpleVector class template:
Requirements:

- the Capacity method should return the current capacity of the vector - the number of elements that fit into the memory block currently allocated by the vector
- the Size method should return the number of elements in the vector
- the PushBack method adds a new element to the end of the vector; if there is no free space left in the current allocated block of memory (i.e. Size () == Capacity ()), the vector should allocate a block of size 2 * Capacity (), copy all elements into it and delete the old one.
- the first call to the PushBack method for the newly created object should make the capacity equal to one
- the PushBack method must have amortized constant complexity
- the begin and end methods must return iterators at the current start and end of the vector
- in the destructor, the current block of memory allocated by the vector must be released
- also see additional requirements for running SimpleVector in unit tests in the attached solution template
