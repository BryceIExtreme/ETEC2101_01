#pragma once
#include <string>
#include <stdexcept>
#include <ostream>
#include "iostream"

//The general namespace this will go in, just like array list
namespace ssuds
{
	/// <summary>
	/// The enumerator class that allows us to select if we wanna go from front to back with FORWARD or back to front with BACKWARD
	/// </summary>
	enum class LinkedListIteratorDirection { FORWARD, BACKWARD };


	/// <summary>
	/// A linked list based data structure
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	class LinkedList
	{
		// IMPORTANT DESIGN CONSIDERATION: User shouldn't be able to see any Nodes!!
	private:
		/// <summary>
		/// A container of multiple bits of data we might need to access
		/// Like the stats of a character player
		/// </summary>
		class Node			// Each instance corresponds to an orange "box" in the slides
		{
		public:
			/// <summary>
			/// The Data grouped into the Node
			/// </summary>
			T mData;
			/// <summary>
			/// The next node in the list, NULL if there is none
			/// </summary>
			Node* mNext;
			/// <summary>
			/// The previous node, allows a doubly linked list
			/// </summary>
			Node* mPrevious;
		};

	public:
		/// <summary>
		/// Similar to the ArrayListIterator this is used to help us traverse data within the LinkedList
		/// </summary>
		class LinkedListIterator
		{
			friend class LinkedList;
		private:
			// attributes???
			Node* mCurrentNode;
			LinkedListIteratorDirection mType;

		public:
			LinkedListIterator(LinkedListIteratorDirection tp, Node* node) : mCurrentNode(node), mType(tp)
			{
				//Intentionally empty thing
			}

			LinkedListIterator() : mCurrentNode(nullptr), mType(LinkedListIteratorDirection::FORWARD)
			{

			}

			bool operator==(const LinkedListIterator& other) const
			{
				return mCurrentNode == other.mCurrentNode;
			}

			bool operator!=(const LinkedListIterator& other) const
			{
				return !(*this == other);
			}

			T& operator*()
			{
				return (mCurrentNode->mData);
			}

			// Might return a LinkedListIterator?
			LinkedListIterator operator++()
			{
				if (mType == LinkedListIteratorDirection::FORWARD)
					mCurrentNode = mCurrentNode->mNext;
				else
					mCurrentNode = mCurrentNode->mPrevious;
				return LinkedListIterator(mType, mCurrentNode);
			}

			LinkedListIterator operator++(int not_used)
			{
				if (mType == LinkedListIteratorDirection::FORWARD)
					mCurrentNode = mCurrentNode->mNext;
				else
					mCurrentNode = mCurrentNode->mPrevious;
				return LinkedListIterator(mType, mCurrentNode);
			}

			LinkedListIterator operator=(const LinkedListIterator& other)
			{
				mCurrentNode = other.mCurrentNode;
				mType = other.mType;
				return *this;
			}

			LinkedListIterator operator-(int offset) const
			{
				Node temp = mCurrentNode;
				for (int i = 0; i < offset && temp; ++i); {
					temp = temp->mPrevious;
				}
				return LinkedListIterator(temp, mType);
			}

			LinkedListIterator operator+(int offset) const
			{
				Node* temp = mCurrentNode;
				for (int i = 0; i < offset && temp; ++i); {
					temp = temp->mNext;
				}
				return LinkedListIterator(temp, mType);
				

			}

		};

		// Attributes
		Node* mStart;			// Sometimes called the "head"
		Node* mEnd;				// Sometimes called the "tail"
		unsigned int mSize;

	public:
		LinkedList()
		{
			mStart = nullptr;
			mEnd = nullptr;
			mSize = 0;
		}

		/// <summary>
		/// The move constructor based on the similar principal of making a shallow copy that we used in ArrayList
		/// </summary>
		/// <param name="other"></param>
		LinkedList(LinkedList&& other) : mStart(other.mStart), mEnd(other.mEnd), mSize(other.mSize)
		{
			other.mStart = nullptr;
			other.mEnd = nullptr;
			other.mSize = 0;
		}

		LinkedList(const LinkedList& other) : mStart(other.mStart), mEnd(other.mEnd), mSize(other.mSize)
		{
			
		}

		/// <summary>
		/// Function that goes through each node of the Linked List and clears it of data
		/// </summary>
		void clear()
		{
			Node* current = mStart;
			while (current != nullptr) {
				Node* next = current->mNext;
				delete current;
				current = next;
			}
			mStart = mEnd = nullptr;
			mSize = 0;
		}

		/// <summary>
		/// Deconstructor which uses the clear method to clean up each node
		/// </summary>
		~LinkedList()
		{
			clear();
		}

		void append(const T& val)
		{

			if (mSize == 0)
			{
				// Case1: list is empty
				// a. Make a new Node
				// b. Make mStart and mEnd point to it.
				Node* new_node = new Node;
				mStart = mEnd = new_node;			// Maybe add a constructor to Node??
				new_node->mData = val;	            // Initializing the new node (could've
				new_node->mNext = nullptr;          //    referred to mEnd -- it's the same node!)
				new_node->mPrevious = nullptr;
			}
			else
			{
				// Case2: list has data in it
				Node* new_node = new Node;
				new_node->mData = val;	            // Initializing the new node (could've
				new_node->mNext = nullptr;          //    referred to mEnd -- it's the same node!)
				new_node->mPrevious = nullptr;
				// Make the current last node point to this new one
				mEnd->mNext = new_node;
				// Make the new node point to the *CURRENT* end node
				new_node->mPrevious = mEnd;
				// Make the new node THE last node
				mEnd = new_node;
			}
			// Increase size
			mSize++;
		}

		void prepend(const T& val)
		{

			if (mSize == 0)
			{
				// Case1: list is empty
				// a. Make a new Node
				// b. Make mStart and mEnd point to it.
				Node* new_node = new Node;
				mStart = mEnd = new_node;			// Maybe add a constructor to Node??
				new_node->mData = val;	            // Initializing the new node (could've
				new_node->mNext = nullptr;          //    referred to mEnd -- it's the same node!)
				new_node->mPrevious = nullptr;
			}
			else
			{
				// Case2: list has data in it
				Node* new_node = new Node;
				new_node->mData = val;	            // Initializing the new node (could've
				new_node->mNext = nullptr;          //    referred to mEnd -- it's the same node!)
				new_node->mPrevious = nullptr;
				// Make the current first node point to this new one
				mStart->mPrevious = new_node;
				// Make the new node point to the *CURRENT* first node
				new_node->mNext = mStart;
				// Make the new node THE first node
				mStart = new_node;
			}
			// Increase size
			mSize++;
		}

		void insert(const T& new_val, unsigned int index)    // O(n) b/c of step2
		{
			// 1. Check index to see if it's valid -- if not raise std::out_of_range exception
			//      I allowed index == mSize here and just did an append (and return)
			//      if index == 0, just call prepend (and return)
			// 2. Navigate to the current node at the given index (called cur_node)
			// 3. Create a new node.
			if (index > mSize)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			else if (index == mSize)
				append(new_val);
			else if (index == 0) 
			{
				prepend(new_val);
			}
			else
			{
				Node* cur_node = mStart;

				for (int i = 0; i < index && cur_node; ++i)
				{
					cur_node = cur_node->mNext;
				}


				Node* new_node = new Node;
				new_node->mData = new_val;
				new_node->mNext = nullptr;
				new_node->mPrevious = nullptr;
				// 4. Make changes to the links:
				new_node->mPrevious = cur_node->mPrevious;     // b.
				new_node->mPrevious->mNext = new_node;		   // a.
				new_node->mNext = cur_node;					   // d. 
				cur_node->mPrevious = new_node;				   // c. 
				
				// 5. Increase size
				mSize++;
			}

		}

		unsigned int size() const
		{
			return mSize;
		}

		friend std::ostream& operator <<(std::ostream& os, const LinkedList& alist)
		{
			alist.output(os);
			return os;
		}

		void output(std::ostream& os) const
		{
			// Output in python-list style output: [A, B, C, D, E].  This pattern
			// is called ITERATING (not iterator) through all the nodes -- very
			// common pattern in the linked list.
			os << "[";
			Node* cur_node = mStart;		// Might be nullptr!!
			for (unsigned int i = 0; i < mSize; i++)
			{
				//os << mData[i];		// Not a thing here!!!
				os << cur_node->mData;
				cur_node = cur_node->mNext;
				if (i < mSize - 1)
					os << ", ";
			}
			os << "]";
		}


		T& operator[](unsigned int index) const
		{
			// 1. Check index to see if it's valid -- if not raise std::out_of_range exception
			// 2. Loop to the proper spot (using the iteration pattern on slide 8)
			// 3. Return the data of that current node.
			// (maybe a few bonus points if you pick the "smart" side of the linked list to
			//     start from)

			if (index > mSize)
				throw std::out_of_range("Invalid index: " + std::to_string(index));

			return at(index);

		}

		T& at(unsigned int index) const
		{
			Node* current = mStart;
			for (int i = 0; i < index && current; ++i) {
				current = current->mNext;
			}
			while (current != nullptr) {
				return current->mData;
			}
			throw std::out_of_range("Index out of range");

		}

		int find(const T& val, const unsigned int start_index = 0) const
		{
			Node* temp_node = mStart;
			int i;
			if (start_index >= mSize)
				return -1;
			for (i = 0; i < start_index && temp_node; ++i)
			{
				temp_node = temp_node->mNext;
			}

			while (temp_node != nullptr)
			{
				T node_data = temp_node->mData;
				if (node_data == val)
				{
					return i;
				}
				temp_node = temp_node->mNext;
				i++;
			}
			// We didn't find it
			std::cout << "Item not found" << "\n";
			return -1;
		}

		LinkedListIterator find(const T& val, const LinkedListIterator& start) const
		{
			LinkedListIterator temp = start;
			LinkedListIterator ender;

			if (start.mType == LinkedListIteratorDirection::FORWARD)
				ender = end();
			else
				ender = rend();

			while (temp != ender)
			{
				if (*temp == val)
					return temp;
				else
					++temp;
			}

			return temp;
		}

		T remove(unsigned int index)
		{
			Node* current = mStart;
			if (index >= mSize)
			{
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			}
			for (int i = 0; i < index && current; ++i) {
				current = current->mNext;
			}
			while (current != nullptr)
			{
				T result = current->mData;
				current->mPrevious->mNext = current->mNext;     // b.
				current->mNext->mPrevious = current->mPrevious;		   // a.

				mSize--;

				return result;
			}

		}

		LinkedListIterator remove(LinkedListIterator& it) 
		{
			if (it.mCurrentNode == mEnd)
			{
				it.mCurrentNode->mPrevious->mNext = nullptr;
				mSize--;
				return it;
			}
			if (it.mCurrentNode == mStart)
			{
				it.mCurrentNode->mNext->mPrevious = nullptr;
				mSize--;
				return it;
			}
			it.mCurrentNode->mPrevious->mNext = it.mCurrentNode->mNext;
			it.mCurrentNode->mNext->mPrevious = it.mCurrentNode->mPrevious;
			it.mCurrentNode = it.mCurrentNode->mNext;
			mSize--;
			return it;


		}

		void remove_all(const T& val, LinkedListIterator& it)
		{
			if (it.mCurrentNode == mStart && it.mCurrentNode->mData == val)
			{
				it.mCurrentNode->mNext->mPrevious = nullptr;
				mSize--;
				it.mCurrentNode = it.mCurrentNode->mNext;
			}
			while (it.mCurrentNode != mEnd)
			{
				if (it.mCurrentNode->mData == val)
				{
					it.mCurrentNode->mPrevious->mNext = it.mCurrentNode->mNext;
					it.mCurrentNode->mNext->mPrevious = it.mCurrentNode->mPrevious;
					mSize--;
				}
				it.mCurrentNode = it.mCurrentNode->mNext;
			}
			if (it.mCurrentNode == mEnd && it.mCurrentNode->mData == val)
			{
				it.mCurrentNode->mPrevious->mNext = nullptr;
				mSize--;
			}
		}

		LinkedListIterator begin() const
		{
			return LinkedListIterator(LinkedListIteratorDirection::FORWARD, mStart);
		}

		LinkedListIterator rbegin() const
		{
			return LinkedListIterator(LinkedListIteratorDirection::BACKWARD, mEnd);
		}


		LinkedListIterator end() const
		{
			return LinkedListIterator(LinkedListIteratorDirection::FORWARD, NULL);
		}

		LinkedListIterator rend() const
		{
			return LinkedListIterator(LinkedListIteratorDirection::BACKWARD, NULL);
		}
	};

}
