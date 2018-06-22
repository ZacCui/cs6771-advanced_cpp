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

	void sort1(unsigned int numCores);


	bool aLessB(const unsigned int& x, const unsigned int& y, unsigned int pow);

	const unsigned int firstDigit(unsigned int a);

	unsigned int getCurr();

	void storePowValue();

};


#endif /* BUCKET_SORT_H */