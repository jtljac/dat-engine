/*
* Inspired by Skypjack's blogs: https://skypjack.github.io/2019-03-07-ecs-baf-part-2/
*/

#pragma once

#include <cstdint>
#include <vector>

#include <util/type-traits.h>
namespace DatEngine {
    /**
     * An integer key map implementation that uses a Sparse Set to pack entries
     *
     * @tparam TValue The type of the value stored in the sparse set
     * @tparam TKey The type of the key, must be an integral type
     */
    template <typename TValue, uIntegral TKey = uint32_t>
    struct SparseMap {
        using sparseType = TKey;
        using denseType = std::pair<TKey, TValue>;
    protected:
        std::vector<sparseType> sparse;
        std::vector<denseType> dense;
    public:
        void insert(const TKey key, const TValue value) {
            if (sparse.size() < key) sparse.resize(key + 1);
            sparse[key] = size();
            dense.push_back(std::make_pair(std::move(key), std::move(value)));
        }

        template <typename ...Args>
        void emplace(const TKey key, Args&&... args) {
            if (sparse.size() < key) sparse.resize(key + 1);
            sparse[key] = size();
            dense.emplace_back(std::piecewise_construct, std::forward_as_tuple(key), std::forward_as_tuple(args...));
        }

        // remove
        void remove(const TKey key) {
            assert(key < sparse.size());

            // Special case
            if (size() == 1) {
                dense.pop_back();
                return;
            }

            denseType& value = dense[key];
            value = std::move(dense.back());
            sparse[value.first] = key;

            dense.pop_back();
        }

        void swap(const TKey key1, const TKey key2) {
            assert(key1 < sparse.size());
            assert(key2 < sparse.size());

            TKey& sparseKey1 = sparse[key1];
            TKey& sparseKey2 = sparse[key2];
            denseType& value1 = dense[sparseKey1];
            denseType& value2 = dense[sparseKey2];

            TKey tempSparse = std::move(sparseKey1);
            denseType tempDense = std::move(value1);

            sparseKey1 = std::move(sparseKey2);
            sparseKey2 = std::move(tempSparse);

            value1 = std::move(value2);
            value2 = std::move(tempDense);
        }

        // contains
        bool contains(const TKey key) {
            return key < sparse.size() && dense.at(sparse.at(key)).first == key;
        }

        // get
        TValue* get(TKey key) {
            if (key < sparse.size()) return nullptr;

            auto& pair = dense.at(sparse.at(key));

            return pair.first == key
                    ? &pair.second
                    : nullptr;
        }

        // Size
        TKey size() {
            return dense.size();
        }

        // clear
        void clear() {
            // We only need to clear dense, this invalidates sparse
            dense.clear();
        }

        // iterator methods
        auto begin() {
            return dense.begin();
        }
        auto end() {
            return dense.end();
        }

        auto cbegin() {
            return dense.cbegin();
        }
        auto cend() {
            return dense.cend();
        }

        auto rbegin() {
            return dense.rbegin();
        }
        auto rend() {
            return dense.rend();
        }
    };
}