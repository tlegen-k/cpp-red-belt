#pragma once

#include <cstdlib>
#include <algorithm>
template <typename T>
class SimpleVector {
public:
    SimpleVector() : begin_(nullptr), size_(0), capacity_(0)
    {}

    explicit SimpleVector(size_t size) : begin_(new T[size]), size_(size),
    capacity_(size)
    {}

    ~SimpleVector()
    {
        delete [] begin_;
    }

    T& operator[](size_t index)
    {
        return *(begin_ + index);
    }

    T* begin() { return begin_;}

    T* end() { return (begin_ + size_);}

    //- Return number of elements
    size_t Size() const { return size_; }

    //- Number of elements that will fit in memory occupied by vector
    size_t Capacity() const { return capacity_; }

    void PushBack(const T& value)
    {
        if (capacity_ == 0) {
            begin_ = new T[1];
            *begin_ = value;
            ++capacity_;
            size_ = 1;
        } else {
            if (Size() == Capacity()) {
                capacity_ *= 2;
                T* new_vector = new T[capacity_];
                std::copy(begin(), end(), new_vector);
                delete [] begin_;
                begin_ = new_vector;
            }
            begin_[size_] = value;
            ++size_;
        }

    }

private:
    T* begin_;
    size_t size_;
    size_t  capacity_;
};
