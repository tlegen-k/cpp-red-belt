#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate()
    {
        T* tmp = nullptr;
        if (!realesed.empty())
        {
            tmp = realesed.front();
            allocated.insert(tmp);
            realesed.pop();
            return tmp;
        }

        else
        {
            T* pNew = new T;
            allocated.insert(pNew);
            return  pNew;
        }
    }
    T* TryAllocate()
    {
        if (realesed.empty())
        {
            return nullptr;
        }
        else
        {
            return Allocate();
        }
    }

    void Deallocate(T* object)
    {
        auto it = allocated.find(object);
        if (it == allocated.end())
        {
            throw invalid_argument("No object");
        }
        else
        {
            realesed.push(object);
            allocated.erase(it);
        }
    }

    ~ObjectPool()
    {
        for_each(allocated.begin(), allocated.end(), [](T* obj){ delete obj; });

        while( !realesed.empty())
        {
            T* tmp = realesed.front();
            delete tmp;
            realesed.pop();
        }
    }

private:
    queue<T*> realesed;
    set<T*> allocated;
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
