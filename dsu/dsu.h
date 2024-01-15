#ifndef DSU_VISUALIZATION_DSU_H
#define DSU_VISUALIZATION_DSU_H

#include <cassert>
#include <cstdint>
#include <vector>

namespace DSU {
// Базовая реализация СНМ, без оптимизаций
    template<class T>
    class DSU {
        using Container = std::vector<T>;
        using ParentList = std::vector<size_t>;

    public:
        using iterator = typename Container::iterator;
        using const_iterator = typename Container::const_iterator;

        using Index = int64_t;

        DSU() = default;

        DSU(size_t N) : data_(N), parents_(N) {
            fillParents(N);
        };

        DSU(const std::vector<T> &container) : data_(container), parents_(container.size()) {
            fillParents(container.size());
        }

        bool empty() const {
            return data_.empty();
        }

        size_t size() const {
            return data_.size();
        }

        Index add(const T &value) {
            data_.push_back(value);
            Index index = data_.size();
            parents_.push_back(index);
            return index;
        }

        Index find(Index vertex) const {
            assert(indexCorrect(vertex));
            Index current = vertex;
            while ((current = get_parent(vertex)) != vertex) {
                vertex = current;
            }
            return current;
        }

        bool is_connected(Index left_vertex, Index right_vertex) const {
            assert(indexCorrect(left_vertex));
            assert(indexCorrect(right_vertex));
            return find(left_vertex) == find(right_vertex);
        }

        Index unite(Index left_vertex, Index right_vertex) {
            assert(indexCorrect(left_vertex));
            assert(indexCorrect(right_vertex));
            return parents_[left_vertex] = parents_[right_vertex];
        }


        T &operator[](Index index) {
            assert(indexCorrect(index));
            return data_[index];
        }

        const T &operator[](Index index) const {
            assert(indexCorrect(index));
            return data_[index];
        }

        iterator begin() const {
            return data_.begin();
        }

        iterator end() const {
            return data_.end();
        }

        const_iterator cbegin() const {
            return data_.cbegin();
        };

        const_iterator cend() const {
            return data_.cend();
        }

    private:
        Container data_;
        ParentList parents_;

        void fillParents(size_t N) {
            for (size_t i = 0; i < N; ++i) {
                parents_[i] = i;
            }
        }

        bool indexCorrect(Index index) const {
            return (index >= 0) && (index < data_.size());
        }

        Index get_parent(Index vertex) const {
            return parents_[vertex];
        }
    };
}
#endif //DSU_VISUALIZATION_DSU_H
