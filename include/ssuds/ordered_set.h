#pragma once
#include <string>
#include <stdexcept>
#include <ostream>
#include "iostream"
#include "array_list.h"
#include <optional>


namespace ssuds
{

	enum class TraversalType { PRE_ORDER, POST_ORDER, IN_ORDER };

	template <class T>
	class OrderedSet
	{

	private:
		// Just like LinkedList, I don't want outside users to see this AT ALL!!!
		class Node
		{
		friend class OrderedSet;
		private:
			T mData;
			Node* mLeft;
			Node* mRight;
		public:
			friend class OrderedSetIterator;
			friend class OrderedSet;
			Node(const T& data) : mData(data), mLeft(nullptr),
				mRight(nullptr)
			{
				// intentionally empty
			}

			~Node()
			{
				if (mLeft != nullptr)
				{
					delete mLeft;
				}
				if (mRight != nullptr)
				{
					delete mRight;
				}
			}


			int size_rec(Node* node) const 
			{
				if (node == nullptr) {
					return 0;
				}
				else {
					return 1 + get_size(node->mLeft) + get_size(node->mRight);
				}
			}



			void clear(Node*& node) {
				if (node != nullptr) {
					clear(node->mLeft);
					clear(node->mRight);
					delete node;
					node = nullptr;
				}
			}


			// Other getters/setters

			bool insert_recursive(const T& new_val)
			{
				if (new_val == mData)
					return false;			// It's a duplicate -- stop!
				else if (new_val < mData)
				{
					// This should go to my left
					if (mLeft == nullptr)
					{
						// I don't have a left-child -- make a new node that BECOMES the left child.
						mLeft = new Node(new_val);
						return true;
					}
					else
					{
						// I DO have a left child
						mLeft->insert_recursive(new_val);
					}
				}
				else
				{
					// This should go to my right -- similar to left case
					if (mRight == nullptr)
					{
						// I don't have a right-child -- make a new node that BECOMES the left child.
						mRight = new Node(new_val);
						return true;
					}

					else
					{
						// I DO have a right child
						mRight->insert_recursive(new_val);
					}
				}
			}
			void traversal_rec(ssuds::ArrayList<T>& values, TraversalType order, int& index) const
			{
				if (this == nullptr) {
					return; // Base case: stop recursion if the node is null
				}

				// Pre-order: Process current node before left and right children
				if (order == ssuds::TraversalType::PRE_ORDER) {
					values[index++] = this->mData;
				}

				// Traverse the left subtree
				if (mLeft != nullptr) {
					mLeft->traversal_rec(values, order, index);
				}

				// In-order: Process current node between left and right children
				if (order == ssuds::TraversalType::IN_ORDER) {
					values[index++] = this->mData;
				}

				// Traverse the right subtree
				if (mRight != nullptr) {
					mRight->traversal_rec(values, order, index);
				}

				// Post-order: Process current node after left and right children
				if (order == ssuds::TraversalType::POST_ORDER) {
					values[index++] = this->mData;
				}
			}


			Node* erase_rec(const T& val)
			{
				if (val == mData)
				{
					//need to remove
					//need to return true
					if (!mLeft && !mRight)
					{
						delete this;
						return nullptr;
					}
					else if (mLeft && mRight)
					{
						Node* succ = get_successor(val);
						mData = succ->mData;
						mRight->erase_rec(mData);
					}
					else if (mLeft && !mRight)
					{
						Node* temp = mLeft;
						mLeft = nullptr;
						delete this;
						return temp;
					}
					else if (!mLeft && mRight)
					{
						Node* temp = mRight;
						mRight = nullptr;
						delete this;
						return temp;
					}

					else if (val < mData && mLeft != nullptr)
					{
						mLeft = mLeft->erase_rec(val);
					}
					else if (val > mData && mRight)
					{
						mRight = mRight->erase_rec(val);
					}
					//We somehow got nothing
					return this;
				}
			}


			std::optional<Node*> parent_rec( const T& val) const 
			{
				if (this == nullptr || this->mData == val) {
					return false;
				}
				else if ((this->mLeft != nullptr && this->mLeft->mDaa == val) ||
					(this->mRight != nullptr && this->mRight->mData == val)) {
					return this;
				}
				else if (val < this->mData) {
					return parent_rec(val);
				}
				else {
					return parent_rec(val);
				}
			}


			bool contains_recursive(const T& val) const
			{
				// If I hold the value, return true.
				// If the value is less than my data it *WOULD* go to my left
				//     If I don't have a left child, return false
				//     If I do, ask the left child to compute the answer.

				if (val == mData) {
					return true;
				}
				else if (val < mData) {
					return mLeft && mLeft->contains_recursive(val);
				}
				else {
					return mRight && mRight->contains_recursive(val);
				}
				if (this->mLeft == nullptr && this->mRight == nullptr) 
				{
					return false;
				}
			}


			int height_rec() const {
				if (this == nullptr) {
					return 0;
				}
				else {
					return 1 + std::max(get_height(this->mLeft), get_height(this->mRight));
				}
			}


			Node* succ_rec(const T& val) const
			{
				Node* node = mRoot;
				Node* successor = nullptr;

				while (node != nullptr) {
					if (val < node->mData) {
						successor = node;
						node = node->mLeft;
					}
					else if (val > node->value) {
						node = node->mRight;
					}
					else {
						if (node->right != nullptr) {
							successor = find_min(node->mRight);
						}
						break;
					}
				}

				if (successor != nullptr) {
					return successor->mData;
				}
				else {
					return nullptr;
				}
			}


			Node* find_min(Node* node) const 
			{
				while (node->mLeft != nullptr) {
					node = node->mLeft;
				}
				return node;
			}






		}; // end of Node class

		// OrderedSetIterator here
		public:
			class OrderedSetIterator
			{

			};
		// Attributes for OrderedSet itself.
	private:
		unsigned int mSize;
		Node* mRoot;
	public:


		OrderedSet() : mSize(0), mRoot(nullptr)
		{
			// intentionally empty.

		}

		~OrderedSet()
		{
			if (mRoot != nullptr)
				delete mRoot;
		}

		void clear() 
		{
			clear_rec(mRoot);
		}

		unsigned int get_size() const 
		{ return size_rec(mRoot); 
		}


		bool insert(const T& val)
		{
			if (mSize == 0)
			{
				// Nothing here -- make the new node the root
				mRoot = new Node(val);
				mSize = 1;
				return true;
			}
			else
			{
				// We already have a root -- let it handle the rest
				bool result = mRoot->insert_recursive(val);
				if (result)
					mSize++;
			}
		}

		bool contains(const T& val) const
		{
			if (!mRoot)
				return false;
			else
				return mRoot->contains_recursive(val);
		}


		ssuds::ArrayList<T> traversal(ssuds::TraversalType order) const 
		{
			ssuds::ArrayList<T> values;
			int index = 0;
			mRoot->traversal_rec(values, order, index);
			return values;
		}

		bool erase(const T& val)
		{
			if (mSize == 0)
				return false;
			else
			{
				mRoot = mRoot->erase_rec(val);
			}
		}

		void rebalance()
		{
			ssuds::ArrayList<T> io = traversal(TraversalType::IN_ORDER);
			clear();
			mRoot = rebalance_rec(io, 0, io.size() - 1);
		}
		

		int get_height() const 
		{ 
			return this->height_rec(); 
		}

		int get_succesor(const T& val) const
		{
			return this->succ_rec(val);
		}

		std::optional<Node*> get_parent(const T& val) const 
		{
			return this->parent_rec(val);
		}

	};
}
