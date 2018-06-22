#include <iostream>
#include <random>
#include <thread>
#include <cassert>

#include "BucketSort.h"

int main() {
	BucketSort test;
	test.numbersToSort.push_back(98);
	test.numbersToSort.push_back(12);
	test.numbersToSort.push_back(643);
	test.numbersToSort.push_back(53);
	test.numbersToSort.push_back(52);
	test.numbersToSort.push_back(3);
	test.numbersToSort.push_back(3);
	test.numbersToSort.push_back(143);
	test.numbersToSort.push_back(32);
	test.numbersToSort.push_back(0);
	test.numbersToSort.push_back(10);
	test.numbersToSort.push_back(1);


	test.sort(4);
	for(auto n: test.numbersToSort){
		std::cout << n << ' ';
	}
	std::cout << '\n';
	
	unsigned int totalNumbers =	5000000;
	unsigned int printIndex =	259000;
	
	// use totalNumbers required as the seed for the random
	// number generator. 
	std::mt19937 mt(totalNumbers);
	std::uniform_int_distribution<unsigned int> dist(1, std::numeric_limits<unsigned int>::max());

	// create a sort object
	BucketSort pbs;


	// insert random numbers into the sort object
	for (unsigned int i=0; i < totalNumbers; ++i) {
		pbs.numbersToSort.push_back(dist(mt));

	} 
	
	// call sort giving the number of cores available.
        const unsigned int numCores = std::thread::hardware_concurrency();
        pbs.sort(numCores);

        std::cout << "number of cores used: " << numCores << std::endl;
	
	// print certain values from the buckets
	std::cout << "Demonstrating that all the numbers that start with 1 come first" << std::endl;
	std::cout << pbs.numbersToSort[0] << " " << pbs.numbersToSort[printIndex - 10000]
		<< " " << pbs.numbersToSort[printIndex] << " " << pbs.numbersToSort[pbs.numbersToSort.size() - 1] 
		<< std::endl;
	
	/*for(auto n: pbs.numbersToSort){
		std::cout << n << '\n';
	}*/
	/*for(auto l = 0U; l < pbs.numbersToSort.size();++l){
		assert(pbs.numbersToSort[l] == test.numbersToSort[l]);
	}*/

	
}
