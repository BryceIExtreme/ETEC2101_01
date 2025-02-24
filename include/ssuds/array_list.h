#pragma once
#include <string>
#include <stdexcept>
#include <ostream>
#include <initializer_list>

// Note: in C++, a general tempate (like this one) must be defined inline
// entirely in the .h file (no .cpp files).  

namespace ssuds
{
	/// An ArrayList is an array-based data structure. 
	template <class T>
	class ArrayList
	{
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ ATTRIBUTES                              @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	protected:
		/// The default (and minimum) capacity of an ArrayList
		static const int msMinCapacity = 5;

		/// The current number of "slots" AVAILABLE in mData (i.e. the array size)
		unsigned int mCapacity;

		/// How many slots are we USING?  This will always be less than or equal to mCapacity
		unsigned int mSize;

		/// The array of data we're currently holding.  Note: an alternative would've been T* mData
		/// but I'm attempting to use raw bytes here so we don't have to have a default constructor
		/// for templated types.
		unsigned char* mData;



		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ CONSTRUCTORS / DESTRUCTORS              @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		class ArrayListIterator		// or iterator?
		{
		private:
			// Some attributes here....
			ArrayList* my_array_list;		// Keeps track of the ArrayList we're traversing.
			int index;			// Keeps track of our current spot (and how many times we've
			// been incremented)

		public:
			ArrayListIterator()
			{
				my_array_list = nullptr;
				index = 0;
			}

			ArrayListIterator(ArrayList* owning_list, int starting_index)
			{
				my_array_list = owning_list;
				index = starting_index;
			}


			bool operator != (const ArrayListIterator& rhs)
			{
				// Finish me!   We should return false if we're NOT like rhs
				if (this != my_array_list)
				{
					return 0;
				}
			}

			// This is a "unary" operator (no parameters).  Triggered by ++my_iterator
			ArrayListIterator operator++()
			{
				// We change ourself and then return a copy of ourself

				// First, advance our position
				index++;


				if (index > my_array_list.mSize)
				{
					my_array_list = NULL;
				}
				// We need to ensure when we're done traversing the ArrayList, that
				// we are made to look like the special "null" iterator that gets
				// returned by the end function.
				return *this;
			}

			// Optional.  Triggered by my_iterator++;  Note the "Dummy" variable is just to distinguish
			// from ++my_iterator, but plays no role.
			ArrayListIterator operator++(int dummy)
			{
				
				// We make a copy of ourself, then change ourself, then return the copy
				index++;

				if (index > my_array_list.mSize)
				{
					my_array_list = NULL;
				}

				return *this;
			}


			// This is called when we do something like    std::string cur_string = *my_iterator;
			T& operator*()
			{
				// Our job is to return the value at the current "position" in the
				// ArrayList we're iterating through.
				return my_array_list->at(index);
			}

			// (Optional).  Maybe this too
			ArrayListIterator operator+(int offset)
			{
				index = index + offset;
			}
			
			ArrayListIterator(const ArrayListIterator& other_ali)
			{
				unsigned char* new_arrayI = nullptr;
				new_arrayI = new unsigned char[other_ali.mSize * sizeof(T)];

				// Copy data from the existing array
				memcpy(new_arrayI, mData, mSize * sizeof(T));
		
				// 4. Make sure size and capacity attribute are correct.
				mData = new_arrayI;
				mCapacity = other_ali.mCapacity;
				mSize = other_ali.mSize;
				// 5. Return a reference to ME (to support chain assignments like a = b = c)
				return *this;      // De-reference the this pointer to get a reference
			}
			ArrayListIterator operator=(const ArrayListIterator& other_ali)
			{
				unsigned char* new_arrayI = nullptr;
				new_arrayI = new unsigned char[other_ali.mSize * sizeof(T)];

				// Copy data from the existing array
				memcpy(new_arrayI, mData, mSize * sizeof(T));

				// Free the old array
				delete[] mData;
				// 4. Make sure size and capacity attribute are correct.
				mData = new_arrayI;
				mCapacity = other_ali.mCapacity;
				mSize = other_ali.mSize;
				// 5. Return a reference to ME (to support chain assignments like a = b = c)
				return *this;      // De-reference the this pointer to get a reference
			}


		}; // end of ArrayListIterator nested class

		/// Default constructor
		ArrayList()
		{
			mSize = 0;
			mCapacity = 0;
			mData = nullptr;
		};

		// New initializer-list constructor
		ArrayList(std::initializer_list<T>& init_list)
		{
			// We need to set our attributes to starting values.
			mSize = 0;
			mCapacity = 0;
			mData = nullptr;

			// init_list has size() method and an iterator, but that's it.
			// We could use a manual iterator
			typename std::initializer_list<T>::iterator it = init_list.begin();

			// Or use a for-each loop
			for (const T& cur_val : init_list)
			{
				// Do something with cur_val...
				append(cur_val);
			}
		}



		/// Destructor
		~ArrayList()
		{
			// Note that I used to worry about mData being null, but the delete operator
			// already has an internal check to avoid freeing a null pointer, so adding our own
			// would be redundance, so I'm commenting this line.
			// if (mData)
			delete[] mData;
		}


		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ OTHER METHODS (alphabetical)            @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:

		// overload =operator using Method1 (could use method 2 or 3 as well)
		ArrayList& operator=(const ArrayList& other_al)
		{
			// We want a DEEP copy here (make us have a distinc array, but with the same
			// values as other_al)
			// 1. Free up our array. Done further down
			// 2. Make a new array (at least big enough to hold other_al.size())
			unsigned char* new_array = nullptr;
			new_array = new unsigned char[other_al.mSize * sizeof(T)];

			// Copy data from the existing array
			memcpy(new_array, mData, mSize * sizeof(T));

			// Free the old array
			delete[] mData;
			// 4. Make sure size and capacity attribute are correct.
			mData = new_array;
			mCapacity = other_al.mCapacity;
			mSize = other_al.mSize;
			// 5. Return a reference to ME (to support chain assignments like a = b = c)
			return *this;      // De-reference the this pointer to get a reference
		}

		ArrayList(const ArrayList& other_al)
		{
			// Just like an =operator, but no need to do step1.  Initialize your attributes instead.
			// Then do steps 2 - 4 from the =operator.
			
			unsigned char* new_array = nullptr;
			new_array = new unsigned char[other_al.mSize * sizeof(T)];

			// Copy data from the existing array
			memcpy(new_array, mData, mSize * sizeof(T));

			// 4. Make sure size and capacity attribute are correct.
			mData = new_array;
			mCapacity = other_al.mCapacity;
			mSize = other_al.mSize;
			// 5. Return a reference to ME (to support chain assignments like a = b = c)
			return *this;      // De-reference the this pointer to get a reference
		}

		/// <summary>
		///  Inserts a new element at the end of the array
		/// </summary>
		/// <param name="val">the new value to add</param>
		void append(const T& val)
		{
			// check to see if we need to increase our capacity
			grow();

			// Stick our new element in the last slot and (sneakily) increase our size in the process
			// ... This is what I had originally...
			//(T&)(mData[mSize * sizeof(T)]) = val;
			// ... but I switched to this.  Person seemed to be a problem (in particular the strings)
			//     Memcpy would side-step any = operators.  I'm not 100% sure why this fixed the problem
			memcpy(&mData[mSize * sizeof(T)], &val, sizeof(T));
			//T temp = (T&)(mData[mSize * sizeof(T)]);     // <- seeing if I could read out what i put in just now
			mSize++;
		}


		/// <summary>
		/// Returns a reference to the item at the given index.  Since it is a reference, this
		/// type of operation is allowed:
		///		my_float_array.at(5) = 17.3f;
		///		my_int_array.at(3)++;
		/// This method will raise a std::out_of_range exception if an invalid index is given.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		T& at(const unsigned int index) const
		{
			if (index >= mSize)
				throw std::out_of_range("Invalid index (" + std::to_string(index) + ")");
			return (T&)(mData[index * sizeof(T)]);
		}

		ArrayList operator [](const unsigned int index)
		{
			return (T&)(mData[index * sizeof(T)]);
		}


		/// <summary>
		/// Returns the current capacity of the ArrayList (this is always
		/// greater than or equal to the size)
		/// </summary>
		/// <returns>the capacity of the internal array in the ArrayList</returns>
		unsigned int capacity() const
		{
			return mCapacity;
		}

		/// <summary>
		/// Clears the array back to its original state
		/// </summary>
		void clear()
		{
			if (mData)
				delete[] mData;
			mData = nullptr;
			mSize = 0;
			mCapacity = 0;
		}

		/// <summary>
		/// Finds the index of the first occurrence of the given value
		/// </summary>
		/// <param name="val">the value to search for</param>
		/// <param name="start_index">the index to start searching at</param>
		/// <returns></returns>
		int find(const T& val, const unsigned int start_index = 0) const
		{
			if (start_index >= mSize)
				throw std::out_of_range("Invalid index: " + std::to_string(start_index));

			for (unsigned int i = start_index; i < mSize; i++)
			{
				T temp = at(i);
				if (temp == val)
					return i;
			}

			// We didn't find it
			return -1;
		}



		/// <summary>
		/// Inserts a new data item at a given index
		/// </summary>
		/// <param name="val">the new value to insert</param>
		/// <param name="index">the index at which to insert (must be >= 0 and <= size) </param>
		void insert(const T& val, unsigned int index)
		{
			if (index > mSize)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			else if (index == mSize)
				append(val);
			else
			{
				// check to see if we need to increase capacity first
				grow();

				// Move all the elements that come *after* index up one spot
				memcpy(&mData[sizeof(T) * (index + 1)], &mData[index * sizeof(T)], (mSize - index) * sizeof(T));

				// Put our new elements in spot index and increase our size
				//(T&)(mData[index * sizeof(T)]) = val;
				memcpy(&mData[index * sizeof(T)], &val, sizeof(T));
				mSize++;
			}
		}


		/// <summary>
		/// Outputs the ArrayList to the given output stream
		/// </summary>
		/// <param name="os">an ostream object (ofstream, stringstream, cout, etc.) </param>
		void output(std::ostream& os) const
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

		friend ArrayList operator <<(std::ostream& os) const
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

		/// <summary>
		/// Removes a data item at the given index
		/// </summary>
		/// <param name="index">the index of the thing to remove (will return a std::out_of_bounds exception if invalid (<0 or >= size)</param>
		/// <param name="resize_if_necessary">if true, the array will be resized if it is now below half capacity</param>
		/// <returns>the data item that was just removed</returns>
		T remove(unsigned int index, bool resize_if_necessary = true)
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));

			// Get the value we'll return at the end (the element removed)
			T result = (T&)(mData[index * sizeof(T)]);

			// Move all elements that come after index down one spot
			memcpy(&mData[index * sizeof(T)], &mData[(index + 1) * sizeof(T)], (mSize - index - 1) * sizeof(T));

			// Decrement our size
			mSize--;

			// Shrink, if applicable and requested
			if (resize_if_necessary)
				shrink();

			// Return the result
			return result;
		}

		/// <summary>
		/// Removes all occurrences of a given value.  Uses find and remove internally to do the removal
		/// </summary>
		/// <param name="val">the value to remove</param>
		/// <param name="resize_if_necessary">if true, the array will be resized if it is now below half capacity</param>
		/// <returns>the number of occurrences of that data item that were removed</returns>
		int remove_all(const T val, bool resize_if_necessary = true)
		{
			int cur_index = 0;
			unsigned int num_removed = 0;
			while (cur_index >= 0 && (unsigned int)cur_index < mSize)
			{
				// Find the next occurrence of val, starting at the current position
				cur_index = find(val, cur_index);
				if (cur_index >= 0)
				{
					// We found one!
					remove(cur_index, false);
					num_removed++;
				}
			}

			if (resize_if_necessary)
				shrink();

			return num_removed;
		}


		/// <summary>
		/// Ensures the internal array has at least this capacity.  This is useful if
		/// the user knows how many items they will add and don't want to take the performance
		/// penalty of the grow operation happening in-between.  If the capacity is already higher or
		/// equal to the given value, there will be no effect.
		/// </summary>
		/// <param name="desired_capacity">The capacity will be set to at least this value</param>
		void reserve(unsigned int desired_capacity)
		{
			if (desired_capacity > mCapacity)
			{
				// Make the larger array
				unsigned char* temp_array = new unsigned char[desired_capacity * sizeof(T)];
				memset(temp_array, 0, sizeof(T) * desired_capacity);

				// Copy data from the existing array
				memcpy(temp_array, mData, mSize * sizeof(T));

				// Free the old array
				delete[] mData;

				// Make mData point to the larger array
				mData = temp_array;
				mCapacity = desired_capacity;
			}
		}

		/// <summary>
		/// Returns the size of the internal array (i.e.) how many things are being stored in the ArrayList
		/// </summary>
		/// <returns>the size of the ArrayList</returns>
		unsigned int size() const
		{
			return mSize;
		}

		ArrayListIterator begin()
		{
			// In Python, all methods have self first.  This is a reference to the instance
			// of the class that called it.  In C++, there is "this", a POINTER to the instance
			// that called it.
			ArrayListIterator return_value(this, 0);
			return return_value;
		}

		ArrayListIterator end()
		{
			// Your job is to make a special "null" value for an Iterator here.  
			ArrayListIterator return_value(NULL,mSize);
			// Set up that instance and return
			return return_value;
		}

		ArrayListIterator rbegin()
		{
			ArrayListIterator return_value(this, mSize);
			return return_value;
		}

		ArrayListIterator rend()
		{
			ArrayListIterator return_value(NULL, mSize);
			return return_value;
		}


	protected:
		/// <summary>
		/// An internal method to resize the array if we are currently at capacity (if we are not, nothing is done)
		/// </summary>
		void grow()
		{
			if (mSize == mCapacity)
			{
				// Allocate what will become the new array
				unsigned char* new_array = nullptr;
				if (mCapacity == 0)
				{
					new_array = new unsigned char[msMinCapacity * sizeof(T)];
					memset(new_array, 0, msMinCapacity * sizeof(T));
				}
				else
				{
					new_array = new unsigned char[(mCapacity * 2) * sizeof(T)];
					memset(new_array, 0, (mCapacity * 2) * sizeof(T));
				}

				// Copy over data from the old array (if any)
				if (mData != nullptr)
				{
					memcpy(new_array, mData, sizeof(T) * mSize);

					// Destroy the old array
					delete[] mData;
				}

				// Make the new array *the* array
				mData = new_array;

				// Note that our capacity is now double what it used to be
				if (mCapacity == 0)
					mCapacity = msMinCapacity;
				else
					mCapacity *= 2;
			}
		}


		/// <summary>
		/// An internal method to see if the array can be shrunk (capacity reduced by half, down to msMinCapacity)
		/// </summary>
		void shrink()
		{
			if (mSize < mCapacity / 4 && mCapacity > msMinCapacity)
			{
				// Allocate what will become the new array
				unsigned char* new_array = new unsigned char[(mCapacity / 2) * sizeof(T)];
				memset(new_array, 0, (mCapacity / 2) * sizeof(T));

				// Copy over data from the old array (if any)
				memcpy(new_array, mData, mSize * sizeof(T));

				// Destroy the old array
				delete[] mData;

				// Make the new array *the* array
				mData = new_array;

				// Note that our capacity is now double what it used to be
				mCapacity /= 2;
			}
		}		
	};
}
