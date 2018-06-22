#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class BucketSort {
public:
    BucketSort() noexcept = default;
    BucketSort(const BucketSort& b) noexcept
        : powResults{b.powResults}, buckets{b.buckets},
        currBucketIndex{b.currBucketIndex}, currBucketIndexMutex{}
    {
    }

    void sort(const unsigned int numCores);

    std::vector<unsigned int> numbersToSort {};

private:
    bool aLessB(const unsigned int& x, const unsigned int& y, unsigned int pow = 0) const;
    void calculatePowResults();
    unsigned int getFirstDigit(unsigned int x) const;
    void sortBucket();

    std::pair<unsigned int, bool> takeCurrBucketIndex();

    std::vector<unsigned int> powResults {};
    std::vector<std::vector<unsigned int>> buckets {};
    unsigned int currBucketIndex = 0U;
    std::mutex currBucketIndexMutex {};
};

#endif /* BUCKET_SORT_H */