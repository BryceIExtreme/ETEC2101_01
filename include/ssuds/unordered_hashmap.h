#pragma once

#include <iostream>
#include <functional>
#include <string>

namespace ssuds
{
    template <typename K, typename V>
    class UnorderedHashMap
    {
    private:
        struct KeyValuePair {
            K key;
            V value;
            bool is_occupied;

            KeyValuePair() : is_occupied(false) {}
        };

        KeyValuePair* table;
        unsigned int mCapacity;
        unsigned int mSize;
        float load_factor;

        unsigned int hash(const K& key) const {
            return std::hash<K>{}(key) % mCapacity;
        }

        void grow() {
            mCapacity *= 2;
            KeyValuePair* new_table = new KeyValuePair[mCapacity];

            for (unsigned int i = 0; i < mCapacity / 2; ++i) {
                if (table[i].is_occupied) {
                    unsigned int index = hash(table[i].key);
                    while (new_table[index].is_occupied) {
                        index = (index + 1) % mCapacity;
                    }
                    new_table[index] = table[i];
                }
            }

            delete[] table;
            table = new_table;
        }

    public:
        UnorderedHashMap(unsigned int initial_mCapacity = 16, float load_factor = 0.75)
            : mCapacity(initial_mCapacity), mSize(0), load_factor(load_factor)
        {
            table = new KeyValuePair[mCapacity];
        }

        ~UnorderedHashMap()
        {
            delete[] table;
        }

        friend std::ostream& operator<<(std::ostream& os, const UnorderedHashMap& map)
        {
            os << "{";
            bool first = true;
            for (unsigned int i = 0; i < map.mCapacity; ++i) {
                if (map.table[i].is_occupied) {
                    if (!first) {
                        os << ", ";
                    }
                    os << map.table[i].key << ":" << map.table[i].value;
                    first = false;
                }
            }
            os << "}";
            return os;
        }

        V& operator[](const K& key)
        {
            if (mSize >= mCapacity * load_factor)
            {
                grow();
            }

            unsigned int index = hash(key);
            while (table[index].is_occupied && table[index].key != key)
            {
                index = (index + 1) % mCapacity;
            }

            if (!table[index].is_occupied)
            {
                table[index].key = key;
                table[index].is_occupied = true;
                ++mSize;
            }

            return table[index].value;
        }


        bool contains(const K& key) const
        {
            unsigned int index = hash(key);
            while (table[index].is_occupied)
            {
                if (table[index].key == key)
                {
                    return true;
                }
                index = (index + 1) % mCapacity;
            }
            return false;
        }

        bool remove(const K& key)
        {
            unsigned int index = hash(key);
            while (table[index].is_occupied)
            {
                if (table[index].key == key)
                {
                    table[index].is_occupied = false;
                    --mSize;
                    return true;
                }
                index = (index + 1) % mCapacity;
            }
            return false;
        }

        unsigned int get_size() const {
            return mSize;
        }

        class Iterator {
        private:
            const UnorderedHashMap& map;
            unsigned int index;

        public:
            Iterator(const UnorderedHashMap& map, unsigned int index) : map(map), index(index) {}

            bool operator!=(const Iterator& other) const {
                return index != other.index;
            }

            const KeyValuePair& operator*() const {
                return map.table[index];
            }

            Iterator& operator++() {
                do {
                    ++index;
                } while (index < map.mCapacity && !map.table[index].is_occupied);
                return *this;
            }
        };

        Iterator begin() const {
            unsigned int index = 0;
            while (index < mCapacity && !table[index].is_occupied) {
                ++index;
            }
            return Iterator(*this, index);
        }

        Iterator end() const
        {
            return Iterator(*this, mCapacity);
        }

    };
}

