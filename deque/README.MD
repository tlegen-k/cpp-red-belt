## C++ Red belt
This repository contains my solutions to tasks from week 1 of [C++ course](https://www.coursera.org/learn/c-plus-plus-yellow/home/welcome)

### Deque on two vectors

Write a templated Deque class containing the following set of methods:

- default constructor;
- a constant method Empty that returns true if the deck contains no elements;
- constant method Size that returns the number of elements in the deck;
- T & operator [] (size_t index) and const T & operator [] (size_t index) const;
- constant and non-constant method At (size_t index), which throws the standard out_of_range exception if the index is greater than or equal to the number of elements in the deck;
- constant and non-constant versions of the Front and Back methods, which return references to the first and last elements of the deck, respectively;
- methods PushFront and PushBack.

Non-const versions of methods must allow the corresponding element of the deck to be modified.

For implementation, put two vectors inside the Deque class: insert into one in the PushFront method, and in the other, in the PushBack method.
### Comment
The header file that you send for verification should not include files <list>, <deque>, <set>, <map>. If you have one of these files included, you will receive a compilation error.
