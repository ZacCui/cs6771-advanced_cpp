// test for header guards by including twice

#include <iostream>

#include "EuclideanVector.h"
#include "EuclideanVector.h"

int main() {

	// try the extra normal functions without operator overloading.

	unsigned int i = 3;
	double d = 1.0;
	evec::EuclideanVector ev (i,d);

	std::cout << ev.getNumDimensions() << std::endl;

	for (unsigned int i = 0; i < ev.getNumDimensions(); ++i) {
		std::cout << ev.get(i) << std::endl;
	}

	std::cout << ev.getEuclideanNorm() << std::endl;

	auto evNorm = ev.createUnitVector();
	for (unsigned int i = 0; i < evNorm.getNumDimensions(); ++i) {
		std::cout << evNorm.get(i) << std::endl;
	}

}
