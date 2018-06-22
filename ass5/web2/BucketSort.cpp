#include "BucketSort.h"

#include <algorithm>
#include <cmath>
#include <thread>
#include <iostream>
#include <mutex>

bool aLessB(const unsigned int& x, const unsigned int& y, unsigned int pow) {
    
        if (x == y) return false; // if the two numbers are the same then one is not less than the other
    
        unsigned int a = x;
        unsigned int b = y;
    
        // work out the digit we are currently comparing on. 
        if (pow == 0) {
                while (a / 10 > 0) {
                        a = a / 10; 
                }   
                while (b / 10 > 0) {
                        b = b / 10;
                }
        } else {
        	while (a / 10 >= (unsigned int) std::round(std::pow(10,pow))) {
                        a = a / 10;
                }
                while (b / 10 >= (unsigned int) std::round(std::pow(10,pow))) {
                        b = b / 10;
                }
        }

        if (a == b)
                return aLessB(x,y,pow + 1);  // recurse if this digit is the same 
        else
                return a < b;
}
//get number of digits in a number
int getSize(unsigned int x) {
    int retval = (x < 10 ? 1 :
              (x < 100 ? 2 :
               (x < 1000 ? 3 :
                (x < 10000 ? 4 :
                 (x < 100000 ? 5 :
                  (x < 1000000 ? 6 :
                   (x < 10000000 ? 7 :
                    (x < 100000000 ? 8 :
                     (x < 1000000000 ? 9 :
                      10)))))))));
    return retval-1;
}
//get digit at a given index in the number; -1 if invalid region
int getDigit(unsigned int num, int digitIndex) {
    if (digitIndex > getSize(num)) return -1;
    unsigned int pow = std::round(std::pow(10, digitIndex));
    while (num/10 >= pow) {
        num = num/10;
    }
    return num%10;
}

void BucketSort::sort(unsigned int numCores) {

//    std::sort(numbersToSort.begin(),numbersToSort.end(), [](const unsigned int& x, const unsigned int& y){
//        return aLessB(x,y,0);
//    } );
//
//    return;

    //clamping max number of cores to be used and necessary buckets and thread lists
    //numCores = numCores -1;
    std::vector<std::vector<unsigned int>> bucket;
    std::vector<std::vector<unsigned int>> finalBuc;
    bucket.resize(11);
    finalBuc.resize(11);
    std::vector<std::thread> threads;
    std::vector<std::thread> threads2;
    std::recursive_mutex bucMutex;


//    std::vector<unsigned int> array;
//    for (unsigned int z = 50; z > 0; z--) {
//        array.push_back(z);
//    }
//    array.push_back(111);
//    array.push_back(112);
//    array.push_back(999);
//    array.push_back(289341);
//    array.push_back(245);

    //Function that splits up the given vector into sections so that each thread can create inside
    //a series of buckets that bucketize the given range of vector indices
    //after this they are placed into a larger bucket
    std::function<void(unsigned int start, unsigned int end, unsigned int core)> buc_place;
    buc_place = [this, &bucket,  &bucMutex] (unsigned int start, unsigned int end, unsigned int core) {
        if (start != 0) start++;
        //create small buckets and size it to what is required (0 -> 9)
        std::vector<std::vector<unsigned int>> sml_buc;
        sml_buc.resize(10);
        //for the given range; get put all the numbers in correct small buckets
        for (unsigned int i = start; i <= end; i++) {
            //getDigit gets the digit at the given significant digit index
            sml_buc[ getDigit(numbersToSort[i], 0) ].push_back(numbersToSort[i]);
        }
        //now place it into big bucket; be wary of overwrites - so use mutexes
        bucMutex.lock();
        for (unsigned int i = 0; i < 10; i++) {
            bucket[i].insert(bucket[i].end(), sml_buc[i].begin() , sml_buc[i].end() );
        }
        bucMutex.unlock();
    };

    //get the size of the vector and divide vector[treat it like array] indices
    //into ranges for each thread
    unsigned int maxSize = numbersToSort.size() - 1;
    unsigned int subrange = maxSize/numCores;
    unsigned int start = 0;
    unsigned int end = 0;
    unsigned int i = 0;

    for (i = 0; i < numCores; ++i) {
        end = start+subrange;
        if (i == numCores - 1) {
            end = maxSize; //if last thread the break out of look and set end to true end (stops any rounding errors)
            break;
        }
        //create a thread that places given range into small buckets AND into big buckets after
        threads.push_back(std::thread{buc_place, start, end, i});
        start += subrange;
    }
    //also using this current thread to do the placing
    buc_place(start, end, i);

    //wait for all threads to rejoin
    for (auto& t : threads) {
        //std::cout << "Closing 1st thread\n";
        t.join();
    }
    threads.clear();

    //keep track of number of threads
    int numThreadsInUse = 0;
    //this function does a recursive radix sort
    std::function<void(std::vector<unsigned int> vec, int digit, int maxDigit, int parentBucIndex )> radix_sort;
    radix_sort = [this, &numThreadsInUse, &radix_sort, &bucMutex, &finalBuc ] (std::vector<unsigned int> vec, int digit, int maxDigit, int parentBucIndex ) {
        //get the maximal number of sig figures present in given dataset
        maxDigit = 0;
        for( auto num: vec ) {
            if (getSize(num) > maxDigit) maxDigit = getSize(num);
        }
        //create buckets and resize them then push numbers into buckets
        std::vector<std::vector<unsigned int>> tempBuc;
        tempBuc.resize(11);
        for( auto num: vec ) {
            tempBuc[ getDigit(num , digit ) +1 ].push_back(num);
        }

        //if we are at last step of the radix sort; place them into final bucket
        if (digit >= maxDigit) {
            bucMutex.lock();
            for (unsigned int i = 0; i < 11; i++) {
                for (auto num: tempBuc[i]) finalBuc[parentBucIndex].push_back(num);
            }
            numThreadsInUse--;
            bucMutex.unlock();
            return;
        }
        //or else recursive call radix on all buckets in a sequence
        for (unsigned int i = 0; i < 11; i++) {
             if (tempBuc[i].size() != 0) radix_sort( tempBuc[i], digit+1 , maxDigit, parentBucIndex);
        }
    };

    std::mutex thrMutex;
    int bucIndex = -1;

    //this is a wrapper for the radix sort, necessary to keep track of what bucket needs to be sorted
    //next by whatever thread
    //MUTEXES are used to stop any race conditions on when buckets are selected for sorting
    std::function<void()> radix_wrapper;
    radix_wrapper = [this, &radix_sort, &radix_wrapper, &thrMutex, &bucket, &bucIndex] () {
        while (bucIndex < 9) {

            thrMutex.lock();
            bucIndex++;

            thrMutex.unlock();
            //when function called; sort bucket and increment so next bucket is
            //the one to be sorted
            radix_sort(bucket[bucIndex], 1, 10, bucIndex);
            thrMutex.lock();
            //if function returns for radix sort (bucket is done) find out which bucket to sort next
            if (bucIndex < 9) {
                thrMutex.unlock();
                radix_wrapper();
            } else {
                thrMutex.unlock();
            }
        }

    };
    //call the radix wrapper on all the cores available
    //we only call up to numCores-1 (if given 4, call 3)
    for (unsigned int i = 0; i < numCores-1; i++) {
        threads2.push_back(std::thread{radix_wrapper});
    }
    //then we also use current thread to run the radix sorter
    radix_wrapper();

    //wait for sorting to finish and join them
    for (auto& t : threads2) {
        //std::cout << "Closing 2nd thread\n";
        t.join();
    }
    //clear the list
    numbersToSort.clear();
    //in the final bucket; add each bucket in order to the numbersToSort list
    for (unsigned int i = 0; i < 11; i++) {
        numbersToSort.insert(numbersToSort.end(), finalBuc[i].begin(), finalBuc[i].end());
    }
}