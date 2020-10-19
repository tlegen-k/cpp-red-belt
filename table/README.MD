## C++ Red belt
This repository contains my solutions to tasks from week 1 of [C++ course](https://www.coursera.org/learn/c-plus-plus-yellow/home/welcome)

### Table

You need to write a templated Table class for the spreadsheet. For simplicity, we will assume that all table cells have the same data type T. The table must be able to change its size at the user's request. Newly created cells should be filled with default values ​​of type T.

The class requirements are as follows:

- The class must be named Table.
- The class must have a template parameter T - the type of the element in the cell.
- The class must have a constructor that receives two numbers of size_t type as input - the number of rows and columns, respectively.
- The class must have a constant and a non-constant version of the [] operator, which returns something to which the [] operator can be applied again. That is, constructions like cout << table [i] [j]; and table [i] [j] = value; should work. You do not need to check the correctness of the indexes.
- The class must have a Resize function that receives two parameters of type size_t as input and resizes the table. The old data that fits into the new size should be preserved.
- The class must have a constant function Size that returns pair <size_t, size_t> - the size of the table (in the same order in which these arguments were passed to the constructor). Moreover, if the table Table has one of the sizes zero, then it is necessary to consider the second table size as such.
