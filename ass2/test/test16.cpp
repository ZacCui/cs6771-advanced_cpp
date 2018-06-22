// miscellanenous test

#include <iostream>
#include <vector>

#include "EuclideanVector.h"

int main() {

	// 0 dimensions test	
	evec::EuclideanVector ev0(0);

	// try to do some fun things with no dimensions
	std::cout << ev0 << " " << ev0.getNumDimensions() << std::endl;
	std::cout << ev0.getEuclideanNorm() << std::endl;
	
	// create a container of vectors
	std::vector<evec::EuclideanVector> evV;
	evV.push_back(ev0);
	evV.push_back(evec::EuclideanVector(1));
	
	// modify the base vector
	ev0 = evec::EuclideanVector(3,2);
	
	// check that the container vector hasn't changed
	std::cout << ev0 << " " << ev0.getNumDimensions() << std::endl;
	std::cout << ev0.getEuclideanNorm() << std::endl;
	std::cout << evV[0] << " " << evV[0].getEuclideanNorm() << std::endl;
	
	// modify the container and see if the norm changes
	ev0[2] = 6.0;
	std::cout << ev0 << " " << ev0.getEuclideanNorm() << std::endl;
	
}
