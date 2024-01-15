#ifndef TESTS_TEST_LIGHT_H
#define TESTS_TEST_LIGHT_H

#include "dsu.h"
#include "test_common.h"

namespace DSUTest {
    using namespace Testcommon;
    namespace LightTests {

        using TestData = DSUTest::TestData;
        using Graph = DSUTest::TestGraph<TestData>;
        using TestDSU = DSU::DSU<TestData>;

        void test_simple_with_three_nodes();
    }
}
#endif //TESTS_TEST_LIGHT_H
