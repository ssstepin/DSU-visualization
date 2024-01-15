#include "test_light.h"

using namespace DSUTest;

void LightTests::test_simple_with_three_nodes() {
  static const size_t N = 3;
  auto sample = GenerateSample<TestData>(N);
  TestDSU dsu(sample);

  assert(dsu.size() == N);
  CheckData<TestData>(dsu, sample);
  CheckNoEdges<TestData>(dsu);

  dsu.unite(0, 1);
  assert(dsu.is_connected(0, 1));
  dsu.unite(1, 2);
  CheckCompleteGraph(dsu);
}