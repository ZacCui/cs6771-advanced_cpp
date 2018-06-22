#include "BucketSort.h"

#include <algorithm>
#include <cmath>
#include <iostream>

void BucketSort::sort(unsigned int numCores) {
    if(numCores > std::thread::hardware_concurrency()){
        numCores = std::thread::hardware_concurrency();
    }
    std::vector<std::thread> threads;
    powValue.clear();
    buckets.clear();
    storePowValue();
    buckets.resize(10);

    for(auto &n : numbersToSort){
        buckets[firstDigit(n,0U)].push_back(n);
    }

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

void BucketSort::r_sort(unsigned int finalIndex,std::vector<unsigned int> &vec, unsigned int pow){
        //merge
        auto ret = true;
        for(auto &n : vec){
            if (n >= powValue[pow]){
                 ret = false;
                 break;
            }
        }
        if(ret || pow == powValue.size()-1){
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
            if(n < powValue[pow]){
                temp[0].push_back(n);
            }else{
                temp[firstDigit(n,pow)%10+1].push_back(n);
            }
        }
        //revurvise
        auto pos = finalIndex;
        for(auto i = 0U; i < temp.size(); ++i){
            if(i) pos += temp[i-1].size();
            r_sort(pos,temp[i],pow+1);
        }
}


unsigned int BucketSort::firstDigit(unsigned int a, const unsigned int & pow){
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


