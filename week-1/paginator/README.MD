## Template Paginator
In the lesson, we developed the Head function that allows you to loop through the for loop at the beginning of the container. In this task, we will take a step forward and develop a Paginator template that splits the contents of a container into multiple pages. A classic example of when this can be useful in practice is the distribution of the list of mobile applications across phone screens. Let's say we have a vector of all applications on our phone and we can place 20 application icons on one screen. Then we can distribute applications across screens with the following code:
```cpp
vector<vector<Application>> DistributeAmongScreens(const vector<Application>& apps) {
  vector<vector<Application>> result;
  for (const auto& page : Paginate(apps, 20)) {
    result.push_back({page.begin(), page.end()});
  }
  // result[0] - all apps on 1st screen,
  // result[1] - all apps on 2nd screen, etc.
  return result;
}
```
Note that our code is short and elegant. We didn't have to write any separate code to handle the final screen, which can contain fewer than 20 apps.

So, design a Paginator class template with the following properties:

- it has one templated parameter - the iterator type
- the constructor of the Paginator <Iterator> class takes three parameters:

1. Iterator begin
2. Iterator end - a pair of begin and end iterators specify a half-interval [begin; end), which we will slice into pages
3. size_t page_size - size of one page

- objects of the Paginator <Iterator> class can be iterated over using a range-based for loop
- the Paginator <Iterator> class has a size_t size () const method that returns the number of pages into which the passed container has been split
- the pages themselves must also support iteration using range-based for and have a size_t size () const method that returns the number of objects in this page
- for detailed examples of use, see unit tests in the solution template

Also, design a Paginate function template that takes a container reference and page size and returns a Paginator <It> object:
```cpp
template <typename C> ??? Paginate(C& c, size_t page_size)
```
