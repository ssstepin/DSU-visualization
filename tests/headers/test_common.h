#ifndef TEST_TEST_COMMIN_H
#define TEST_TEST_COMMIN_H

#include <cassert>
#include <cstdint>
#include <stack>
#include <unordered_set>
#include <vector>

namespace DSUTest::Testcommon {
struct TestData {
  size_t val;

  TestData() = default;

  TestData(size_t x) : val(x) {}

  bool operator==(const TestData &other) const {
    return this->val == other.val;
  }
};

template <class T> class TestGraph {
  using Index = int64_t;
  using Container = std::vector<T>;
  using AdjList = std::vector<std::unordered_set<Index>>;

public:
  using ConnectedList = std::unordered_set<Index>;
  using VertexList = std::vector<Index>;

  TestGraph(size_t N) : data(N), adj_list(N) {}

  TestGraph(const std::vector<T> &container)
      : data(container), adj_list(container.size()) {}

  size_t size() { return data.size(); }

  void add_edge(Index left_vertex, Index right_vertex) {
    assert(indexCorrect(left_vertex));
    assert(indexCorrect(right_vertex));
    assert(edgeCorrect(left_vertex, right_vertex));
    adj_list[left_vertex].insert(right_vertex);
    adj_list[right_vertex].insert(left_vertex);
  }

  bool has_edge(Index left_vertex, Index right_vertex) {
    assert(indexCorrect(left_vertex));
    assert(indexCorrect(right_vertex));
    assert(edgeCorrect(left_vertex, right_vertex));
    return is_adj(left_vertex, right_vertex);
  }

  ConnectedList get_connected(Index vertex) {
    assert(indexCorrect(vertex));
    return adj_list[vertex];
  }

  VertexList subtree(Index vertex) {
    assert(indexCorrect(vertex));
    return DFS(vertex);
  }

private:
  Container data;
  AdjList adj_list;

  bool is_adj(Index left_vertex, Index right_vertex) {
    return adj_list[left_vertex].find(right_vertex) !=
           adj_list[left_vertex].end();
  }

  bool indexCorrect(Index index) {
    return (index >= 0) && (index < data.size());
  }

  bool edgeCorrect(Index left_vertex, Index right_vertex) {
    return is_adj(left_vertex, right_vertex) ==
           is_adj(right_vertex, left_vertex);
  }

  // Да, DFS тут на стеке, а не рекурсией
  using DFSStack = std::stack<Index>;
  using DFSUseList = std::vector<bool>;

  VertexList DFS(Index vertex) {
    DFSStack stack;
    DFSUseList used(data.size());
    VertexList dfs_result;
    stack.push(vertex);
    while (!stack.empty()) {
      Index current_vertex = stack.top();
      used[current_vertex] = true;
      dfs_result.push_back(current_vertex);
      stack.pop();
      for (Index next_vertex : get_connected(current_vertex)) {
        if (!used[next_vertex]) {
          stack.push(next_vertex);
        }
      }
    }
    return dfs_result;
  }
};

template <class T> std::vector<T> GenerateSample(size_t N) {
  std::vector<T> sample(N);
  for (size_t i = 0; i < N; ++i) {
    sample[i] = T(i);
  }
  return sample;
}

template <class T> void CheckNoEdges(const DSU::DSU<T> &dsu) {
  for (size_t i = 0; i < dsu.size(); ++i) {
    assert(dsu.find(i) == i);
  }
}

template <class T>
void CheckData(const DSU::DSU<T> &dsu, const std::vector<T> &data) {
  for (size_t i = 0; i < data.size(); ++i) {
    assert(data[i] == dsu[i]);
  }
}

template <class T> void CheckCompleteGraph(const DSU::DSU<T> &dsu) {
  size_t N = dsu.size();
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      assert(dsu.is_connected(i, j));
    }
  }
}
} // namespace DSUTest::Testcommon

#endif // TEST_TEST_COMMIN_H
