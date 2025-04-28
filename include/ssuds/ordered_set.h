#pragma once
#include <string>
#include <stdexcept>
#include <ostream>
#include "iostream"
#include "array_list.h"
#include <optional>
#include "linked_list.h"



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
			const T& getData() const 
			{
				return mData;
			}

			int size_rec(Node* node) const
			{
				if (node == nullptr) {
					return 0;
				}
				else {
					int leftSize = size_rec(node->mLeft);
					int rightSize = size_rec(node->mRight);
					int totalSize = 1 + leftSize + rightSize;
					return totalSize;
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
				if (this == nullptr) return false;
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
			void traversal_rec(ssuds::ArrayList<T>& values, TraversalType order, int& index) const {
				if (this == nullptr) {
					return; // Base case: stop recursion if the node is null
				}

				// Pre-order: Process current node before left and right children
				if (order == ssuds::TraversalType::PRE_ORDER) {
					values.push_back(this->mData); // Use push_back
				}

				// Traverse the left subtree
				if (mLeft != nullptr) {
					mLeft->traversal_rec(values, order, index);
				}

				// In-order: Process current node between left and right children
				if (order == ssuds::TraversalType::IN_ORDER) {
					values.push_back(this->mData); // Use push_back
				}

				// Traverse the right subtree
				if (mRight != nullptr) {
					mRight->traversal_rec(values, order, index);
				}

				// Post-order: Process current node after left and right children
				if (order == ssuds::TraversalType::POST_ORDER) {
					values.push_back(this->mData); // Use push_back
				}
			}


			Node* erase_rec(const T& val) {
				if (val == mData) {
					if (!mLeft && !mRight) {
						delete this;
						return nullptr;
					}
					else if (mLeft && mRight) {
						Node* succ = succ_rec(val);
						mData = succ->mData;
						mRight = mRight->erase_rec(mData);
					}
					else if (mLeft && !mRight) {
						Node* temp = mLeft;
						mLeft = nullptr;
						delete this;
						return temp;
					}
					else if (!mLeft && mRight) {
						Node* temp = mRight;
						mRight = nullptr;
						delete this;
						return temp;
					}
				}
				else if (val < mData && mLeft != nullptr) {
					mLeft = mLeft->erase_rec(val);
				}
				else if (val > mData && mRight != nullptr) {
					mRight = mRight->erase_rec(val);
				}
				return this;
			}




			std::optional<Node*> parent_rec(const T& val) const
			{
				if (this == nullptr || this->mData == val) {
					return std::nullopt; // Return an empty optional if the current node is null or matches the value
				}
				else if ((this->mLeft != nullptr && this->mLeft->mData == val) ||
					(this->mRight != nullptr && this->mRight->mData == val)) {
					return const_cast<Node*>(this); // Cast away constness to return a non-const Node*
				}
				else if (val < this->mData && mLeft != nullptr) {
					return mLeft->parent_rec(val); // Recur on the left subtree
				}
				else if (val > this->mData && mRight != nullptr) {
					return mRight->parent_rec(val); // Recur on the right subtree
				}
				return std::nullopt; // Return an empty optional if no parent is found
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


			int height_rec(Node* node) const {
				if (node == nullptr) {
					return 0;
				}
				return 1 + std::max(height_rec(node->mLeft), height_rec(node->mRight));
			}


			Node* succ_rec(const T& val)
			{
				Node* node = this; // Start from the current node
				Node* successor = nullptr;

				while (node != nullptr) {
					if (val < node->mData) {
						successor = node; // Update successor
						node = node->mLeft;
					}
					else if (val > node->mData) {
						node = node->mRight;
					}
					else {
						if (node->mRight != nullptr) {
							successor = find_min(node->mRight); // Find the minimum in the right subtree
						}
						break;
					}
				}

				return successor; // Return the successor node
			}


			Node* find_min(Node* node) const
			{
				while (node->mLeft != nullptr) {
					node = node->mLeft;
				}
				return node;
			}

			static Node* rebalance_rec(const ssuds::ArrayList<T>& values, int start, int end) {
				if (start > end) {
					return nullptr; // Base case: no elements to process
				}

				// Find the middle element
				int mid = start + (end - start) / 2;

				// Create a new node with the middle element
				Node* newNode = new Node(values[mid]);

				// Recursively build the left and right subtrees
				newNode->mLeft = rebalance_rec(values, start, mid - 1);
				newNode->mRight = rebalance_rec(values, mid + 1, end);

				return newNode;
			}
		}; // end of Node class




	public:
		// In-Order Iterator
		class InOrderIterator
		{
		private:
			LinkedList<Node*> mStack; // Using LinkedList as a stack
			Node* mCurrent;

		public:
			InOrderIterator(Node* root) : mCurrent(root) {
				// Initialize the stack with the leftmost path
				while (mCurrent != nullptr) {
					mStack.push_front(mCurrent);
					mCurrent = mCurrent->mLeft;
				}
			}

			bool has_next() const {
				return !mStack.is_empty();
			}

			const T& next()
			{
				if (mStack.is_empty()) {
					throw std::out_of_range("No more elements in the iterator");
				}

				// Pop the top node from the stack
				mCurrent = mStack.pop_front();

				// Save the data to return
				const T& result = mCurrent->mData;

				// If the current node has a right child, push its leftmost path onto the stack
				mCurrent = mCurrent->mRight;
				while (mCurrent != nullptr) {
					mStack.push_front(mCurrent);
					mCurrent = mCurrent->mLeft;
				}

				return result;
			}
		};

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
			if (mRoot != nullptr) {
				mRoot->clear(mRoot);
				mRoot = nullptr; // Ensure the root is reset
				mSize = 0;       // Reset the size
			}
		}

		unsigned int get_size() const 
		{ 
			return mRoot->size_rec(mRoot); 
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
				return result;
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
			if (mRoot) {
				int treeSize = mRoot->size_rec(mRoot); // Calculate the size of the tree

				values.reserve(treeSize);             // Reserve capacity in the ArrayList
				int index = 0;
				mRoot->traversal_rec(values, order, index);
			}
			else {
				std::cout << "Traversal failed: mRoot is nullptr" << std::endl;
			}
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
			ssuds::ArrayList<T> io = traversal(TraversalType::IN_ORDER); // Collect elements in sorted order
			clear(); // Clears the tree
			mRoot = Node::rebalance_rec(io, 0, io.size() - 1); // Rebuild the tree from the sorted list
			mSize = io.size(); // Update the size of the tree
		}
		

		int get_height() const 
		{ 
			return mRoot->height_rec(mRoot);
		}

		int get_succesor(const T& val) const
		{
			if (!mRoot) {
				throw std::runtime_error("Tree is empty");
			}
			if (!contains(val)) {
				throw std::runtime_error("Value not found in the tree");
			}
			Node* successorNode = mRoot->succ_rec(val);
			if (successorNode != nullptr) {
				return successorNode->mData; // Return the data of the successor node
			}
			else {
				throw std::runtime_error("Successor not found");
			}
		}

		std::optional<Node*> get_parent(const T& val) const 
		{
			return mRoot->parent_rec(val);
		}

		InOrderIterator begin_in_order() const {
			return InOrderIterator(mRoot);
		}


	};
}
