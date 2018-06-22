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

    for(auto &n : numbersToSort){
        buckets[firstDigit(n,0U)].push_back(n);
    }

    auto r_sort= [&](unsigned int finalIndex,std::vector<unsigned int> &vec, unsigned int pow){
        //merge
        auto max = std::max_element(vec.begin(),vec.end());
        if(*max < powValue[pow]){
            for(auto &n : vec){
                numbersToSort[finalIndex++] = std::move(n);
            }
            return;
        }
        std::vector<std::vector<unsigned int>> temp;
        //partition
        //\d+[0-9] and 0 total 11 elements
        temp.resize(11); 
        for(auto &n : vec){
            auto & index = firstDigit(n,pow);
            if(!index){
                temp[index].push_back(n);
            }else{
                temp[index%10+1].push_back(n);
            }
        }
        //revurvise
        auto pos = finalIndex;
        for(auto i = 0U; i < temp.size(); ++i){
            if(i) pos += temp[i-1].size();
            r_sort(finalIndex,temp[i],pow+1);
        }
    };

    auto sort = [&](){
        for(auto i = getCurr(); i < buckets.size(); i = getCurr()){
            auto pos = 0U;
            for (auto j = 0U; j < i; ++j) pos += buckets[j].size();  
            r_sort(pos,buckets[i],1);
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


const unsigned int BucketSort::firstDigit(unsigned int a, const unsigned int & pow){
    if(pow == 0){
        while (a >= 10) {
            a /= 10; 
        }
    }else{
        while (a / 10 >= powValue[pow]){
            a /= 10;
        }
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

