#include "test_light.h"
#include "dsu.h"
#include "test_common.h"

namespace DSUTest {
namespace LightTests {
using TestData = DSUTest::Testcommon::TestData;
using Graph = DSUTest::Testcommon::TestGraph<TestData>;
using TestDSU = DSU::DSU<TestData>;

void test_simple_with_three_nodes() {
  static constexpr size_t N = 3;

  TestDSU dsu({{0}, {1}, {2}});

  assert(dsu.size() == N);
  Testcommon::CheckData<TestData>(dsu, {{0}, {1}, {2}});
  Testcommon::CheckNoEdges<TestData>(dsu);

  dsu.unite(0, 1);
  assert(dsu.is_connected(0, 1));
  dsu.unite(1, 2);
  CheckCompleteGraph(dsu);
}

void test_simple_euristics() {
  {
    static constexpr size_t N = 3;

    TestDSU dsu({{0}, {1}, {2}});
    dsu.enable_find_euristic();

    assert(dsu.size() == N);
    Testcommon::CheckData<TestData>(dsu, {{0}, {1}, {2}});
    Testcommon::CheckNoEdges<TestData>(dsu);

    dsu.unite(0, 1);
    assert(dsu.is_connected(0, 1));
    dsu.disable_find_euristic();
    assert(dsu.is_connected(0, 1));
    dsu.unite(1, 2);
    CheckCompleteGraph(dsu);
  }

  {
    static constexpr size_t N = 3;

    TestDSU dsu({{0}, {1}, {2}});
    dsu.enable_union_euristic();

    assert(dsu.size() == N);
    Testcommon::CheckData<TestData>(dsu, {{0}, {1}, {2}});
    Testcommon::CheckNoEdges<TestData>(dsu);

    dsu.unite(0, 1);
    assert(dsu.is_connected(0, 1));
    dsu.unite(1, 2);
    CheckCompleteGraph(dsu);
  }
}
} // namespace LightTests
} // namespace DSUTest
