#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) \
do {                            \
out << (x) << endl;             \
out << (y) << endl;             \
}                               \
while (0)

void TestOutput() {
    ostringstream output;
    int x = 10;
    PRINT_VALUES(output, x++, x);
    output.str();
    cout << output.str();
    ASSERT_EQUAL(output.str(), "11\n10\n");
}
void TestIf() {
    ostringstream output;
    if (true)
        PRINT_VALUES(output, 5, "red belt");
    else
        PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
}
int main() {
    TestRunner tr;
    tr.RunTest([] {
        ostringstream output;
        PRINT_VALUES(output, 5, "red belt");
        ASSERT_EQUAL(output.str(), "5\nred belt\n");
    }, "PRINT_VALUES usage example");
    RUN_TEST(tr,TestOutput);
    RUN_TEST(tr, TestIf);
}
