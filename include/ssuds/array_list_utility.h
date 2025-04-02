#include "array_list.h"
#include <random>
#include <string>
#include <iostream>
#include <algorithm>

namespace ssuds
{
	enum class SortOrder { ASCENDING, DESCENDING };

	template <class T>


	void partition(ssuds::ArrayList<T>& alist, int left_index, int right_index, SortOrder order, int &swaps, int &index)
	{
		int times_swapped= 0;

		if (order == SortOrder::ASCENDING)
		{
			int mid_index = (left_index + right_index) / 2;
			T pivot_value = alist[mid_index];

			std::swap(alist[mid_index], alist[right_index]);
			times_swapped++;

			int swap_index = left_index;
			for (int i = left_index; i <= right_index; i++)
			{
				if (alist[i] == alist[swap_index] && alist[i] >= pivot_value)
					{
						std::swap(alist[i], alist[swap_index]);
						swap_index++;
						times_swapped++;
					}
			}
			swaps = times_swapped;
			index = swap_index;
			
		}
	}
	template <class T>
	int quicksort(ssuds::ArrayList<T>& alist, int left_index, int right_index, SortOrder order)
	{
		int swap_index, swapped_times = 0;
		if (left_index >= right_index)
		{
			return 1;
		}
		partition(alist, left_index, right_index, order, swapped_times, swap_index);
		int pivot_index = swap_index;

		swapped_times += quicksort(alist, left_index, pivot_index - 1, order);
		swapped_times += quicksort(alist, pivot_index + 1, right_index, order);
		
		return swapped_times;
	
	}
	template <class T>
	int bubble_sort(ssuds::ArrayList<T>& alist, SortOrder desired_order)
	{
		int swaps = 0;
		bool is_sorted;
		if (desired_order == SortOrder::ASCENDING)
		{
			int n = alist.size();
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
			int n = alist.size();
			for (int i = 0; i < n - 1; i++)
			{
				is_sorted = false;
				for (int j = alist.size() - 1; j > 0; j--)
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
		int high = alist.size() - 1;

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
		int n = array.size();
		std::uniform_int_distribution<long int> uni(0, n-1);

	}
}