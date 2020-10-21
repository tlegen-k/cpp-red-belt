#include <iostream>
#include <vector>
#include <stdexcept>
//#include "test_runner.h"
using namespace std;

template<typename T> class Deque
{
private:
    vector<T> front;
    vector<T> back;
public:
    //- Default constructor
    Deque() {  }
    //- Access Deque element through reference
    T& operator[](size_t i) {
        if (i < front.size()) {
            return front[front.size() - i - 1];
        }
        else {
            return back[i - front.size()];
        }
    }
    //- Access Deque element through const reference
    const T& operator[](size_t i) const {
        if (i < front.size()) {
            return front[front.size() - i - 1];
        }
        else {
            return back[i - front.size()];
        }
    }
    //- Return the emptiness of Deque
    bool Empty() const {
        return (front.empty() && back.empty());
    }

    //- Return reference to element at given index in Deque
    T& At(size_t index ) {
        if (index > Size()) {
            throw out_of_range("Index is out of range");
        }
        if (index < front.size()) {
            return front[front.size() - index - 1];
        }
        else {
            return back[index - front.size()];
        }
    }
    //- Return const reference to element at given index in Deque
    const T& At(size_t index) const {
        if (index > Size()) {
            throw out_of_range("Index is out of range");
        }
        if (index < front.size()) {
            return front[front.size() - index - 1];
        }
        else {
            return back[index - front.size()];
        }
    }

    //- Return reference to the first element in Deque
    T& Front( ) {
        if (front.empty()) {
            return back.front();
        }
        else {
            return front.back();
        }
    }

    //- Return const reference to the first element in Deque
    const T& Front() const {
        if (front.empty()) {
            return back.front();
        }
        else {
            return front.back();
        }

    }

    //- Return reference to the last element in Deque
    T& Back() {
        if (back.empty()) {
            return front.front();
        }
        else {
            return back.back();
        }
    }

    //- Return const reference to the last element in Deque
    const T& Back() const {
        if (back.empty()) {
            return front.front();
        }
        else {
            return back.back();
        }
    }

    //- Add element to the beginning of Deque
    void PushFront(const T& item) {
        front.push_back(item);
    }

    //- Add element to the end of Deque
    void PushBack(const T& item) {
        back.push_back(item);
    }

    //- Return size of Deque
    int Size() const {
        return (front.size() + back.size());
    }

};

int main() {
    {
        Deque<int> d1;
        d1.PushFront(3);
        d1.PushFront(2);
        d1.PushFront(1);
        d1.PushBack(4);
        d1.PushBack(5);
        d1.PushBack(6);
    //    cout << "Size of Deque: " << d1.Size() << endl;
    //    cout << d1.At(5) << endl;
        for (int i =0 ; i < d1.Size(); i++) {
            cout << d1.At(i) << endl;
        }
    //    cout << "Front of Deque: " << d1.Front() << endl;
    //    cout << "Back of Deque: " << d1.Back() << endl;
//        return 0;
    }
    {
        Deque<int> d2;
        d2.PushFront(3);
        d2.PushFront(2);
        d2.PushFront(1);
        cout << d2.Back() << endl;
    }
    {
        Deque<int> d3;
        d3.PushBack(1);
        d3.PushBack(2);
        d3.PushBack(3);
        cout << d3.Front() << endl;
    }
    return 0;
}
