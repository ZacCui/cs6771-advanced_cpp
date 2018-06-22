// test the performance for a large Euclidean vector

#include <iostream>
#include <vector>

#include "EuclideanVector.h"

// this is designed to be a hard test so you cannot pass it unless you are good.
#include "EuclideanVector.h"

int main() {
	
	std::vector<double> vd;
	for (int d = 1; d < 7000000; ++d) {
		vd.push_back(d);
	}
	
	evec::EuclideanVector ev {vd.begin(), vd.end()};
// should use the following one but some solutions don't really work 
//	evec::EuclideanVector ev2 {vd.rbegin(), vd.rbegin() + (vd.size() / 2)};
	evec::EuclideanVector ev2 {vd.begin(), vd.begin() + (vd.size() / 2)};
	
	std::cout << ev.getNumDimensions() << std::endl;
	
	std::cout << ev.getEuclideanNorm() << " " << ev2.getEuclideanNorm() << std::endl;
	
	for (long i = 0; i < 100000001; ++i) {
		if (i % 2500000 == 0) {
			std::swap(ev,ev2);
			std::cout << ev.getEuclideanNorm() << " " << ev2.getEuclideanNorm() << std::endl;
		}
	}
	
	
}

