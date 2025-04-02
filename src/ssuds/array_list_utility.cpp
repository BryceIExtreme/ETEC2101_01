#include "array_list.h"
#include "array_list_utility.h"
#include <random>
#include <string>
#include <iostream>
#include <algorithm>

namespace ssuds
{

	template <class T>
	int quicksort(ssuds::ArrayList<T>& alist, SortOrder order)
	{

	}
	template <class T>
	void bubble_sort(ssuds::ArrayList<T>& alist, SortOrder desired_order)
	{
		int swaps = 0;
		bool is_sorted;
		if (desired_order == SortOrder::ASCENDING)
		{
			int n = alist.mSize;
			for (int i = 0; i < n - 1; i++)
			{
				is_sorted = false;
				for (int j = 0; j < n - 1; j++)
				{
					if (alist[j] > alist[j + 1])
					{
						std::swap(alist[i], alist[j]);
						++swaps;
						is_sorted = true;
					}
				}
				if (!is_sorted)
				{
					break;
				}
			}
		}
		else
		{
			int n = alist.mSize;
			for (int i = 0; i < n - 1; i++)
			{
				is_sorted = false;
				for (int j = alist.mSize - 1; j > 0; j--)
				{
					if (alist[j] > alist[j + 1])
					{
						std::swap(alist[i], alist[j]);
						++swaps;
						is_sorted = true;
					}
				}
				if (!is_sorted)
				{
					break;
				}
			}
		}
		return swaps;
	}
	template <class T>
	int binary_search(ssuds::ArrayList<T>& alist, SortOrder order, int value) 
	{
		int low = 0;
		int high = alist.mSize - 1;

		while (low <= high) {
			int mid = low + (high - low) / 2;
			if (alist[mid] == value) {
				return mid;
			}
			if ((order == SortOrder::ASCENDING && alist[mid] < value) ||
				(order == SortOrder::DESCENDING && alist[mid] > value)) {
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
		}
		return -1;
	}
	template <class T>
	void shuffle(ssuds::ArrayList<T>& array)
	{
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(array.begin(), array.end(), g);

	}
}