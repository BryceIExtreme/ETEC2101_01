#pragma once
#include <string>
#include <stdexcept>
#include <ostream>

namespace ssuds
{
	template <class T>
	class ArrayList
	{ 
		private:
			T* my_array;
			unsigned int my_array_size;
			unsigned int my_array_capacity;

		public:
			ArrayList()
			{
				
				//The Constructor
				// Option2: don't allocate the array just yet -- wait until first
				// append/insert/prepend
				my_array_capacity = 0;
				my_array_size = 0;
				my_array = nullptr;
			}
			~ArrayList()
			{
				//Decontructor
				delete[] my_array;
			}

			unsigned int get_size()
			{
				//Should return the size of the array, so how many things are in the array as of right now.
				return my_array_size;
			}

			unsigned int get_capacity()
			{
				//Should return the capacity of the array, so how many things CAN be put into the array before it goes overboard.
				return my_array_capacity;
			}

			void append(const T& new_value)
			{
				// This *might* make the array bigger....
				// IF the size == capacity, do the "Grow" operation
				//     Make a new temporary array (double our current capacity)
				//     Copy over data from current array to the new one
				//     Free up the old one
				//     Make my_array point to the bigger array
				//     Double capacity value.
				if (my_array_size < my_array_capacity)
				{
					my_array[my_array_size] = new_value;
					my_array_size++;
				}
				if (my_array_size >= my_array_capacity)
				{
					T* temp_array = new T[my_array_capacity * 2];
					temp_array[my_array_size] = new_value;
					for (unsigned int i = 0; i < my_array_capacity; i++)
						{
						temp_array[i] = my_array[i - 1];
						}
					// start our base our on a fresh slate!
					delete[] my_array;
					// pointing the array to the temporary array
					my_array = temp_array;

					++my_array_size;

				}
			}

			void prepend(T new_value)
			{
				if (my_array_size > my_array_capacity)
				{
					T* temp_array = new T[my_array_capacity * 2];
					temp_array[0] = new_value;
					for (unsigned int i = 1; i < my_array_capacity; i++)
					{
						temp_array[i] = my_array[i - 1];
					}
					// start our base our on a fresh slate!
					delete[] my_array;
					// pointing the array to the temporary array
					my_array = temp_array;

					++my_array_size;

				}
				// This is more costly because we need to move all values "up" one index
				// And possibly grow.
			}

			//<summary>
			//This function works similarly to the prepend and append functions, it even calls them if need be
			//but it allows the user to put the value at the index they want.
			//</summary>
			void insert(T new_value, unsigned int index)
			{
				if (index == 0)
				{
					prepend(new_value);
				}
				else if (index == my_array_size)
				{
					append(new_value);
				}
				else
				{
					if (my_array_size < my_array_capacity)
					{
						my_array[index] = new_value;
						my_array_size++;
					}
					if (my_array_size >= my_array_capacity)
					{
						T* temp_array = new T[my_array_capacity * 2];
						temp_array[index] = new_value;
							for (unsigned int i = index; i < my_array_capacity; i++)
							{
								temp_array[i] = my_array[i - 1];
							}
						// start our base our on a fresh slate!
						delete[] my_array;
						// pointing the array to the temporary array
						my_array = temp_array;

						++my_array_size;
					}
				}
			}

			void reserve(T start_value)
			{
				//Should reserve the amount of start_value worth of space in the capacity.
				//The first if should be if the user inputs a negative amount of space the entire thing just shouldn't work and or return the -1.
				//The else changes the capacity if the user enters a positive interger.
				if (start_value < 0)
				{
					return -1;
				}
				else
				{
					my_array_capacity = start_value;
				}
				return my_array_capacity;
			}

			int find(const T& search_value, unsigned int start_index = 0)
			{
				start_index = 0 + start_index;
				for (unsigned int i = start_index; i < my_array_size; i++)
				{
					if (my_array.at(i) == search_value)
					{
						return i;
					}
					else
					{
						continue;
					}
				}
				return -1;
				// Starting at start_index, do the search above.
			}

			void remove(unsigned int index)
			{
				//This if statement should decrease the capacity of the array by half if we are below half the amount.
				if (my_array_size < my_array_capacity / 2) {
					T* temp_array = new T[my_array_capacity / 2];
					for (unsigned int i = index; i < my_array_capacity; i++)
					{
						temp_array[i] = my_array[i + 1];
					}
					// start our base our on a fresh slate!
					delete[] my_array;
					// pointing the array to the temporary array
					my_array = temp_array;

					// adjusting the size of the array
					--my_array_size;
					
				}
				// When you remove something, you need to take all values after that index and move them
				// "down" one index.  You might need to shrink the array if we drop below half our capacity,
				// a "shrink" operation is needed.
				else 
				{
					//Goes through the entire array starting at the index provided, which then moves all the things after it down one space.
					for (unsigned int i = index; i < my_array_capacity; i++)
					{
						my_array[i] = my_array[i + 1];
					}
					// adjusting the size of the array
					--my_array_size;

					return true;
				
				}
			}

			int remove_all(const T& val)
			{
				unsigned int elim_count = 0;
				for (unsigned int i = 0; i < my_array_capacity; i++)
				{
					if (my_array.at(i) == val)
					{
						my_array.remove(i);
						elim_count++;
					}
					else
					{
						continue;
					}
				}
				return elim_count;
			}

			T at(unsigned int index) const
			{
				// This should raise a std::out_of_range error if index is invalid (index greater than
				// or equal to my_array_size).  Otherwise return the value at that index
				if (index >= my_array_size)
				{
					std::out_of_range("Index is out of range");
				}
				return my_array[index];
			}

			// ostream is the base class for all output-based streams (cout, ofstream)
			void output(std::ostream& os)
			{
				os << "[";
				for (unsigned int i = 0; i < size(); i++)
				{
					os << at(i);
					if (i < size() - 1)
						os << ", ";
				}
				os << "]";
			}
	};

}
