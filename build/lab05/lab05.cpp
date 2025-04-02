

#include <iostream>
#include <fstream>
#include "array_list.h"
#include "array_list_utility.h"
#include <chrono>
using namespace std::chrono;

int main(int argc, char** argv)
{
    std::ofstream fp("..\\..\\media\\results.csv");
    fp << "n, create-time(ns), shuffle-time(ns), copy-time(ns), save-time(ns), quicksort(ms), bubblesort(ms), binary-search(ms), linear-search(ms)\n";
    for (int sample_size = 1000; sample_size <= 21000; sample_size += 5000)
    {
        
     
        fp << sample_size << ", ";

        //Step 1: Creating ArrayList
        auto start1 = high_resolution_clock::now();
        ssuds::ArrayList<float> flist;
        std::random_device device;
        std::uniform_real_distribution<float> distribution(-5.0f, 25.0f);
        std::mt19937 generator(device());
        for (int i = 0; i <= sample_size; i++)
        {
            flist.append(distribution(generator));
        }
        auto stop1 = high_resolution_clock::now();
        auto create_time = duration_cast<nanoseconds>(stop1 - start1);
        fp << create_time.count() << ", ";

        //Step 2: Shuffle Time
        auto start2 = high_resolution_clock::now();
        shuffle(flist);
        auto stop2 = high_resolution_clock::now();
        auto time_for_shuffle = duration_cast<nanoseconds>(stop2 - start2);
        fp << time_for_shuffle.count() << ", ";

        //Step 3: Copying the shuffled Array
        auto start3 = high_resolution_clock::now();
        ssuds::ArrayList<float> flist2(flist);
        auto stop3 = high_resolution_clock::now();
        auto time_for_copy = duration_cast<nanoseconds>(stop3 - start3);
        fp << time_for_copy.count() << ", ";

        //Step 4: Saving Away 1000 values
        auto start4 = high_resolution_clock::now();
        ssuds::ArrayList<float> flist3 = flist;
        for (int i = 0; i < 1000; i++)
        {
            flist3.append(flist[i]);
        }
        auto stop4 = high_resolution_clock::now();
        auto time_for_save = duration_cast<nanoseconds>(stop4 - start4);
        fp << time_for_save.count() << ", ";

        //Step 5: Quicksort the OG Array
        auto start5 = high_resolution_clock::now();
        quicksort(flist, 0, sample_size, ssuds::SortOrder::ASCENDING);
        auto stop5 = high_resolution_clock::now();
        auto time_for_quicksort = duration_cast<milliseconds>(stop5 - start5);
        fp << time_for_quicksort.count() << ", ";

        //Step 6: Bubblesort the Copy Array
        auto start6 = high_resolution_clock::now();
        bubble_sort(flist2, ssuds::SortOrder::ASCENDING);
        auto stop6 = high_resolution_clock::now();
        auto time_for_bubblesort = duration_cast<milliseconds>(stop6 - start6);
        fp << time_for_bubblesort.count() << ", ";

        //Step 7: Bineary Search
        auto start7 = high_resolution_clock::now();
        for (int i = 0; i < 1000; i++ )
        {
            binary_search(flist, ssuds::SortOrder::ASCENDING, flist3[i]);
        }
        auto stop7 = high_resolution_clock::now();
        auto time_for_bin_search = duration_cast<nanoseconds>(stop7 - start7);
        fp << time_for_bin_search.count() << ", ";

        //Step 8: Linear Search
        auto start8 = high_resolution_clock::now();
        for (int i = 0; i < 1000; i++)
        {
            flist.find(flist3[i]);
        }
        auto stop8 = high_resolution_clock::now();
        auto time_for_line_search = duration_cast<milliseconds>(stop8 - start8);
        fp << time_for_line_search.count() << ", ";


        fp << "\n";
    }
    fp.close();
}


