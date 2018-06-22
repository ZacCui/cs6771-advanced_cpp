#include "BucketSort.h"

#include <algorithm>
#include <cmath>
#include <iostream>

// TODO: replace this with a parallel version. 
void BucketSort::sort(unsigned int numCores) {
    if(numCores > std::thread::hardware_concurrency()) exit(0);
    std::vector<std::thread> threads;
    powValue.clear();
    buckets.clear();
    storePowValue();
    buckets.resize(10);

    for(const auto &n : numbersToSort){
        buckets[firstDigit(n)].push_back(n);
    }
    
    auto sort = [&](){
        for(auto i = getCurr(); i < buckets.size(); i = getCurr()){
            std::sort(buckets[i].begin(), buckets[i].end(),
                [&](unsigned int & a, unsigned int & b){
                    return aLessB(a,b,1);
                });

            auto pos = 0U;
            for (auto j = 0U; j < i; ++j) pos += buckets[j].size();  
            for (auto & n : buckets[i]) numbersToSort[pos++] = std::move(n);
        }
    };
    for(auto i = 0U; i < numCores-1; ++i) threads.push_back(std::thread(sort));

    sort();

    for (auto& t : threads) t.join();
}


void BucketSort::sort1(unsigned int numCores) {
        storePowValue();
        std::sort(numbersToSort.begin(),numbersToSort.end(), [&](const unsigned int& x, const unsigned int& y){
                return aLessB(x,y,0);
        } );
}

bool BucketSort::aLessB(const unsigned int& x, const unsigned int& y, unsigned int pow) {
    
        if (x == y) return false; // if the two numbers are the same then one is not less than the other
    
        unsigned int a = x;
        unsigned int b = y;
    
        // work out the digit we are currently comparing on. 
        if (pow == 0) {
                a = firstDigit(a);
                b = firstDigit(b);
        } else {
            while (a / 10 >= powValue[pow]) {
                a /= 10;
            }
            while (b / 10 >= powValue[pow]) {
                b /= 10;
            }
        }
        //std::cout << powValue[pow] << " " << a << " " << b << '\n';
        if (a == b)
                return aLessB(x,y,pow + 1);  // recurse if this digit is the same 
        else
                return a < b;
}


const unsigned int BucketSort::firstDigit(unsigned int a){
    while (a >= 10) {
        a /= 10; 
    }
    return a;
}

unsigned int BucketSort::getCurr(){
    std::lock_guard<std::mutex> guard(curr_mutex);
    return curr++;
}

void BucketSort::storePowValue() {
    auto pow = 0U;
    for (auto a = std::numeric_limits<unsigned int>::max(); a > 0; a /= 10) {
        powValue.push_back((unsigned int) std::round(std::pow(10, pow)));
        ++pow;
    }
    powValue.push_back((unsigned int) std::round(std::pow(10, pow)));
}



/*
    auto partition = [&](){
        for(auto i = getCurr(); i < numbersToSort.size(); i = getCurr()){
            std::lock_guard<std::mutex> guard(push_mutex);
            buckets[firstDigit(numbersToSort[i])-1].push_back(numbersToSort[i]);
        }
    };

    for(auto i = 0U; i < numCores-1; ++i){
        threads.push_back(std::thread(partition));
    }
    partition();

    for (auto& t : threads) t.join();
    */

/*
    numbersToSort.clear();
    for(auto & n: buckets){
        std::move(std::begin(n), std::end(n), std::back_inserter(numbersToSort));
    }*/

