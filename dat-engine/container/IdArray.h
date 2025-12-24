#pragma once

#include <algorithm>
#include <vector>

namespace DatEngine {
    /**
     * A list structure that provides ID values for inserted objects that are guaranteed to remain valid until the item is
     * removed. Arbitrary removals are allowed, where gaps are tracked and filled in with new insertions.
     *
     * @tparam TValue The type of the values stored in the IdArray
     */
    template<typename TValue>
    class IdQueue {
        /**
         * The type of the value stored in the backing vector
         *
         * This is a union to allow storing an index that, for removed items, points to the next available index after this
         * one.
         */
        using TValue = union {
            size_t nextIndex{};
            TValue value;
        };

        /** The next available ID in the list */
        size_t nextId = 0;
        /** The backing vector storing the values */
        std::vector<TValue> values;

        /**
         * Handle inserting a value into the next available slot when it is into a removed value
         *
         * @param value The value to insert
         * @return The index of the inserted value
         */
        size_t handleInnerInsert(TValue value) {
            size_t id = nextId;
            nextId = values.at(id).nextIndex;

            values[id] = value;
            return id;
        }

    public:
        IdQueue() = default;
        IdQueue(const IdQueue& other) = default;
        IdQueue(IdQueue&& other) = default;

        /**
         * Get a value from the IdQueue by its ID
         *
         * @param id The id of the value to get
         * @return The value with the given ID
         */
        TValue& get(size_t id) const { return values.at(id).value; }

        //   Brackets
        TValue& operator[](size_t id) const { return values.at(id).value; }

        /**
         * Insert a value into the IdQueue
         *
         * @param value The value to insert
         * @return The ID of the inserted value for retrieval
         */
        size_t pushBack(TValue value) {
            if (nextId < values.size())
                return handleInnerInsert(value);

            values.push_back(value);
            return nextId++;
        }

        /**
         * Emplace a value in the IDQueue
         *
         * @tparam Args The types of the arguments to pass to the value constructor
         * @param args The arguments to pass to the value constructor
         * @return The ID of the emplaced value
         */
        template<typename... Args>
        size_t emplaceBack(Args&&... args) {
            if (nextId < values.size())
                return handleInnerInsert(TValue(std::forward<Args>(args)...));

            values.emplace_back(std::forward<Args>(args)...);
            return nextId++;
        }

        /**
         * Remove a value from the IdQueue
         *
         * This does not check if the id is present, therefore carelessness can lead to values removed multiple times and
         * circular dependencies in the nextId chain.
         *
         * @param id The id of the value to remove
         */
        void remove(size_t id) {
            values[id] = nextId;
            nextId = id;
        }

        /**
         * Pack the IdQueue into the smallest array that fits it
         *
         * This method does not compact the IDs together, as IDs are guaranteed to remain constant. This method instead
         * chops unused IDs off the end of the array.
         */
        void pack() {
            // Convert chain of nextIds into list
            std::vector<size_t> indices;
            size_t id = nextId;
            while (id != values.size()) {
                indices.push_back(id);
                id = values.at(id).nextIndex;
            }

            // Sort bigger to smaller
            std::ranges::sort(indices, std::ranges::greater());

            // Find the minimum size the nextId can be by iterating through the sorted indices until there is a gap between
            // indices that is greater than 1 (I.e, a jump over currently used indices)
            size_t maxIndex = indices.front();
            while (maxIndex < indices.size() - 1 && indices[maxIndex] == indices[maxIndex + 1] + 1)
                ++maxIndex;
            values.resize(indices[maxIndex]);

            // Adjust nextId chain. This works because the indices list is sorted and will have the side effect of sorting
            // the next chain
            for (int i = maxIndex + 1; i < indices.size(); ++i) {
                values[indices[i]] = indices[i - 1];
            }
            nextId = indices.back();

            // Attempt to shrink the vector to the new size
            values.shrink_to_fit();
        }
    };
}
