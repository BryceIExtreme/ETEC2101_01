#pragma once

#include <iostream>
#include <functional>
#include <string>

namespace ssuds
{
    /// <summary>
    /// This kind of structure takes a value V and associates it with a key K that we use a has to essentially jumble
    /// </summary>
    /// <typeparam name="K"></typeparam>
    /// <typeparam name="V"></typeparam>
    template <typename K, typename V>
    class UnorderedHashMap
    {
    private:
        struct KeyValuePair {

            /// <summary>
            /// Value and key kinda go together, a key is tied to a value, 
            /// a value is tied to a key 
            /// and they cannot exist without each other
            /// </summary>
            K key;
            V value;
            bool is_occupied; //Tells us whether a slot is occupado

            KeyValuePair() : is_occupied(false) {}
        };

        KeyValuePair* table; //The table storing key-value pairs
        unsigned int mCapacity; //The max ammount allowed in the hash table before we grow it
        unsigned int mSize; //the number of elements in the table
        float load_factor; //Maximum load factor before resizing

        /// <summary>
        /// The hash computer where we give it a ket and we get back a hash value
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
        unsigned int hash(const K& key) const {
            return std::hash<K>{}(key) % mCapacity;
        }

        /// <summary>
        /// If we reach the max amount of capacity we use this to instantly increase out space by double after creating a new table
        /// and copying all the information over
        /// </summary>
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

        /// <summary>
        /// Our initial setup function
        /// </summary>
        /// <param name="initial_mCapacity"></param>
        /// <param name="load_factor"></param>
        UnorderedHashMap(unsigned int initial_mCapacity = 16, float load_factor = 0.75)
            : mCapacity(initial_mCapacity), mSize(0), load_factor(load_factor)
        {
            table = new KeyValuePair[mCapacity];
        }

        /// <summary>
        /// The standard deconstructor which destroys every part of the table
        /// </summary>
        ~UnorderedHashMap()
        {
            delete[] table;
        }

        /// <summary>
        /// Our friendly stream operator which allows to actually print the values in the map 
        /// </summary>
        /// <param name="os"></param>
        /// <param name="map"></param>
        /// <returns></returns>
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


        /// <summary>
        /// Accesses or inserts a value with a given key.
        /// if the key doesnt exist then we create a new value with the default
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
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

        /// <summary>
        /// Checks if the table contains the value by the key given that alligns with it
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
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

        /// <summary>
        /// Removes a key-value pair from the map via an index we feed it
        /// if it does remove it, we get back true
        /// if we dont find it, then we get false
        /// </summary>
        /// <param name="key"></param>
        /// <returns></returns>
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

        /// <summary>
        /// Gets the number of elements in the hash map
        /// </summary>
        /// <returns></returns>
        unsigned int get_size() const {
            return mSize;
        }

        class Iterator {
        private:
            const UnorderedHashMap& map; //Hashmap being traversed
            unsigned int index; //Current index in the hash table

        public:

            /// <summary>
            /// Like with all other labs, we needed an iterator to manually go through values in a glob of data.
            /// We also need a default constructor to actually make an iterator
            /// </summary>
            /// <param name="map"></param>
            /// <param name="index"></param>
            Iterator(const UnorderedHashMap& map, unsigned int index) : map(map), index(index) {}

            /// <summary>
            /// Simple check if an iterator and another arent equal
            /// </summary>
            /// <param name="other"></param>
            /// <returns></returns>
            bool operator!=(const Iterator& other) const {
                return index != other.index;
            }

            /// <summary>
            /// Dereferencing Operator for our iterator to get the current key-value
            /// </summary>
            /// <returns></returns>
            const KeyValuePair& operator*() const {
                return map.table[index];
            }

            /// <summary>
            /// Advances the iterator by one slot and gives us a new iterator to said spot
            /// </summary>
            /// <returns></returns>
            Iterator& operator++() {
                do {
                    ++index;
                } while (index < map.mCapacity && !map.table[index].is_occupied);
                return *this;
            }
        };

        /// <summary>
        /// Gets an iterator to the first actually occupied slot in the hash map, not just the first slot
        /// </summary>
        /// <returns></returns>
        Iterator begin() const {
            unsigned int index = 0;
            while (index < mCapacity && !table[index].is_occupied) {
                ++index;
            }
            return Iterator(*this, index);
        }

        /// <summary>
        /// Gets an iterator to the end of the map
        /// </summary>
        /// <returns>An iterator to the last value of the hash map</returns>
        Iterator end() const
        {
            return Iterator(*this, mCapacity);
        }

    };
}

