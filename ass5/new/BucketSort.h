#ifndef BUCKET_SORT_H
#define BUCKET_SORT_H

#include <thread>
#include <mutex>
#include <vector>

struct BucketSort {
	
	// vector of numbers
	std::vector<unsigned int> numbersToSort;
	std::vector<std::vector<unsigned int>> buckets;
	std::vector<unsigned int> powValue;
	unsigned int curr = 0U;
	std::mutex curr_mutex;

	void sort(unsigned int numCores);

	unsigned int firstDigit(unsigned int a, const unsigned int & pow);
	
	unsigned int getCurr();

	void storePowValue();

	void r_sort(unsigned int finalIndex,std::vector<unsigned int> &vec, unsigned int pow);

};


#endif /* BUCKET_SORT_H */