#include "test_runner.h"

using namespace std;

template <typename T> class Table {
private:
    vector<vector<T>> table;
public:
    Table(size_t i, size_t j) {
        Resize(i, j);
    }
    vector<T>& operator[](size_t i) {
        return table[i];
    }

    const vector<T>& operator[](size_t i) const {
        return table[i];
    }
    void Resize(size_t new_rows, size_t new_cols) {
        table.resize(new_rows);
        for (auto& item : table) {
            item.resize(new_cols);
        }
    }
    pair<size_t ,size_t> Size() const {
        if (!table.empty() && !table[0].empty()) {
            return {table.size(), table[0].size()}; }
        return {0,0};
    }

};
void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
