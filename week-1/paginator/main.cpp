#include "test_runner.h"

#include <numeric>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename Iterator>
class Page {
    Iterator start;
    Iterator finish;
public:
    Page(Iterator begin, Iterator end): start(begin), finish(end)
    {}

    size_t size() const {
        return finish - start;
    }

    auto begin() const
    {
        return start;
    }
    auto end() const
    {
        return finish;
    }

    auto begin()
    {
        return start;
    }
    auto end()
    {
        return finish;
    }
};

// Реализуйте шаблон класса Paginator

template <typename Iterator>
class Paginator {
private:
    Iterator first, last;
    size_t size_of_page;
    vector<Page<Iterator>> pages;
public:
    Paginator(Iterator begin, Iterator end, size_t page_size)
    : first(begin)
    , last(end)
    , size_of_page(page_size)
    {
        if (last - first == 0)
        {

        }
        else
        {
            Iterator start_page = first;
            Iterator end_page = next(first, size_of_page);
            while (last > end_page) {
                pages.push_back({start_page, end_page});
                start_page = end_page;
                end_page = next(end_page, size_of_page);
            }
            pages.push_back({start_page, last});
        }
//        for (auto it = first; it <= last; it + page_size)
//        {
//            pages.push_back(it);
//        }
    }
    // typename vector<Page<Iterator>>::const_iterator
    auto begin() const
    {
        return pages.begin();
    }
    auto end() const
    {
        return pages.end();
    }
    // typename vector<Page<Iterator>>::iterator
    auto begin()
    {
        return pages.begin();
    }
    auto end()
    {
        return pages.end();
    }
    size_t size() const
    {
        return pages.size();
    }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    // Реализуйте этот шаблон функции
    return Paginator
            {
                c.begin(), c.end(), page_size
            };
}
void TestPageCounts() {
  vector<int> v(15);

  ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
  ASSERT_EQUAL(Paginate(v, 3).size(), 5u);
  ASSERT_EQUAL(Paginate(v, 5).size(), 3u);
  ASSERT_EQUAL(Paginate(v, 4).size(), 4u);
  ASSERT_EQUAL(Paginate(v, 15).size(), 1u);
  ASSERT_EQUAL(Paginate(v, 150).size(), 1u);
  ASSERT_EQUAL(Paginate(v, 14).size(), 2u);
}

void TestLooping() {
  vector<int> v(15);
  iota(begin(v), end(v), 1);

  Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
  ostringstream os1;
  for (const auto& page : paginate_v) {
    for (int x : page) {
      os1 << x << ' ';
    }
    os1 << '\n';
  }

  ASSERT_EQUAL(os1.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}

void TestModification() {
  vector<string> vs = {"one", "two", "three", "four", "five"};
  for (auto page : Paginate(vs, 2)) {
    for (auto& word : page) {
      word[0] = toupper(word[0]);
    }
  }

  const vector<string> expected = {"One", "Two", "Three", "Four", "Five"};
  ASSERT_EQUAL(vs, expected);
}

void TestPageSizes() {
  string letters(26, ' ');

  Paginator letters_pagination(letters.begin(), letters.end(), 11);
  vector<size_t> page_sizes;
  for (const auto& page : letters_pagination) {
    page_sizes.push_back(page.size());
  }

  const vector<size_t> expected = {11, 11, 4};
  ASSERT_EQUAL(page_sizes, expected);
}

void TestConstContainer() {
  const string letters = "abcdefghijklmnopqrstuvwxyz";

  vector<string> pages;
  for (const auto& page : Paginate(letters, 10)) {
    pages.push_back(string(page.begin(), page.end()));
  }

  const vector<string> expected = {"abcdefghij", "klmnopqrst", "uvwxyz"};
  ASSERT_EQUAL(pages, expected);
}

void TestPagePagination() {
  vector<int> v(22);
  iota(begin(v), end(v), 1);

  vector<vector<int>> lines;
  for (const auto& split_by_9 : Paginate(v, 9)) {
    for (const auto& split_by_4 : Paginate(split_by_9, 4)) {
      lines.push_back({});
      for (int item : split_by_4) {
        lines.back().push_back(item);
      }
    }
  }

  const vector<vector<int>> expected = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9},
      {10, 11, 12, 13},
      {14, 15, 16, 17},
      {18},
      {19, 20, 21, 22}
  };
  ASSERT_EQUAL(lines, expected);
}

void TestEmpty() {
    vector<int> v(0);
//    cout << v.size() << endl;
    ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
}
void TestOversized() {
    vector <int> v = {1, 2, 3};

    Paginator<vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
    ASSERT_EQUAL(Paginate(v, 6).size(), 1);
}
int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPageCounts);
  RUN_TEST(tr, TestLooping);
  RUN_TEST(tr, TestModification);
  RUN_TEST(tr, TestPageSizes);
  RUN_TEST(tr, TestConstContainer);
  RUN_TEST(tr, TestPagePagination);
  RUN_TEST(tr, TestEmpty);
  RUN_TEST(tr, TestOversized);
//    {
//
//        vector<int> v(15);
//        iota(begin(v), end(v), 1);
//        int value_1 = 4;
//        int value_2 = 2;
//        Paginate(Paginate(v, value_1),value_2);
//    }
}
