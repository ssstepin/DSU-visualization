#ifndef DSU_VISUALIZATION_DSU_H
#define DSU_VISUALIZATION_DSU_H

#include <cassert>
#include <cstdint>
#include <functional>
#include <vector>

namespace DSU {
// Базовая реализация СНМ, без оптимизаций
template <class T> class DSU {
  using Container = std::vector<T>;
  using Index = int64_t;
  using RankType = int64_t;
  using SizeType = size_t;

public:
  using iterator = typename Container::iterator;
  using const_iterator = typename Container::const_iterator;
  using RankContainer = std::vector<RankType>;
  using ParentList = std::vector<Index>;

  DSU() { initMethods(); }

  DSU(SizeType N) : data_(N), parents_(getParents(N)), ranks_(getRanks(N)) {
    initMethods();
  }

  DSU(std::initializer_list<T> list)
      : data_(list), parents_(getParents(data_.size())),
        ranks_(getRanks(data_.size())) {
    initMethods();
  }

  bool empty() const { return data_.empty(); }

  SizeType size() const { return data_.size(); }

  Index add(const T &value) {
    data_.push_back(value);
    Index index = data_.size();
    parents_.push_back(index);
    ranks_.push_back(1);
    return index;
  }

  Index add(T &&value) {
    data_.push_back(std::move(value));
    Index index = data_.size();
    parents_.push_back(index);
    ranks_.push_back(1);
    return index;
  }

  Index find(Index vertex) {
    assert(indexCorrect(vertex));
    return call_find(vertex);
  }

  bool is_connected(Index left_vertex, Index right_vertex) const {
    assert(indexCorrect(left_vertex));
    assert(indexCorrect(right_vertex));
    return find(left_vertex) == find(right_vertex);
  }

  bool is_connected(Index left_vertex, Index right_vertex) {
    assert(indexCorrect(left_vertex));
    assert(indexCorrect(right_vertex));
    return find(left_vertex) == find(right_vertex);
  }

  Index unite(Index left_vertex, Index right_vertex) {
    assert(indexCorrect(left_vertex));
    assert(indexCorrect(right_vertex));
    return call_unite(left_vertex, right_vertex);
  }

  T &operator[](Index index) {
    assert(indexCorrect(index));
    return data_[index];
  }

  const T &operator[](Index index) const {
    assert(indexCorrect(index));
    return data_[index];
  }

  iterator begin() const { return data_.begin(); }

  iterator end() const { return data_.end(); }

  const_iterator cbegin() const { return data_.cbegin(); };

  const_iterator cend() const { return data_.cend(); }

  void enable_find_euristic() {
    find_function_ = ackermann_path_euristic;
  }

  void enable_union_euristic() {
    union_function_ = rank_union_euristic;
  }

  void disable_find_euristic() {
    find_function_ = default_find;
  }

  void disable_union_euristic() {
    union_function_ = default_union;
  }
private:
  using FindFunction = std::function<Index(Index, ParentList &)>;
  using UnionFunction = std::function<Index(
      Index, Index, ParentList &, RankContainer &, const FindFunction &)>;

  static ParentList getParents(size_t N) {
    ParentList parents(N);
    for (Index i = 0; i < N; ++i) {
      parents[i] = i;
    }
    return parents;
  }

  static RankContainer getRanks(size_t N) {
    RankContainer ranks(N);
    for (Index i = 0; i < N; ++i) {
      ranks[i] = 1;
    }
    return ranks;
  }

  void initMethods() {
    find_function_ = default_find;
    union_function_ = default_union;
  }

  bool indexCorrect(Index index) const {
    return (index >= 0) && (index < data_.size());
  }

  Index get_parent(Index vertex) const { return parents_[vertex]; }

  static Index default_find(Index vertex, ParentList &parents) {
    Index current;
    while ((current = parents[vertex]) != vertex) {
      vertex = current;
    }
    return current;
  }

  static Index ackermann_path_euristic(Index vertex, ParentList &parents) {
    if (parents[vertex] != vertex) {
      return parents[vertex] = ackermann_path_euristic(vertex, parents);
    }
    return vertex;
  }

  static Index default_union(Index left_vertex, Index right_vertex,
                             ParentList &parents, RankContainer &ranks,
                             const FindFunction &find_func) {
    Index left_parent = find_func(left_vertex, parents);
    Index right_parent = find_func(right_vertex, parents);
    if (left_parent == right_parent) {
      return left_parent;
    }
    ranks[right_parent] += ranks[left_parent];
    return parents[left_parent] = right_parent;
  }

  static Index rank_union_euristic(Index left_vertex, Index right_vertex,
                                   ParentList &parents, RankContainer &ranks,
                                   const FindFunction &find_func) {
    Index left_parent = find_func(left_vertex, parents);
    Index right_parent = find_func(right_vertex, parents);
    if (left_parent == right_parent) {
      return left_parent;
    }
    if (ranks[left_parent] < ranks[right_parent]) {
      ranks[right_parent] += ranks[left_parent];
      return parents[left_parent] = right_parent;
    }
    ranks[left_parent] += ranks[right_parent];
    return parents[right_parent] = left_parent;
  }

  Index call_find(Index vertex) { return find_function_(vertex, parents_); }

  Index call_unite(Index left_vertex, Index right_vertex) {
    return union_function_(left_vertex, right_vertex, parents_, ranks_,
                           find_function_);
  }

  Container data_;
  ParentList parents_;
  RankContainer ranks_;

  FindFunction find_function_;
  UnionFunction union_function_;
};
} // namespace DSU
#endif // DSU_VISUALIZATION_DSU_H
