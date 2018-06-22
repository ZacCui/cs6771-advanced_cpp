// tests the performance of the caching of the Euclidean norm

#include <iostream>
#include <vector>

#include "EuclideanVector.h"


int main() {

	std::vector<double> vd;
	for (double d = 4; d < 200001; d *= ( (d / vd.size()) / (1.3 * vd.size())) ) {
		vd.push_back(d);
	}

	evec::EuclideanVector ev {vd.begin(), vd.end()};

	std::cout << ev.getNumDimensions() << std::endl;

	std::cout << ev << std::endl;

	for (long i = 0; i < 100000001; ++i) {
		ev.getEuclideanNorm();
		if (i % 10000000 == 0) {
			std::swap(ev[0],ev[ev.getNumDimensions()-1]);
			std::swap(ev[1],ev[0]);
			std::cout << ev << " " << ev.getEuclideanNorm() << std::endl;
		}
	}


}
